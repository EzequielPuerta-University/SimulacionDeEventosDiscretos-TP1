#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "dogBirths.h"

using namespace std;

DogBirths::DogBirths(const string &name) :
	Atomic(name),
	applyBirths(addInputPort("applyBirths")),
	susceptibleBirths(addOutputPort("susceptibleBirths")),
	infectedBirths(addOutputPort("infectedBirths")),
	birthsApplied(addOutputPort("birthsApplied")),
	frequency_time(0,0,0,1){
}


Model &DogBirths::initFunction(){
	meanBirthRate = 0.001002;
	standardDeviation = 0.000301;
	congenitalTransmissionProbability = 0.10;
	passivate();
	return *this;
}


Model &DogBirths::externalFunction(const ExternalMessage &msg){
	if(msg.port() == applyBirths){
		susceptiblePopulation = (Tuple<Real>::from_value(msg.value())[0]).value();
		infectedPopulation = (Tuple<Real>::from_value(msg.value())[1]).value();
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &DogBirths::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &DogBirths::outputFunction(const CollectMessage &msg){
	birthRate = getBirthRate();
	susceptibleBirthsAmount = static_cast<int>(birthRate * susceptiblePopulation);
	int infectedMothers = static_cast<int>(birthRate * infectedPopulation);
	std::binomial_distribution<int> binomial(infectedMothers, congenitalTransmissionProbability);

	infectedBirthsAmount = binomial(randomGenerator);
	susceptibleBirthsAmount = susceptibleBirthsAmount + (infectedMothers - infectedBirthsAmount);
	susceptiblePopulation = susceptiblePopulation + susceptibleBirthsAmount;
	infectedPopulation = infectedPopulation + infectedBirthsAmount;

	Tuple<Real> birthsValue{Real(susceptiblePopulation), Real(infectedPopulation)};
	sendOutput(msg.time(), susceptibleBirths, susceptibleBirthsAmount);
	sendOutput(msg.time(), infectedBirths, infectedBirthsAmount);
	sendOutput(msg.time(), birthsApplied, birthsValue);

	return *this;
}


double DogBirths::getBirthRate(){
	std::normal_distribution<double> birthRateDistribution(meanBirthRate, standardDeviation);
	return abs(birthRateDistribution(randomGenerator));
}
