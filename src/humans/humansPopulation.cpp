#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "humansPopulation.h"
#include "utils.h"

using namespace std;

HumansPopulation::HumansPopulation(const string &name) :
	Atomic(name),
	setBirths(addInputPort("setBirths")),
	setDeaths(addInputPort("setDeaths")),
	setMigrations(addInputPort("setMigrations")),
	setInfections(addInputPort("setInfections")),
	infectionsApplied(addOutputPort("infectionsApplied")),
	getPopulation(addInputPort("getPopulation")),
	queryPopulation(addOutputPort("queryPopulation")){
	susceptiblePopulation = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "susceptiblePopulation" ));
	acutePopulation = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "acutePopulation" ));
	indeterminatePopulation = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "indeterminatePopulation" ));
	chronicPopulation = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "chronicPopulation" ));
}


Model &HumansPopulation::initFunction(){
	acuteCureRate = 0.000667;
	acuteCureDeviation = 0.000200;
	indeterminateCureRate = 0.000018;
	indeterminateCureDeviation = 0.000007;

	// acuteBloodTransmissionRate = 0.000002;
	// acuteBloodTransmissionDeviation = 0.000001;
	// indeterminateBloodTransmissionRate = 0.000008;
	// indeterminateBloodTransmissionDeviation = 0.000002;
	// chronicBloodTransmissionRate = 0.000001;
	// chronicBloodTransmissionDeviation = 0.0000009;

	acuteProgressionRate = 0.015833;
	acuteProgressionDeviation = 0.00475;
	indeterminateProgressionRate = 0.000096;
	indeterminateProgressionDeviation = 0.000041;
	state = PASSIVE;
	passivate();
	return *this;
}


Model &HumansPopulation::externalFunction(const ExternalMessage &msg){
	if(msg.port() == getPopulation){
			applyCures();
			applyDiseaseProgression();
			state = POPULATION_REQUEST;
	} else if(msg.port() == setInfections){
			lastInfections = getValueFrom(msg);
			susceptiblePopulation = susceptiblePopulation - lastInfections;
			acutePopulation = acutePopulation + lastInfections;
			state = INFECTIONS_APPLIED;
	} else if(msg.port() == setMigrations){
			susceptibleImmigrants = getValueFromTupleAt(msg,0);
			susceptibleEmmigrants = getValueFromTupleAt(msg,1);
			acuteImmigrants = getValueFromTupleAt(msg,2);
			acuteEmmigrants = getValueFromTupleAt(msg,3);
			indeterminateImmigrants = getValueFromTupleAt(msg,4);
			indeterminateEmmigrants = getValueFromTupleAt(msg,5);
			chronicImmigrants = getValueFromTupleAt(msg,6);
			chronicEmmigrants = getValueFromTupleAt(msg,7);

			susceptiblePopulation = susceptiblePopulation - susceptibleEmmigrants + susceptibleImmigrants;
			acutePopulation = acutePopulation - acuteEmmigrants + acuteImmigrants;
			indeterminatePopulation = indeterminatePopulation - indeterminateEmmigrants + indeterminateImmigrants;
			chronicPopulation = chronicPopulation - chronicEmmigrants + chronicImmigrants;
	} else if(msg.port() == setBirths){
			susceptiblePopulation = susceptiblePopulation + getValueFromTupleAt(msg,0);
			acutePopulation = acutePopulation + getValueFromTupleAt(msg,1);
			indeterminatePopulation = indeterminatePopulation + getValueFromTupleAt(msg,3);
			chronicPopulation = chronicPopulation + getValueFromTupleAt(msg,4);
	} else if (msg.port() == setDeaths){
			susceptiblePopulation = susceptiblePopulation + getValueFromTupleAt(msg,0);
			acutePopulation = acutePopulation + getValueFromTupleAt(msg,1);
			indeterminatePopulation = indeterminatePopulation + getValueFromTupleAt(msg,3);
			chronicPopulation = chronicPopulation + getValueFromTupleAt(msg,4);
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &HumansPopulation::internalFunction(const InternalMessage &msg){
	state = PASSIVE;
	passivate();
	return *this;
}


Model &HumansPopulation::outputFunction(const CollectMessage &msg){
	switch (this->state) {
		case POPULATION_REQUEST:
			sendOutput(msg.time(), queryPopulation, asTuple(susceptiblePopulation, acutePopulation, indeterminatePopulation, chronicPopulation));
			break;
		case INFECTIONS_APPLIED:
			sendOutput(msg.time(), infectionsApplied, asTuple(susceptiblePopulation, acutePopulation, indeterminatePopulation, chronicPopulation));
			break;
		default:
			break;
	}
	return *this;
}

double HumansPopulation::getRate(double mean, double deviation){
	std::normal_distribution<double> rateDistribution(mean, deviation);
	return abs(rateDistribution(randomGenerator));
}

void HumansPopulation::applyCures(){
	int acuteRecovered = getRate(acuteCureRate, acuteCureDeviation) * acutePopulation;
	int indeterminateRecovered = getRate(indeterminateCureRate, indeterminateCureDeviation) * indeterminatePopulation;
	acutePopulation = acutePopulation - acuteRecovered;
	indeterminatePopulation = indeterminatePopulation - indeterminateRecovered;
	susceptiblePopulation = susceptiblePopulation + acuteRecovered + indeterminateRecovered;
}

void HumansPopulation::applyDiseaseProgression(){
	int acuteAggravated = getRate(acuteProgressionRate, acuteProgressionDeviation) * acutePopulation;
	int indeterminateAggravated = getRate(indeterminateProgressionRate, indeterminateProgressionDeviation) * indeterminatePopulation;
	acutePopulation = acutePopulation - acuteAggravated;
	indeterminatePopulation = indeterminatePopulation - indeterminateAggravated + acuteAggravated;
	chronicPopulation = chronicPopulation + indeterminateAggravated;
}
