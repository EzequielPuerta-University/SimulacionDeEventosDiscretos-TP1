#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "dogBirths.h"

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


DogBirths::DogBirths(const string &name) :
	Atomic(name),
	currentInfectedPopulation(addInputPort("currentInfectedPopulation")),
	currentSusceptiblePopulation(addInputPort("currentSusceptiblePopulation")),
	infectedBirths(addOutputPort("infectedBirths")),
	nonInfectedBirths(addOutputPort("nonInfectedBirths")),
	frequency_time(0,0,0,1),
	susceptibleMotherBirthRate(0.001002), //b_{DS}
	infectedMotherBirthRate(0.001002), //b_{DI}
	congenitalTransmissionProbability(0.10), //q_{D}
	randomGenerator(random_device()()),
	susceptiblePopulation(10),
	infectedPopulation(4){
	susceptiblePopulation = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "susceptiblePopulation" ));
	infectedPopulation = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "infectedPopulation" ));
}


Model &DogBirths::initFunction(){
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &DogBirths::externalFunction(const ExternalMessage &msg){
#if VERBOSE
	PRINT_TIMES("dext");
#endif

	if(msg.port() == currentInfectedPopulation){
		this->infectedPopulation = Real::from_value(msg.value());
	} else if(msg.port() == currentSusceptiblePopulation){
		this->susceptiblePopulation = Real::from_value(msg.value());
	}
	holdIn(AtomicState::active, nextChange());

	return *this;
}


Model &DogBirths::internalFunction(const InternalMessage &msg){
#if VERBOSE
	PRINT_TIMES("dint");
#endif

	holdIn(AtomicState::active, this->frequency_time);

	return *this ;
}


Model &DogBirths::outputFunction(const CollectMessage &msg){
	int nonInfectedMothers = static_cast<int>(susceptibleMotherBirthRate * susceptiblePopulation);
	int infectedMothers = static_cast<int>(infectedMotherBirthRate * infectedPopulation);
	std::binomial_distribution<int> binomial(infectedMothers, congenitalTransmissionProbability);
	int infectedBirths = binomial(randomGenerator);
	int nonInfectedBirths = nonInfectedMothers + (infectedMothers - infectedBirths);

	Tuple<Real> infectedValue{Real(infectedBirths), 0, 1};
	Tuple<Real> nonInfectedValue{Real(nonInfectedBirths), 0, 1};
	sendOutput(msg.time(), infectedValue, infectedBirths);
	sendOutput(msg.time(), nonInfectedValue, nonInfectedBirths);

	return *this ;
}
