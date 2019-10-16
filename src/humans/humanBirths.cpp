#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "humanBirths.h"
#include "utils.h"

using namespace std;

HumanBirths::HumanBirths(const string &name) :
	Atomic(name),
	execute(addInputPort("execute")),
	setValues(addOutputPort("setValues")),
	applied(addOutputPort("applied")){
}


Model &HumanBirths::initFunction(){
	susceptibleMeanRate = 0.000058;
	susceptibleStandardDeviation = 0.000017;
	indeterminateMeanRate = 0.000057;
	indeterminateStandardDeviation = 0.000017;
	chronicMeanRate = 0.000029;
	chronicStandardDeviation = 0.000009;
	congenitalTransmissionProbability = 0.10;
	passivate();
	return *this;
}


Model &HumanBirths::externalFunction(const ExternalMessage &msg){
	if(msg.port() == execute){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		acutePopulation = getValueFromTupleAt(msg,1);
		indeterminatePopulation = getValueFromTupleAt(msg,2);
		chronicPopulation = getValueFromTupleAt(msg,3);
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &HumanBirths::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &HumanBirths::outputFunction(const CollectMessage &msg){
	lastSusceptibleRate = getRate(susceptibleMeanRate, susceptibleStandardDeviation);
	lastIndeterminateRate = getRate(indeterminateMeanRate, indeterminateStandardDeviation);
	lastChronicRate = getRate(chronicMeanRate, chronicStandardDeviation);

	susceptibleBirthsAmount = static_cast<int>(lastSusceptibleRate * susceptiblePopulation);
	int infectedIndeterminateMothers = static_cast<int>(lastIndeterminateRate * indeterminatePopulation);
	int infectedChronicMothers = static_cast<int>(lastChronicRate * chronicPopulation);
	std::binomial_distribution<int> binomialI(infectedIndeterminateMothers, congenitalTransmissionProbability);
	std::binomial_distribution<int> binomialC(infectedChronicMothers, congenitalTransmissionProbability);

	indeterminateBirthsAmount = binomialI(randomGenerator);
	chronicBirthsAmount = binomialC(randomGenerator);
	susceptibleBirthsAmount = susceptibleBirthsAmount + (infectedIndeterminateMothers - indeterminateBirthsAmount) + (infectedChronicMothers - chronicBirthsAmount);
	susceptiblePopulation = susceptiblePopulation + susceptibleBirthsAmount;
	acutePopulation = acutePopulation + indeterminateBirthsAmount + chronicBirthsAmount;

	sendOutput(msg.time(), setValues, asTuple(susceptibleBirthsAmount, (indeterminateBirthsAmount + chronicBirthsAmount)));
	sendOutput(msg.time(), applied, asTuple(susceptiblePopulation, acutePopulation, indeterminatePopulation, chronicPopulation));

	return *this;
}


double HumanBirths::getRate(double mean, double deviation){
	std::normal_distribution<double> rateDistribution(mean, deviation);
	return abs(rateDistribution(randomGenerator));
}
