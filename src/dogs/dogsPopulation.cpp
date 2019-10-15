#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "dogsPopulation.h"
#include "utils.h"

using namespace std;

DogsPopulation::DogsPopulation(const string &name) :
	Atomic(name),
	setBirths(addInputPort("setBirths")),
	setDeaths(addInputPort("setDeaths")),
	setMigrations(addInputPort("setMigrations")),
	setInfections(addInputPort("setInfections")),
	infectionsApplied(addOutputPort("infectionsApplied")),
	getPopulation(addInputPort("getPopulation")),
	queryPopulation(addOutputPort("queryPopulation")){
	susceptiblePopulation = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "susceptiblePopulation" ));
	infectedPopulation = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "infectedPopulation" ));
}


Model &DogsPopulation::initFunction(){
	state = PASSIVE;
	passivate();
	return *this;
}


Model &DogsPopulation::externalFunction(const ExternalMessage &msg){
	if(msg.port() == getPopulation){
			state = POPULATION_REQUEST;
	} else if(msg.port() == setInfections){
			lastInfections = getValueFrom(msg);
			susceptiblePopulation = susceptiblePopulation - lastInfections;
			infectedPopulation = infectedPopulation + lastInfections;
			state = INFECTIONS_APPLIED;
	} else if(msg.port() == setMigrations){
			susceptibleImmigrants = getValueFromTupleAt(msg,0);
			susceptibleEmmigrants = getValueFromTupleAt(msg,1);
			infectedImmigrants = getValueFromTupleAt(msg,2);
			infectedEmmigrants = getValueFromTupleAt(msg,3);
			susceptiblePopulation = susceptiblePopulation - susceptibleEmmigrants + susceptibleImmigrants;
			infectedPopulation = infectedPopulation - infectedEmmigrants + infectedImmigrants;
	} else if(msg.port() == setBirths){
			susceptiblePopulation = susceptiblePopulation + getValueFromTupleAt(msg,0);
			infectedPopulation = infectedPopulation + getValueFromTupleAt(msg,1);
	} else if (msg.port() == setDeaths){
			susceptiblePopulation = susceptiblePopulation - getValueFromTupleAt(msg,0);
			infectedPopulation = infectedPopulation - getValueFromTupleAt(msg,1);
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &DogsPopulation::internalFunction(const InternalMessage &msg){
	state = PASSIVE;
	passivate();
	return *this;
}


Model &DogsPopulation::outputFunction(const CollectMessage &msg){
	switch (this->state) {
		case POPULATION_REQUEST:
			sendOutput(msg.time(), queryPopulation, asTuple(susceptiblePopulation, infectedPopulation));
			break;
		case INFECTIONS_APPLIED:
			sendOutput(msg.time(), infectionsApplied, asTuple(susceptiblePopulation, infectedPopulation));
			break;
		default:
			break;
	}
	return *this;
}
