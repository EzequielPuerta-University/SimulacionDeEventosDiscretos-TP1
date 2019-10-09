#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "susceptibleVectors.h"

using namespace std;

SusceptibleVectors::SusceptibleVectors(const string &name) :
	Atomic(name),
	births(addInputPort("births")),
	migrations(addInputPort("migrations")),
	infected(addInputPort("infected")),
	deaths(addInputPort("deaths")),
	populationRequest(addInputPort("populationRequest")),
	currentPopulation(addOutputPort("currentPopulation")),
	infectionsApplied(addOutputPort("infectionsApplied")),
	frequency_time(0,0,0,1){
	population = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "population" ));
}


Model &SusceptibleVectors::initFunction(){
	deathRate = 0.000913;
	standardDeviation = 0.000274;
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &SusceptibleVectors::externalFunction(const ExternalMessage &msg){
	if((msg.port() == births) || (msg.port() == immigrants)) {
		population = population + (Real::from_value(msg.value())).value();
	} else if((msg.port() == deaths) || (msg.port() == emmigrants)){
		population = population - (Real::from_value(msg.value())).value();
	}
	holdIn(AtomicState::active, nextChange());
	return *this;
}


Model &SusceptibleVectors::internalFunction(const InternalMessage &msg){
	holdIn(AtomicState::active, this->frequency_time);
	return *this ;
}


Model &SusceptibleVectors::outputFunction(const CollectMessage &msg){
	std::normal_distribution<double> deathRateDistribution(deathRate, standardDeviation);
	double currentDeathRate = abs(deathRateDistribution(randomGenerator));
	int deathsAmount = static_cast<int>(currentDeathRate * population);
	population = population - deathsAmount;

	Tuple<Real> deathsValue{Real(deathsAmount), 0, 1};
	sendOutput(msg.time(), deaths, deathsValue);

	Tuple<Real> currentValue{Real(population), 0, 1};
	sendOutput(msg.time(), currentPopulation, currentValue);
	return *this;
}
