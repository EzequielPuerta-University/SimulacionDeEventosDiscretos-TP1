#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "../utils/utils.h"
#include "dogsPopulation.h"

using namespace std;

DogsPopulation::DogsPopulation(const string &name) :
	Atomic(name),
	setBirths(addInputPort("setBirths")),
	setMigrations(addInputPort("setMigrations")),
	setInfections(addInputPort("setInfections")),
	setDeaths(addInputPort("setDeaths")),
	infectionsApplied(addOutputPort("infectionsApplied")),
	getPopulation(addInputPort("getPopulation")),
	queryPopulation(addOutputPort("queryPopulation")){
	population = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "population" ));
}


Model &DogsPopulation::initFunction(){
	state = PASSIVE;
	passivate();
	return *this;
}


Model &DogsPopulation::externalFunction(const ExternalMessage &msg){
	switch (msg.port()) {
		case getPopulation:
			state = POPULATION_REQUEST;
			wakeUp();
			break;
		case setInfections:
			lastInfections = msg.value();
			susceptiblePopulation = susceptiblePopulation - lastInfections;
			infectedPopulation = infectedPopulation + lastInfections;
			state = INFECTIONS_APPLIED;
			passivate();
			break;
		case setMigrations:
			susceptibleImmigrants = getIntFromTupleAt(msg,0);
			susceptibleEmmigrants = getIntFromTupleAt(msg,1);
			infectedImmigrants = getIntFromTupleAt(msg,2);
			infectedEmmigrants = getIntFromTupleAt(msg,3);
			susceptiblePopulation = susceptiblePopulation - susceptibleEmmigrants + susceptibleImmigrants;
			infectedPopulation = infectedPopulation - infectedEmmigrants + infectedImmigrants;
			passivate();
			break;
		case setBirths:
			susceptiblePopulation = susceptiblePopulation + getIntFromTupleAt(msg,0);
			infectedPopulation = infectedPopulation + getIntFromTupleAt(msg,1);
			passivate();
			break;
		case setDeaths:
			susceptiblePopulation = susceptiblePopulation - getIntFromTupleAt(msg,0);
			infectedPopulation = infectedPopulation - getIntFromTupleAt(msg,1);
			passivate();
			break;
	}
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
			Tuple<int> population{susceptiblePopulation, infectedPopulation};
			sendOutput(msg.time(), queryPopulation, population);
			break;
		case INFECTIONS_APPLIED:
			sendOutput(msg.time(), infectionsApplied, lastInfections);
			break;
	}
	return *this;
}
