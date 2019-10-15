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
	applyBirths(addInputPort("applyBirths")),
	susceptibleBirths(addOutputPort("susceptibleBirths")),
	infectedBirths(addOutputPort("infectedBirths")),
	birthsApplied(addOutputPort("birthsApplied")),
	frequency_time(0,0,0,1){
}


Model &VectorBirths::initFunction(){
	meanBirthRate = 0.012500;
	standardDeviation = 0.00375;
	passivate();
	return *this;
}


Model &VectorBirths::externalFunction(const ExternalMessage &msg){
	if(msg.port() == applyBirths){
		susceptiblePopulation = (Tuple<Real>::from_value(msg.value())[0]).value();
		infectedPopulation = (Tuple<Real>::from_value(msg.value())[1]).value();
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &VectorBirths::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &VectorBirths::outputFunction(const CollectMessage &msg){
	birthRate = getBirthRate();
	susceptibleBirthsAmount = static_cast<int>(birthRate * susceptiblePopulation);
	infectedBirthsAmount = static_cast<int>(birthRate * infectedPopulation);

	susceptiblePopulation = susceptiblePopulation + susceptibleBirthsAmount;
	infectedPopulation = infectedPopulation + infectedBirthsAmount;

	Tuple<Real> birthsValue{Real(susceptiblePopulation), Real(infectedPopulation)};
	sendOutput(msg.time(), susceptibleBirths, susceptibleBirthsAmount);
	sendOutput(msg.time(), infectedBirths, infectedBirthsAmount);
	sendOutput(msg.time(), birthsApplied, birthsValue);

	return *this;
}


double VectorBirths::getBirthRate(){
	std::normal_distribution<double> birthRateDistribution(meanBirthRate, standardDeviation);
	return abs(birthRateDistribution(randomGenerator));
}
