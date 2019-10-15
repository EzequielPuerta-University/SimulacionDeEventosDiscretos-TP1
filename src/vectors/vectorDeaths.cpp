#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "vectorDeaths.h"
#include "utils.h"

using namespace std;

VectorDeaths::VectorDeaths(const string &name) :
	Atomic(name),
	execute(addInputPort("execute")),
	setValues(addOutputPort("setValues")),
	applied(addOutputPort("applied")){
}


Model &VectorDeaths::initFunction(){
	meanRate = 0.011078;
	standardDeviation = 0.003323;
	passivate();
	return *this;
}


Model &VectorDeaths::externalFunction(const ExternalMessage &msg){
	if(msg.port() == execute){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		infectedPopulation = getValueFromTupleAt(msg,1);
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &VectorDeaths::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &VectorDeaths::outputFunction(const CollectMessage &msg){
	lastRate = getRate();
	susceptibleDeathsAmount = static_cast<int>(lastRate * susceptiblePopulation);
	infectedDeathsAmount = static_cast<int>(lastRate * infectedPopulation);

	susceptiblePopulation = susceptiblePopulation - susceptibleDeathsAmount;
	infectedPopulation = infectedPopulation - infectedDeathsAmount;

	sendOutput(msg.time(), setValues, asTuple(susceptibleDeathsAmount, infectedDeathsAmount));
	sendOutput(msg.time(), applied, asTuple(susceptiblePopulation, infectedPopulation));

	return *this;
}


double VectorDeaths::getRate(){
	std::normal_distribution<double> rateDistribution(meanRate, standardDeviation);
	return abs(rateDistribution(randomGenerator));
}
