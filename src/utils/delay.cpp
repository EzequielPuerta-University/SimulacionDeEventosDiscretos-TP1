#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "delay.h"
#include "utils.h"

using namespace std;

Delay::Delay(const string &name) :
	Atomic(name),
	in(addInputPort("in")),
	out(addOutputPort("out")),
	delay_time(0,0,1,0){
	delay_time = ParallelMainSimulator::Instance().getParameter( description(), "delay_time" );
}


Model &Delay::initFunction(){
	passivate();
	return *this;
}


Model &Delay::externalFunction(const ExternalMessage &msg){
	if(msg.port() == in){
		receivedValue = getValueFrom(msg);
	}
	holdIn(AtomicState::active, this->delay_time);
	return *this;
}


Model &Delay::internalFunction(const InternalMessage &msg){
	passivate();
	return *this;
}


Model &Delay::outputFunction(const CollectMessage &msg){
	sendOutput(msg.time(), out, Real(receivedValue));
	return *this;
}
