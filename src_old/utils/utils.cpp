#include "utils.h"
#include "atomic.h"


void wakeUp(){
	holdIn(AtomicState::active, VTime::Zero);
}

int getIntFromTupleAt(const ExternalMessage &msg, int index){
	return (Tuple<int>::from_value(msg.value())[index]).value();
}
