#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "diseaseTransmission.h"
#include "utils.h"

using namespace std;

DiseaseTransmission::DiseaseTransmission(const string &name) :
	Atomic(name),
	vectorRequest(addOutputPort("vectorRequest")),
	humansRequest(addOutputPort("humansRequest")),
	dogsRequest(addOutputPort("dogsRequest")),
	vectorResponse(addInputPort("vectorResponse")),
	humansResponse(addInputPort("humansResponse")),
	dogsResponse(addInputPort("dogsResponse")),
	transmitInfectedVectors(addOutputPort("transmitInfectedVectors")),
	transmitInfectedDogs(addOutputPort("transmitInfectedDogs")),
	transmitInfectedHumans(addOutputPort("transmitInfectedHumans")),
	frequency_time(0,0,0,1){
}


Model &DiseaseTransmission::initFunction(){
	transmissionRateFromInfectedVectorsToSusceptibleHumans = 0.000150;
	transmissionRateOnSusceptibleDogs = 0.001661;
	standardDeviationOnSusceptibleDogs = 0.000498;
	transmissionRateFromAcuteHumans = 0.000531;
	standardDeviationFromAcuteHumans = 0.000159;
	transmissionRateFromIndeterminateHumans = 0.000166;
	standardDeviationFromIndeterminateHumans = 0.00005;
	transmissionRateFromChronicHumans = 0.000166;
	standardDeviationFromChronicHumans = 0.00005;
	transmissionRateFromInfectedDogs = 0.038533;
	standardDeviationFromInfectedDogs = 0.01156;
	dogsPreferenceFactor = 2.0/3.0;
	lagBetweenFeeds = 6;
	state = VECTOR_REQUEST;
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &DiseaseTransmission::externalFunction(const ExternalMessage &msg){
	if(msg.port() == vectorResponse){
		//llegan las cantidades correspondientes a los vectores infectados
		//y no infectados que pueden picar en el presente dia
		nonInfectedVectors = getValueFromTupleAt(msg, 0);
		infectedVectors = getValueFromTupleAt(msg, 1);
		allVectors = nonInfectedVectors + infectedVectors;
		//std::cout << "nonInfectedVectors: " << nonInfectedVectors << '\n';
		//std::cout << "infectedVectors: " << infectedVectors << '\n';
		//std::cout << "allVectors: " << allVectors << '\n';
		state = HUMANS_REQUEST;
	} else if(msg.port() == humansResponse){
		//ya tenemos las cantidades de humanos que seran picados
		//(susceptibles, agudos, indeterminados y cronicos... en ese orden)
		susceptibleHumans = getValueFromTupleAt(msg, 0);
		acuteHumans = getValueFromTupleAt(msg, 1);
		indeterminateHumans = getValueFromTupleAt(msg, 2);
		chronicHumans = getValueFromTupleAt(msg, 3);
		state = DOGS_REQUEST;
	} else if(msg.port() == dogsResponse){
		//sabemos que perros seran picados (susceptibles e infectados)
		susceptibleDogs = getValueFromTupleAt(msg, 0);
		infectedDogs = getValueFromTupleAt(msg, 1);
		state = NEW_INFECTED;
	}

	//me despierto y hago lo que corresponda con los datos que llegaron
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &DiseaseTransmission::internalFunction(const InternalMessage &msg){
	switch (this->state) {
		case NEW_INFECTED:
			//es un nuevo dia... comienza el ciclo nuevamente
			state = VECTOR_REQUEST;
			holdIn(AtomicState::active, this->frequency_time);
			break;
		default:
			//me pongo a la espera de los datos correspondientes
			passivate();
			break;
	}
	return *this;
}


Model &DiseaseTransmission::outputFunction(const CollectMessage &msg){
	switch (this->state) {
		case VECTOR_REQUEST:
			vectorsReadyToFeed(msg);
			break;
		case HUMANS_REQUEST:
			requestToHumans(msg);
			break;
		case DOGS_REQUEST:
			requestToDogs(msg);
			break;
		case NEW_INFECTED:
			transmissionForHumans();
			transmissionForDogs();
			transmitNewInfected(msg);
			break;
		default:
	    cout<<"Error: no se pudo encontrar etapa de transmisión para"<<this->state<<"\n";
	    break;
	}
	return *this ;
}

void DiseaseTransmission::vectorsReadyToFeed(const CollectMessage &msg){
	//como los vectores se alimentan aprox cada 6 dias,
	//pido una sexta parte de los vectores totales
	sendOutput(msg.time(), vectorRequest, Real(1/lagBetweenFeeds));
}

void DiseaseTransmission::requestToHumans(const CollectMessage &msg){
	//la probabilidad que un vector pique a un perro en lugar de una persona
	//es de 2/3... por lo tanto calculo cuantos vectores picaran a humanos
	std::discrete_distribution<int> vectorDistribution({infectedVectors, nonInfectedVectors});
	amountOfVectorsForHumans = round(allVectors * (1 - dogsPreferenceFactor));

	std::map<int, int> resultsForHumans;
	for(int n=0; n<amountOfVectorsForHumans; ++n) {
			++resultsForHumans[vectorDistribution(randomGenerator)];
	}

	infectedVectorsForHumans = resultsForHumans[0];
	nonInfectedVectorsForHumans = resultsForHumans[1];
	//y consulto cuales humanos seran picados
	sendOutput(msg.time(), humansRequest, Real(amountOfVectorsForHumans));
}

void DiseaseTransmission::requestToDogs(const CollectMessage &msg){
	//el complemento de vectores representa a aquellos que picaran perros
	amountOfVectorsForDogs = allVectors - amountOfVectorsForHumans;
	infectedVectorsForDogs = infectedVectors - infectedVectorsForHumans;
	nonInfectedVectorsForDogs = nonInfectedVectors - nonInfectedVectorsForHumans;

	//y consulto que perros seran picados
	sendOutput(msg.time(), dogsRequest, Real(amountOfVectorsForDogs));
}

void DiseaseTransmission::transmissionForHumans(){
	//ya sabemos que vectores (infectados o no) picaran a los humanos (en sus
	//respectivos estadios)... ahora calculamos las cantidades resultantes
	//despues de las eventuales transmisiones que se produzcan por las picaduras
	std::discrete_distribution<int> humansDistribution({susceptibleHumans, acuteHumans, indeterminateHumans, chronicHumans});

	//primero para la combinacion con vector infectado... solo nos interesa saber
	//cuantas personas susceptibles fueron picadas (los otros estadios no son relevantes)
	//y calcular la probabilidad que efectivamente se infecten
	std::map<int, int> resultsForHumansAgainstInfectedVectors;
	for(int n=0; n<infectedVectorsForHumans; ++n) {
			++resultsForHumansAgainstInfectedVectors[humansDistribution(randomGenerator)];
	}

	double susceptibleHumansAgainstInfectedVector = resultsForHumansAgainstInfectedVectors[0];
	double acuteHumansAgainstInfectedVector = resultsForHumansAgainstInfectedVectors[1];
	double indeterminateHumansAgainstInfectedVector = resultsForHumansAgainstInfectedVectors[2];
	double chronicHumansAgainstInfectedVector = resultsForHumansAgainstInfectedVectors[3];

	newInfectedHumans = floor(transmissionRateFromInfectedVectorsToSusceptibleHumans * susceptibleHumansAgainstInfectedVector);

	//ahora calculamos la combinacion con vector no infectado... debemos reformular
	//la distribucion de humanos, restando los ya utilizados en la combinacion anterior
	int susceptibleBis = susceptibleHumans - susceptibleHumansAgainstInfectedVector;
	int acuteBis = acuteHumans - acuteHumansAgainstInfectedVector;
	int indeterminateBis = indeterminateHumans - indeterminateHumansAgainstInfectedVector;
	int chronicBis = chronicHumans - chronicHumansAgainstInfectedVector;
	std::discrete_distribution<int> humansDistribution2({susceptibleBis, acuteBis, indeterminateBis, chronicBis});

	std::map<int, int> resultsForHumansAgainstNonInfectedVectors;
	for(int n=0; n<nonInfectedVectorsForHumans; ++n) {
			++resultsForHumansAgainstNonInfectedVectors[humansDistribution2(randomGenerator)];
	}

	double susceptibleHumansAgainstNonInfectedVector = resultsForHumansAgainstNonInfectedVectors[0];
	double acuteHumansAgainstNonInfectedVector = resultsForHumansAgainstNonInfectedVectors[1];
	double indeterminateHumansAgainstNonInfectedVector = resultsForHumansAgainstNonInfectedVectors[2];
	double chronicHumansAgainstNonInfectedVector = resultsForHumansAgainstNonInfectedVectors[3];

	//ahora como los vectores no estan infectados, hay que calcular los que eventualmente
	//se contagien de los humanos ya infectados (ya sean agudos, indet. o cronicos)
	double txRateFromAcuteHumans = getRate(transmissionRateFromAcuteHumans, standardDeviationFromAcuteHumans);
	double txRateFromIndeterminateHumans = getRate(transmissionRateFromIndeterminateHumans, standardDeviationFromIndeterminateHumans);
	double txRateFromChronicHumans = getRate(transmissionRateFromChronicHumans, standardDeviationFromChronicHumans);
	newInfectedVectorsByHumans =
		floor(txRateFromAcuteHumans * acuteHumansAgainstNonInfectedVector) +
		floor(txRateFromIndeterminateHumans * indeterminateHumansAgainstNonInfectedVector) +
		floor(txRateFromChronicHumans * chronicHumansAgainstNonInfectedVector);
}

void DiseaseTransmission::transmissionForDogs(){
	//ya sabemos que vectores (infectados o no) picaran a los perros (en sus
	//respectivos estadios)... ahora calculamos las cantidades resultantes
	//despues de las eventuales transmisiones que se produzcan por las picaduras
	std::discrete_distribution<int> dogsDistribution({susceptibleDogs, infectedDogs});

	//primero para la combinacion con vector infectado... solo nos interesa saber
	//cuantos perros susceptibles fueron picados y calcular la probabilidad que
	//efectivamente se infecten
	std::map<int, int> resultsForDogsAgainstInfectedVectors;
	for(int n=0; n<infectedVectorsForDogs; ++n) {
			++resultsForDogsAgainstInfectedVectors[dogsDistribution(randomGenerator)];
	}

	double susceptibleDogsAgainstInfectedVector = resultsForDogsAgainstInfectedVectors[0];
	double infectedDogsAgainstInfectedVector = resultsForDogsAgainstInfectedVectors[1];
	double txRateOnSusceptibleDogs = getRate(transmissionRateOnSusceptibleDogs, standardDeviationOnSusceptibleDogs);

	newInfectedDogs = floor(txRateOnSusceptibleDogs * susceptibleDogsAgainstInfectedVector);

	//ahora calculamos la combinacion con vector no infectado... debemos reformular
	//la distribucion de perros, restando los ya utilizados en la combinacion anterior
	int susceptibleBis = susceptibleDogs - susceptibleDogsAgainstInfectedVector;
	int infectedBis = infectedDogs - infectedDogsAgainstInfectedVector;
	std::discrete_distribution<int> dogsDistribution2({susceptibleBis, infectedBis});

	std::map<int, int> resultsForDogsAgainstNonInfectedVectors;
	for(int n=0; n<nonInfectedVectorsForDogs; ++n) {
			++resultsForDogsAgainstNonInfectedVectors[dogsDistribution2(randomGenerator)];
	}

	double susceptibleDogsAgainstNonInfectedVector = resultsForDogsAgainstNonInfectedVectors[0];
	double infectedDogsAgainstNonInfectedVector = resultsForDogsAgainstNonInfectedVectors[1];

	//ahora como los vectores no estan infectados, hay que calcular los que eventualmente
	//se contagien de los perros ya infectados
	double txRateFromInfectedDogs = getRate(transmissionRateFromInfectedDogs, standardDeviationFromInfectedDogs);
	newInfectedVectorsByDogs = floor(txRateFromInfectedDogs * infectedDogsAgainstNonInfectedVector);
}

void DiseaseTransmission::transmitNewInfected(const CollectMessage &msg){
	//ya calculamos los nuevos resultados... los informamos a quienes corresponda
	sendOutput(msg.time(), transmitInfectedVectors, Real(newInfectedVectorsByHumans + newInfectedVectorsByDogs));
	sendOutput(msg.time(), transmitInfectedHumans, Real(newInfectedHumans));
	sendOutput(msg.time(), transmitInfectedDogs, Real(newInfectedDogs));
}

double DiseaseTransmission::getRate(double mean, double deviation){
	std::normal_distribution<double> rateDistribution(mean, deviation);
	return abs(rateDistribution(randomGenerator));
}
