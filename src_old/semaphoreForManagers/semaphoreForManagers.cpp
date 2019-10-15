#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "semaphoreForManagers.h"

using namespace std;

SemaphoreForManagers::SemaphoreForManagers(const string &name) :
	Atomic(name),
	vectorsPopulationComplete(addInputPort("vectorsPopulationComplete")),
	dogsPopulationComplete(addInputPort("dogsPopulationComplete")),
	humansPopulationComplete(addInputPort("humansPopulationComplete")),
	newDay(addOutputPort("newDay")),
	frequency_time(0,0,0,1){
}


Model &SemaphoreForManagers::initFunction(){
	isVectorsPopulationComplete = false;
	isDogsPopulationComplete = false;
	isHumansPopulationComplete = false;
	passivate();
	return *this;
}


Model &SemaphoreForManagers::externalFunction(const ExternalMessage &msg){
	if(msg.port() == vectorsPopulationComplete){
		isVectorsPopulationComplete = true;
	} else if(msg.port() == dogsPopulationComplete){
		isDogsPopulationComplete = true;
	} else if(msg.port() == humansPopulationComplete){
		isHumansPopulationComplete = true;
	}

	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &SemaphoreForManagers::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &SemaphoreForManagers::outputFunction(const CollectMessage &msg){
	if (isVectorsPopulationComplete && isDogsPopulationComplete && isHumansPopulationComplete){
		sendOutput(msg.time(), newDay, true);
	}
	return *this;
}
