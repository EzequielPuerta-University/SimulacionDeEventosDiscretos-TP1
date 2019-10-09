#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "infectedVectors.h"

using namespace std;

InfectedVectors::InfectedVectors(const string &name) :
	Atomic(name),
	births(addInputPort("births")),
	migrations(addInputPort("migrations")),
	deaths(addInputPort("deaths")),
	populationRequest(addInputPort("populationRequest")),
	currentPopulation(addOutputPort("currentPopulation")),
	frequency_time(0,0,0,1){
	population = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "population" ));
}


Model &InfectedVectors::initFunction(){
	state = PASSIVE;
	passivate();
	return *this;
}


Model &InfectedVectors::externalFunction(const ExternalMessage &msg){
	if(msg.port() == populationRequest){
		state = POPULATION_REQUEST;
		holdIn(AtomicState::active, VTime::Zero);
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


Model &InfectedVectors::internalFunction(const InternalMessage &msg){
	state = PASSIVE;
	passivate();
	return *this ;
}


Model &InfectedVectors::outputFunction(const CollectMessage &msg){
	if(POPULATION_REQUEST){
		sendOutput(msg.time(), currentPopulation, Real(population));
	}
	return *this;
}
