#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "dogsManager.h"
#include "utils.h"

using namespace std;

DogsManager::DogsManager(const string &name) :
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


Model &DogsManager::initFunction(){
	state = FINISH;
	passivate();
	return *this;
}


Model &DogsManager::externalFunction(const ExternalMessage &msg){
	if(msg.port() == execute){
		individualsInvolvedTotalAmount = getValueFrom(msg);
		state = POPULATION_REQUEST;
	} else if(msg.port() == population){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		infectedPopulation = getValueFromTupleAt(msg,1);
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


Model &DogsManager::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &DogsManager::outputFunction(const CollectMessage &msg){
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

void DogsManager::prepareIndividualsInvolved(const CollectMessage &msg){
	int totalPopulation = susceptiblePopulation + infectedPopulation;
	double susceptibleProbability = susceptiblePopulation / totalPopulation;
	double infectedProbability = infectedPopulation / totalPopulation;
	std::discrete_distribution<int> populationDistribution({susceptibleProbability, infectedProbability});

	std::map<int, int> results;
	for(int n=0; n<individualsInvolvedTotalAmount; ++n) {
			++results[populationDistribution(randomGenerator)];
	}

	susceptibleIndividualsInvolved = results[0];
	infectedIndividualsInvolved = results[1];
	sendOutput(msg.time(), individualsInvolved, asTuple(susceptibleIndividualsInvolved, infectedIndividualsInvolved));
}
