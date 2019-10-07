#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "vectorBirths.h"

using namespace std;

VectorBirths::VectorBirths(const string &name) :
	Atomic(name),
	currentInfectedPopulation(addInputPort("currentInfectedPopulation")),
	currentSusceptiblePopulation(addInputPort("currentSusceptiblePopulation")),
	infectedBirths(addOutputPort("infectedBirths")),
	nonInfectedBirths(addOutputPort("nonInfectedBirths")),
	frequency_time(0,0,0,1){
	susceptiblePopulation = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "susceptiblePopulation" ));
	infectedPopulation = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "infectedPopulation" ));
}


Model &VectorBirths::initFunction(){
	motherBirthRate = 0.012500;
	motherStandardDeviation = 0.00375;
	congenitalTransmissionProbability = 1;
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &VectorBirths::externalFunction(const ExternalMessage &msg){
	if(msg.port() == currentInfectedPopulation){
		infectedPopulation = (Real::from_value(msg.value())).value();
	} else if(msg.port() == currentSusceptiblePopulation){
		susceptiblePopulation = (Real::from_value(msg.value())).value();
	}
	holdIn(AtomicState::active, nextChange());
	return *this;
}


Model &VectorBirths::internalFunction(const InternalMessage &msg){
	holdIn(AtomicState::active, this->frequency_time);
	return *this ;
}


Model &VectorBirths::outputFunction(const CollectMessage &msg){
	std::normal_distribution<double> birthRateDistribution(motherBirthRate, motherStandardDeviation);
	double birthRate = abs(birthRateDistribution(randomGenerator));

	int nonInfectedMothers = static_cast<int>(birthRate * susceptiblePopulation);
	int infectedMothers = static_cast<int>(birthRate * infectedPopulation);
	std::binomial_distribution<int> binomial(infectedMothers, congenitalTransmissionProbability);

	double infectedBirthsAmount = binomial(randomGenerator);
	double nonInfectedBirthsAmount = nonInfectedMothers + (infectedMothers - infectedBirthsAmount);

	Tuple<Real> infectedValue{Real(infectedBirthsAmount), 0, 1};
	Tuple<Real> nonInfectedValue{Real(nonInfectedBirthsAmount), 0, 1};
	sendOutput(msg.time(), nonInfectedBirths, nonInfectedValue);
	sendOutput(msg.time(), infectedBirths, infectedValue);

	return *this;
}
