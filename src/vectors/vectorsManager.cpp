#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "vectorsManager.h"
#include "utils.h"

using namespace std;

VectorsManager::VectorsManager(const string &name) :
	Atomic(name),
	execute(addInputPort("execute")),
	getPopulation(addOutputPort("getPopulation")),
	population(addInputPort("population")),
	individualsInvolved(addOutputPort("individualsInvolved")),
	setInfections(addInputPort("setInfections")),
	applyNewInfections(addOutputPort("applyNewInfections")),
	infectionsApplied(addInputPort("infectionsApplied")),
	applyMigrations(addOutputPort("applyMigrations")),
	migrationsApplied(addInputPort("migrationsApplied")),
	applyBirths(addOutputPort("applyBirths")),
	birthsApplied(addInputPort("birthsApplied")),
	applyDeaths(addOutputPort("applyDeaths")),
	deathsApplied(addInputPort("deathsApplied")),
	finished(addOutputPort("finished")){
}


Model &VectorsManager::initFunction(){
	state = FINISH;
	passivate();
	return *this;
}


Model &VectorsManager::externalFunction(const ExternalMessage &msg){
	if(msg.port() == execute){
		vectorPercentage = getValueAsDoubleFrom(msg);
		//std::cout << "vectorPercentage: " << vectorPercentage << '\n';
		state = POPULATION_REQUEST;
	} else if(msg.port() == population){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		infectedPopulation = getValueFromTupleAt(msg,1);
		//std::cout << "susceptiblePopulation: " << susceptiblePopulation << '\n';
		//std::cout << "infectedPopulation: " << infectedPopulation << '\n';
		state = PREPARE_RESPONSE;
	} else if(msg.port() == setInfections){
		diseaseTransmissions = getValueFrom(msg);
		state = NEW_INFECTIONS;
	} else if(msg.port() == infectionsApplied){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		infectedPopulation = getValueFromTupleAt(msg,1);
		state = MIGRATIONS;
	} else if(msg.port() == migrationsApplied){
		susceptiblePopulation = getValueFromTupleAt(msg, 0);
		infectedPopulation = getValueFromTupleAt(msg, 1);
		state = BIRTHS;
	} else if(msg.port() == birthsApplied){
		susceptiblePopulation = getValueFromTupleAt(msg, 0);
		infectedPopulation = getValueFromTupleAt(msg, 1);
		state = DEATHS;
	} else if(msg.port() == deathsApplied){
		susceptiblePopulation = getValueFromTupleAt(msg, 0);
		infectedPopulation = getValueFromTupleAt(msg, 1);
		state = FINISH;
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &VectorsManager::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &VectorsManager::outputFunction(const CollectMessage &msg){
	switch (this->state) {
		case POPULATION_REQUEST:
			sendOutput(msg.time(), getPopulation, Real(1));
			break;
		case PREPARE_RESPONSE:
			prepareIndividualsInvolved(msg);
			break;
		case NEW_INFECTIONS:
			sendOutput(msg.time(), applyNewInfections, Real(diseaseTransmissions));
			break;
		case MIGRATIONS:
			sendOutput(msg.time(), applyMigrations, asTuple(susceptiblePopulation,infectedPopulation));
			break;
		case BIRTHS:
			sendOutput(msg.time(), applyBirths, asTuple(susceptiblePopulation,infectedPopulation));
			break;
		case DEATHS:
			sendOutput(msg.time(), applyDeaths, asTuple(susceptiblePopulation,infectedPopulation));
			break;
		case FINISH:
			sendOutput(msg.time(), finished, asTuple(susceptiblePopulation,infectedPopulation));
			break;
	}
	return *this;
}

void VectorsManager::prepareIndividualsInvolved(const CollectMessage &msg){
	std::discrete_distribution<int> populationDistribution({susceptiblePopulation, infectedPopulation});

	double amountOfVectors = round((susceptiblePopulation + infectedPopulation) * vectorPercentage);
	//std::cout << "amountOfVectors: " << amountOfVectors << '\n';
	std::map<int, int> results;
	for(int n=0; n<amountOfVectors; ++n) {
			++results[populationDistribution(randomGenerator)];
	}

	susceptibleIndividualsInvolved = results[0];
	infectedIndividualsInvolved = results[1];
	//std::cout << "susceptibleIndividualsInvolved: " << susceptibleIndividualsInvolved << '\n';
	//std::cout << "infectedIndividualsInvolved: " << infectedIndividualsInvolved << '\n';
	sendOutput(msg.time(), individualsInvolved, asTuple(susceptibleIndividualsInvolved, infectedIndividualsInvolved));
}
