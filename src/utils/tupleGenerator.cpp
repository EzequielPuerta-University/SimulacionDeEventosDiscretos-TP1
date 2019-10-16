#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "utils.h"
#include "tupleGenerator.h"

using namespace std;

TupleGenerator::TupleGenerator(const string &name) :
	Atomic(name),
	setByTuple(addInputPort("setByTuple")),
	out(addOutputPort("out")),
	frequency_time(0,0,10,0){
	size = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "size" ));
	frequency_time = ParallelMainSimulator::Instance().getParameter( description(), "frequency_time" );
	first = stod(ParallelMainSimulator::Instance().getParameter( description(), "first" ));
	second = stod(ParallelMainSimulator::Instance().getParameter( description(), "second" ));
	third = stod(ParallelMainSimulator::Instance().getParameter( description(), "third" ));
	fourth = stod(ParallelMainSimulator::Instance().getParameter( description(), "fourth" ));
	fifth = stod(ParallelMainSimulator::Instance().getParameter( description(), "fifth" ));
	sixth = stod(ParallelMainSimulator::Instance().getParameter( description(), "sixth" ));
}


Model &TupleGenerator::initFunction(){
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &TupleGenerator::externalFunction(const ExternalMessage &msg){
	if(msg.port() == setByTuple){
		if (size > 0){first = getValueFromTupleAt(msg,0);}
		if (size > 1){second = getValueFromTupleAt(msg,1);}
		if (size > 2){third = getValueFromTupleAt(msg,2);}
		if (size > 3){fourth = getValueFromTupleAt(msg,3);}
		if (size > 4){fifth = getValueFromTupleAt(msg,4);}
		if (size > 5){sixth = getValueFromTupleAt(msg,5);}
	}
	holdIn(AtomicState::active, nextChange());
	return *this;
}


Model &TupleGenerator::internalFunction(const InternalMessage &msg){
	holdIn(AtomicState::active, this->frequency_time);
	return *this;
}


Model &TupleGenerator::outputFunction(const CollectMessage &msg){
	switch (size) {
		case 1:
			sendOutput(msg.time(), out, asTuple(first));
			break;
		case 2:
			sendOutput(msg.time(), out, asTuple(first, second));
			break;
		case 3:
			sendOutput(msg.time(), out, asTuple(first, second, third));
			break;
		case 4:
			sendOutput(msg.time(), out, asTuple(first, second, third, fourth));
			break;
		case 5:
			sendOutput(msg.time(), out, asTuple(first, second, third, fourth, fifth));
			break;
		case 6:
			sendOutput(msg.time(), out, asTuple(first, second, third, fourth, fifth, sixth));
			break;
		default:
			break;
	}

	return *this;
}
