#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "vectorsManager.h"

using namespace std;

VectorsManager::VectorsManager(const string &name) :
	Atomic(name),
	vectorRequestPercentage(addInputPort("vectorRequestPercentage")),
	susceptibleResponse(addInputPort("susceptibleResponse")),
	infectedResponse(addInputPort("infectedResponse")),
	newInfections(addInputPort("newInfections")),
	infectionsApplied(addInputPort("infectionsApplied")),
	migrationsApplied(addInputPort("migrationsApplied")),
	birthsApplied(addInputPort("birthsApplied")),
	deathsApplied(addInputPort("deathsApplied")),
	vectorResponse(addOutputPort("vectorResponse")),
	susceptibleRequest(addOutputPort("susceptibleRequest")),
	infectedRequest(addOutputPort("infectedRequest")),
	applyNewInfections(addOutputPort("applyNewInfections")),
	applyMigrations(addOutputPort("applyMigrations")),
	applyBirths(addOutputPort("applyBirths")),
	applyDeaths(addOutputPort("applyDeaths")),
	dayFinished(addOutputPort("dayFinished")),
	frequency_time(0,0,0,1){
}


Model &VectorsManager::initFunction(){
	state = FINISH;
	passivate();
	return *this;
}


Model &VectorsManager::externalFunction(const ExternalMessage &msg){
	if(msg.port() == vectorRequestPercentage){
		vectorPercentage = (Real::from_value(msg.value())).value();
		state = SUSCEPTIBLE_REQUEST;
	} else if(msg.port() == susceptibleResponse){
		susceptiblePopulation = (Real::from_value(msg.value())).value();
		state = INFECTED_REQUEST;
	} else if(msg.port() == infectedResponse){
		infectedPopulation = (Real::from_value(msg.value())).value();
		state = PREPARE_RESPONSE;
	} else if(msg.port() == newInfections){
		diseaseTransmissions = (Real::from_value(msg.value())).value();
		state = NEW_INFECTIONS;
	} else if(msg.port() == infectionsApplied){
		susceptiblePopulation = susceptiblePopulation - diseaseTransmissions;
		infectedPopulation = infectedPopulation + diseaseTransmissions;
		state = MIGRATIONS;
	} else if(msg.port() == migrationsApplied){
		susceptiblePopulation = getDoubleFromRealTupleAt(msg, 0);
		infectedPopulation = getDoubleFromRealTupleAt(msg, 1);
		state = BIRTHS;
	} else if(msg.port() == birthsApplied){
		susceptiblePopulation = getDoubleFromRealTupleAt(msg, 0);
		infectedPopulation = getDoubleFromRealTupleAt(msg, 1);
		state = DEATHS;
	} else if(msg.port() == deathsApplied){
		susceptiblePopulation = getDoubleFromRealTupleAt(msg, 0);
		infectedPopulation = getDoubleFromRealTupleAt(msg, 1);
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
		currentPopulation = {Real(susceptiblePopulation), Real(infectedPopulation)};

		case SUSCEPTIBLE_REQUEST:
			sendOutput(msg.time(), susceptibleRequest, Real(1));
			break;
		case INFECTED_REQUEST:
			sendOutput(msg.time(), infectedRequest, Real(1));
			break;
		case PREPARE_RESPONSE:
			prepareVectorsToFeed(msg);
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

void VectorsManager::prepareVectorsToFeed(const CollectMessage &msg){
	double susceptibleProbability = susceptiblePopulation / (susceptiblePopulation+infectedPopulation);
	double infectedProbability = infectedPopulation / (susceptiblePopulation+infectedPopulation);
	std::discrete_distribution<int> vectorDistribution({susceptibleProbability, infectedProbability});

	double amountOfVectors = round((susceptiblePopulation+infectedPopulation) * vectorPercentage);

	std::map<int, int> results;
	for(int n=0; n<amountOfVectors; ++n) {
			++results[vectorDistribution(randomGenerator)];
	}

	susceptibleVectorsToFeed = results[0];
	infectedVectorsToFeed = results[1];
	Tuple<Real> vectorsToFeed{Real(susceptibleVectorsToFeed), Real(infectedVectorsToFeed)};
	sendOutput(msg.time(), vectorResponse, vectorsToFeed);
}

double VectorsManager::getDoubleFromRealTupleAt(const ExternalMessage &msg, int index){
	return (Tuple<Real>::from_value(msg.value())[index]).value();
}
