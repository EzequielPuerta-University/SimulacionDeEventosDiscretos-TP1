#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "humansManager.h"
#include "utils.h"

using namespace std;

HumansManager::HumansManager(const string &name) :
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


Model &HumansManager::initFunction(){
	state = FINISH;
	passivate();
	return *this;
}


Model &HumansManager::externalFunction(const ExternalMessage &msg){
	if(msg.port() == execute){
		individualsInvolvedTotalAmount = getValueFrom(msg);
		state = POPULATION_REQUEST;
	} else if(msg.port() == population){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		acutePopulation = getValueFromTupleAt(msg,1);
		indeterminatePopulation = getValueFromTupleAt(msg,2);
		chronicPopulation = getValueFromTupleAt(msg,3);
		state = PREPARE_RESPONSE;
	} else if(msg.port() == setInfections){
		diseaseTransmissions = getValueFrom(msg);
		state = NEW_INFECTIONS;
	} else if(msg.port() == infectionsApplied){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		acutePopulation = getValueFromTupleAt(msg,1);
		indeterminatePopulation = getValueFromTupleAt(msg,2);
		chronicPopulation = getValueFromTupleAt(msg,3);
		state = MIGRATIONS;
	} else if(msg.port() == migrationsApplied){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		acutePopulation = getValueFromTupleAt(msg,1);
		indeterminatePopulation = getValueFromTupleAt(msg,2);
		chronicPopulation = getValueFromTupleAt(msg,3);
		state = BIRTHS;
	} else if(msg.port() == birthsApplied){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		acutePopulation = getValueFromTupleAt(msg,1);
		indeterminatePopulation = getValueFromTupleAt(msg,2);
		chronicPopulation = getValueFromTupleAt(msg,3);
		state = DEATHS;
	} else if(msg.port() == deathsApplied){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		acutePopulation = getValueFromTupleAt(msg,1);
		indeterminatePopulation = getValueFromTupleAt(msg,2);
		chronicPopulation = getValueFromTupleAt(msg,3);
		state = FINISH;
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &HumansManager::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &HumansManager::outputFunction(const CollectMessage &msg){
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
			sendOutput(msg.time(), applyMigrations, asTuple(susceptiblePopulation, acutePopulation, indeterminatePopulation, chronicPopulation));
			break;
		case BIRTHS:
			sendOutput(msg.time(), applyBirths, asTuple(susceptiblePopulation, acutePopulation, indeterminatePopulation, chronicPopulation));
			break;
		case DEATHS:
			sendOutput(msg.time(), applyDeaths, asTuple(susceptiblePopulation, acutePopulation, indeterminatePopulation, chronicPopulation));
			break;
		case FINISH:
			sendOutput(msg.time(), finished, asTuple(susceptiblePopulation, acutePopulation, indeterminatePopulation, chronicPopulation));
			break;
	}
	return *this;
}

void HumansManager::prepareIndividualsInvolved(const CollectMessage &msg){
	std::discrete_distribution<int> populationDistribution({susceptiblePopulation, acutePopulation, indeterminatePopulation, chronicPopulation});

	std::map<int, int> results;
	for(int n=0; n<individualsInvolvedTotalAmount; ++n) {
			++results[populationDistribution(randomGenerator)];
	}

	susceptibleIndividualsInvolved = results[0];
	acuteIndividualsInvolved = results[1];
	indeterminateIndividualsInvolved = results[2];
	chronicIndividualsInvolved = results[3];
	sendOutput(msg.time(), individualsInvolved, asTuple(susceptibleIndividualsInvolved, acuteIndividualsInvolved, indeterminateIndividualsInvolved, chronicIndividualsInvolved));
}
