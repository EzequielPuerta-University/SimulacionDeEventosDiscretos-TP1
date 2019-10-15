#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "vectorBirths.h"
#include "utils.h"

using namespace std;

VectorBirths::VectorBirths(const string &name) :
	Atomic(name),
	execute(addInputPort("execute")),
	setValues(addOutputPort("setValues")),
	applied(addOutputPort("applied")){
}


Model &VectorBirths::initFunction(){
	meanRate = 0.012500;
	standardDeviation = 0.00375;
	congenitalTransmissionProbability = 1;
	passivate();
	return *this;
}


Model &VectorBirths::externalFunction(const ExternalMessage &msg){
	if(msg.port() == execute){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		infectedPopulation = getValueFromTupleAt(msg,1);
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &VectorBirths::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &VectorBirths::outputFunction(const CollectMessage &msg){
	lastRate = getRate();
	susceptibleBirthsAmount = static_cast<int>(lastRate * susceptiblePopulation);
	int infectedMothers = static_cast<int>(lastRate * infectedPopulation);
	std::binomial_distribution<int> binomial(infectedMothers, congenitalTransmissionProbability);

	infectedBirthsAmount = binomial(randomGenerator);
	susceptibleBirthsAmount = susceptibleBirthsAmount + infectedMothers - infectedBirthsAmount;
	susceptiblePopulation = susceptiblePopulation + susceptibleBirthsAmount;
	infectedPopulation = infectedPopulation + infectedBirthsAmount;

	sendOutput(msg.time(), setValues, asTuple(susceptibleBirthsAmount, infectedBirthsAmount));
	sendOutput(msg.time(), applied, asTuple(susceptiblePopulation, infectedPopulation));

	return *this;
}


double VectorBirths::getRate(){
	std::normal_distribution<double> rateDistribution(meanRate, standardDeviation);
	return abs(rateDistribution(randomGenerator));
}
