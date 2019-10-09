#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "humansManager.h"

using namespace std;

HumansManager::HumansManager(const string &name) :
	Atomic(name),
	humansToBeBittenRequest(addInputPort("humansToBeBittenRequest")),
	susceptibleResponse(addInputPort("susceptibleResponse")),
	acuteResponse(addInputPort("acuteResponse")),
	indeterminateResponse(addInputPort("indeterminateResponse")),
	chronicResponse(addInputPort("chronicResponse")),
	newInfections(addInputPort("newInfections")),
	curesApplied(addInputPort("curesApplied")),
	infectionsApplied(addInputPort("infectionsApplied")),
	migrationsApplied(addInputPort("migrationsApplied")),
	birthsApplied(addInputPort("birthsApplied")),
	deathsApplied(addInputPort("deathsApplied")),
	humansResponse(addOutputPort("humansResponse")),
	susceptibleRequest(addOutputPort("susceptibleRequest")),
	acuteRequest(addOutputPort("acuteRequest")),
	indeterminateRequest(addOutputPort("indeterminateRequest")),
	chronicRequest(addOutputPort("chronicRequest")),
	applyCures(addOutputPort("applyCures")),
	applyNewInfections(addOutputPort("applyNewInfections")),
	applyMigrations(addOutputPort("applyMigrations")),
	applyBirths(addOutputPort("applyBirths")),
	applyDeaths(addOutputPort("applyDeaths")),
	dayFinished(addOutputPort("dayFinished")),
	frequency_time(0,0,0,1){
}


Model &HumansManager::initFunction(){
	state = FINISH;
	passivate();
	return *this;
}


Model &HumansManager::externalFunction(const ExternalMessage &msg){
	if(msg.port() == humansToBeBittenRequest){
		humansToBeBittenAmount = (Real::from_value(msg.value())).value();
		state = CURES;
	} else if(msg.port() == curesApplied){
		state = SUSCEPTIBLE_REQUEST;
	}  else if(msg.port() == susceptibleResponse){
		susceptiblePopulation = (Real::from_value(msg.value())).value();
		state = ACUTE_REQUEST;
	} else if(msg.port() == acuteResponse){
		acutePopulation = (Real::from_value(msg.value())).value();
		state = INDETERMINATE_REQUEST;
	} else if(msg.port() == indeterminateResponse){
		indeterminatePopulation = (Real::from_value(msg.value())).value();
		state = CHRONIC_REQUEST;
	} else if(msg.port() == chronicResponse){
		chronicPopulation = (Real::from_value(msg.value())).value();
		state = PREPARE_RESPONSE;
	} else if(msg.port() == newInfections){
		diseaseTransmissions = (Real::from_value(msg.value())).value();
		state = NEW_INFECTIONS;
	} else if(msg.port() == infectionsApplied){
		susceptiblePopulation = susceptiblePopulation - diseaseTransmissions;
		acutePopulation = acutePopulation + diseaseTransmissions;
		state = MIGRATIONS;
	} else if(msg.port() == migrationsApplied){
		susceptiblePopulation = getDoubleFromRealTupleAt(msg, 0);
		indeterminatePopulation = getDoubleFromRealTupleAt(msg, 1);
		chronicPopulation = getDoubleFromRealTupleAt(msg, 2);
		state = BIRTHS;
	} else if(msg.port() == birthsApplied){
		susceptiblePopulation = getDoubleFromRealTupleAt(msg, 0);
		acutePopulation = getDoubleFromRealTupleAt(msg, 1);
		state = DEATHS;
	} else if(msg.port() == deathsApplied){
		susceptiblePopulation = getDoubleFromRealTupleAt(msg, 0);
		acutePopulation = getDoubleFromRealTupleAt(msg, 1);
		indeterminatePopulation = getDoubleFromRealTupleAt(msg, 2);
		chronicPopulation = getDoubleFromRealTupleAt(msg, 3);
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
		currentPopulation = {Real(susceptiblePopulation), Real(acutePopulation), Real(indeterminatePopulation), Real(chronicPopulation)};

		case CURES:
			sendOutput(msg.time(), applyCures, Real(1));
			break;
		case SUSCEPTIBLE_REQUEST:
			sendOutput(msg.time(), susceptibleRequest, Real(1));
			break;
		case ACUTE_REQUEST:
			sendOutput(msg.time(), acuteRequest, Real(1));
			break;
		case INDETERMINATE_REQUEST:
			sendOutput(msg.time(), indeterminateRequest, Real(1));
			break;
		case CHRONIC_REQUEST:
			sendOutput(msg.time(), chronicRequest, Real(1));
			break;
		case PREPARE_RESPONSE:
			prepareHumansToBeBitten(msg);
			break;
		case NEW_INFECTIONS:
			sendOutput(msg.time(), applyNewInfections, Real(diseaseTransmissions));
			break;
		case MIGRATIONS:
			sendOutput(msg.time(), applyMigrations, currentPopulation);
			break;
		case BIRTHS:
			sendOutput(msg.time(), applyBirths, currentPopulation);
			break;
		case DEATHS:
			sendOutput(msg.time(), applyDeaths, currentPopulation);
			break;
		case FINISH:
			sendOutput(msg.time(), dayFinished, currentPopulation);
			break;
	}
	return *this;
}

void HumansManager::prepareHumansToBeBitten(const CollectMessage &msg){
	double humansPopulation = susceptiblePopulation+acutePopulation+indeterminatePopulation+chronicPopulation;
	double susceptibleP = susceptiblePopulation / humansPopulation;
	double acuteP = acutePopulation / humansPopulation;
	double indeterminateP = indeterminatePopulation / humansPopulation;
	double chronicP = chronicPopulation / humansPopulation;
	std::discrete_distribution<int> humansDistribution({susceptibleP, acuteP, indeterminateP, chronicP});

	std::map<int, int> results;
	for(int n=0; n<humansToBeBittenAmount; ++n) {
			++results[humansDistribution(randomGenerator)];
	}

	susceptibleHumansToBeBitten = results[0];
	acuteHumansToBeBitten = results[1];
	indeterminateHumansToBeBitten = results[2];
	chronicHumansToBeBitten = results[3];
	Tuple<Real> humansToBeBitten{
		Real(susceptibleHumansToBeBitten),
		Real(acuteHumansToBeBitten),
		Real(indeterminateHumansToBeBitten),
		Real(chronicHumansToBeBitten)};
	sendOutput(msg.time(), humansResponse, humansToBeBitten);
}

double HumansManager::getDoubleFromRealTupleAt(const ExternalMessage &msg, int index){
	return (Tuple<Real>::from_value(msg.value())[index]).value();
}
