#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "susceptibleVectors.h"

using namespace std;

SusceptibleVectors::SusceptibleVectors(const string &name) :
	Atomic(name),
	births(addInputPort("births")),
	migrations(addInputPort("migrations")),
	infected(addInputPort("infected")),
	deaths(addInputPort("deaths")),
	populationRequest(addInputPort("populationRequest")),
	currentPopulation(addOutputPort("currentPopulation")),
	infectionsApplied(addOutputPort("infectionsApplied")),
	frequency_time(0,0,0,1){
	population = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "population" ));
}


Model &SusceptibleVectors::initFunction(){
	state = PASSIVE;
	passivate();
	return *this;
}


Model &SusceptibleVectors::externalFunction(const ExternalMessage &msg){
	if(msg.port() == populationRequest){
		state = POPULATION_REQUEST;
		holdIn(AtomicState::active, VTime::Zero);
	} else if(msg.port() == infected){
		lastInfections = (Real::from_value(msg.value())).value();
		population = population - lastInfections;
		passivate();
	} else if(msg.port() == migrations){
		immigrants = (Tuple<Real>::from_value(msg.value())[0]).value();
		emmigrants = (Tuple<Real>::from_value(msg.value())[1]).value();
		population = population - emmigrants + immigrants;
		passivate();
	} else if(msg.port() == births){
		population = population + (Real::from_value(msg.value())).value();
		passivate();
	} else if(msg.port() == deaths){
		population = population - (Real::from_value(msg.value())).value();
		passivate();
	}
	return *this;
}


Model &SusceptibleVectors::internalFunction(const InternalMessage &msg){
	state = PASSIVE;
	passivate();
	return *this;
}


Model &SusceptibleVectors::outputFunction(const CollectMessage &msg){
	switch (this->state) {
		case POPULATION_REQUEST:
			sendOutput(msg.time(), currentPopulation, Real(population));
			break;
		case INFECTIONS_APPLIED:
			sendOutput(msg.time(), infectionsApplied, Real(lastInfections));
			break;
	}
	return *this;
}
