#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "dogDeaths.h"

using namespace std;

DogDeaths::DogDeaths(const string &name) :
	Atomic(name),
	currentSusceptibleDeaths(addInputPort("currentSusceptibleDeaths")),
	currentInfectedDeaths(addInputPort("currentInfectedDeaths")),
	frequency_time(0,0,0,1){
}


Model &DogDeaths::initFunction(){
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &DogDeaths::externalFunction(const ExternalMessage &msg){
	if(msg.port() == currentInfectedDeaths){
		infectedDeaths = infectedDeaths + (Real::from_value(msg.value())).value();
	} else if(msg.port() == currentSusceptibleDeaths){
		susceptibleDeaths = susceptibleDeaths + (Real::from_value(msg.value())).value();
	}
	holdIn(AtomicState::active, nextChange());
	return *this;
}


Model &DogDeaths::internalFunction(const InternalMessage &msg){
	holdIn(AtomicState::active, this->frequency_time);
	return *this ;
}


Model &DogDeaths::outputFunction(const CollectMessage &msg){
	return *this;
}
