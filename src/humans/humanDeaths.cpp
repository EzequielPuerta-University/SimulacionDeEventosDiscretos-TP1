#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "humanDeaths.h"
#include "utils.h"

using namespace std;

HumanDeaths::HumanDeaths(const string &name) :
	Atomic(name),
	execute(addInputPort("execute")),
	setValues(addOutputPort("setValues")),
	applied(addOutputPort("applied")){
}


Model &HumanDeaths::initFunction(){
	susceptibleMeanRate = 0.000016;
	susceptibleStandardDeviation = 0.000005;
	acuteMeanRate = 0.000433;
	acuteStandardDeviation = 0.000130;
	indeterminateMeanRate = 0.000016;
	indeterminateStandardDeviation = 0.000005;
	chronicMeanRate = 0.000290;
	chronicStandardDeviation = 0.000087;
	passivate();
	return *this;
}


Model &HumanDeaths::externalFunction(const ExternalMessage &msg){
	if(msg.port() == execute){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		acutePopulation = getValueFromTupleAt(msg,1);
		indeterminatePopulation = getValueFromTupleAt(msg,2);
		chronicPopulation = getValueFromTupleAt(msg,3);
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &HumanDeaths::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &HumanDeaths::outputFunction(const CollectMessage &msg){
	lastSusceptibleRate = getRate(susceptibleMeanRate, susceptibleStandardDeviation);
	lastAcuteRate = getRate(acuteMeanRate, acuteStandardDeviation);
	lastIndeterminateRate = getRate(indeterminateMeanRate, indeterminateStandardDeviation);
	lastChronicRate = getRate(chronicMeanRate, chronicStandardDeviation);

	susceptibleDeathsAmount = static_cast<int>(lastSusceptibleRate * susceptiblePopulation);
	acuteDeathsAmount = static_cast<int>(lastAcuteRate * acutePopulation);
	indeterminateDeathsAmount = static_cast<int>(lastIndeterminateRate * indeterminatePopulation);
	chronicDeathsAmount = static_cast<int>(lastChronicRate * chronicPopulation);

	susceptiblePopulation = susceptiblePopulation - susceptibleDeathsAmount;
	acutePopulation = acutePopulation - acuteDeathsAmount;
	indeterminatePopulation = indeterminatePopulation - indeterminateDeathsAmount;
	chronicPopulation = chronicPopulation - chronicDeathsAmount;

	sendOutput(msg.time(), setValues, asTuple(susceptibleDeathsAmount, acuteDeathsAmount, indeterminateDeathsAmount, chronicDeathsAmount));
	sendOutput(msg.time(), applied, asTuple(susceptiblePopulation, acutePopulation, indeterminatePopulation, chronicPopulation));

	return *this;
}


double HumanDeaths::getRate(double mean, double deviation){
	std::normal_distribution<double> rateDistribution(mean, deviation);
	return abs(rateDistribution(randomGenerator));
}
