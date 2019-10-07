#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "humans.h"

using namespace std;


#define VERBOSE true

#define PRINT_TIMES(f) {\
	VTime timeleft = nextChange();\
	VTime elapsed  = msg.time() - lastChange();\
	VTime sigma    = elapsed + timeleft;\
	cout << f << "@" << msg.time() <<\
		" - timeleft: " << timeleft <<\
		" - elapsed: " << elapsed <<\
		" - sigma: " << sigma << endl;\
}


Humans::Humans(const string &name) :
	Atomic(name),
	births(addInputPort("births")),
	deaths(addOutputPort("deaths")),
	frequency_time(0,0,0,1),
	infectedAmount(1),
	totalAmount(100),
	dist(0,100),
	rng(random_device()()){
	totalAmount = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "totalAmount" ));
	infectedAmount = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "infectedAmount" ));
}


Model &Humans::initFunction(){
	holdIn(AtomicState::active, this->frequency_time);
	return *this;
}


Model &Humans::externalFunction(const ExternalMessage &msg){
#if VERBOSE
	PRINT_TIMES("dext");
#endif

	if(msg.port() == births){
		holdIn(AtomicState::active, nextChange());
	}

	return *this;
}


Model &Humans::internalFunction(const InternalMessage &msg){
#if VERBOSE
	PRINT_TIMES("dint");
#endif

	holdIn(AtomicState::active, this->frequency_time);

	return *this ;
}


Model &Humans::outputFunction(const CollectMessage &msg){
	auto random_deaths = this->dist(this->rng);
	Tuple<Real> deaths_value{Real(random_deaths), 0, 1};
	sendOutput(msg.time(), deaths, deaths_value);
	return *this ;
}
