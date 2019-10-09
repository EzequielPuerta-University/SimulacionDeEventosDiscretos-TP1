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
	applyDeaths(addInputPort("applyDeaths")),
	susceptibleDeaths(addOutputPort("susceptibleDeaths")),
	infectedDeaths(addOutputPort("infectedDeaths")),
	deathsApplied(addOutputPort("deathsApplied")),
	frequency_time(0,0,0,1){
}


Model &DogDeaths::initFunction(){
	meanDeathRate = 0.000913;
	standardDeviation = 0.000274;
	passivate();
	return *this;
}


Model &DogDeaths::externalFunction(const ExternalMessage &msg){
	if(msg.port() == applyDeaths){
		susceptiblePopulation = (Tuple<Real>::from_value(msg.value())[0]).value();
		infectedPopulation = (Tuple<Real>::from_value(msg.value())[1]).value();
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &DogDeaths::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &DogDeaths::outputFunction(const CollectMessage &msg){
	deathRate = getDeathRate();
	susceptibleDeathsAmount = static_cast<int>(deathRate * susceptiblePopulation);
	infectedDeathsAmount = static_cast<int>(deathRate * infectedPopulation);

	susceptiblePopulation = susceptiblePopulation - susceptibleDeathsAmount;
	infectedPopulation = infectedPopulation - infectedDeathsAmount;

	Tuple<Real> deathsValue{Real(susceptiblePopulation), Real(infectedPopulation)};
	sendOutput(msg.time(), susceptibleDeaths, susceptibleDeathsAmount);
	sendOutput(msg.time(), infectedDeaths, infectedDeathsAmount);
	sendOutput(msg.time(), deathsApplied, deathsValue);

	return *this;
}


double DogDeaths::getDeathRate(){
	std::normal_distribution<double> deathRateDistribution(meanDeathRate, standardDeviation);
	return abs(deathRateDistribution(randomGenerator));
}
