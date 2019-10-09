#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "vectorDeaths.h"

using namespace std;

VectorDeaths::VectorDeaths(const string &name) :
	Atomic(name),
	applyDeaths(addInputPort("applyDeaths")),
	susceptibleDeaths(addOutputPort("susceptibleDeaths")),
	infectedDeaths(addOutputPort("infectedDeaths")),
	deathsApplied(addOutputPort("deathsApplied")),
	frequency_time(0,0,0,1){
}


Model &VectorDeaths::initFunction(){
	meanDeathRate = 0.011078;
	standardDeviation = 0.003323;
	passivate();
	return *this;
}


Model &VectorDeaths::externalFunction(const ExternalMessage &msg){
	if(msg.port() == applyDeaths){
		susceptiblePopulation = (Tuple<Real>::from_value(msg.value())[0]).value();
		infectedPopulation = (Tuple<Real>::from_value(msg.value())[1]).value();
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &VectorDeaths::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &VectorDeaths::outputFunction(const CollectMessage &msg){
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


double VectorDeaths::getDeathRate(){
	std::normal_distribution<double> deathRateDistribution(meanDeathRate, standardDeviation);
	return abs(deathRateDistribution(randomGenerator));
}
