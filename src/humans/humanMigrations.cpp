#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "humanMigrations.h"
#include "utils.h"

using namespace std;

HumanMigrations::HumanMigrations(const string &name) :
	Atomic(name),
	execute(addInputPort("execute")),
	setValues(addOutputPort("setValues")),
	applied(addOutputPort("applied")){
}


Model &HumanMigrations::initFunction(){
	susceptibleImmigrationRate = 0.000045;
	susceptibleImmigrationDeviation = 0.000017;
	susceptibleEmmigrationRate = 0.000057;
	susceptibleEmmigrationDeviation = 0.000022;
	indeterminateImmigrationRate = 0.000027;
	indeterminateImmigrationDeviation = 0.000016;
	indeterminateEmmigrationRate = 0.000034;
	indeterminateEmmigrationDeviation = 0.000019;
	chronicImmigrationRate = 0.000003;
	chronicImmigrationDeviation = 0.000002;
	chronicEmmigrationRate = 0.000004;
	chronicEmmigrationDeviation = 0.000002;
	passivate();
	return *this;
}


Model &HumanMigrations::externalFunction(const ExternalMessage &msg){
	if(msg.port() == execute){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		acutePopulation = getValueFromTupleAt(msg,1);
		indeterminatePopulation = getValueFromTupleAt(msg,2);
		chronicPopulation = getValueFromTupleAt(msg,3);
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &HumanMigrations::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &HumanMigrations::outputFunction(const CollectMessage &msg){
	lastSusceptibleImmigrationRate = getRate(susceptibleImmigrationRate, susceptibleImmigrationDeviation);
	lastSusceptibleEmmigrationRate = getRate(susceptibleEmmigrationRate, susceptibleEmmigrationDeviation);
	lastIndeterminateImmigrationRate = getRate(indeterminateImmigrationRate, indeterminateImmigrationDeviation);
	lastIndeterminateEmmigrationRate = getRate(indeterminateEmmigrationRate, indeterminateEmmigrationDeviation);
	lastChronicImmigrationRate = getRate(chronicImmigrationRate, chronicImmigrationDeviation);
	lastChronicEmmigrationRate = getRate(chronicEmmigrationRate, chronicEmmigrationDeviation);

	susceptibleImmigrationsAmount = static_cast<int>(lastSusceptibleImmigrationRate * susceptiblePopulation);
	susceptibleEmmigrationsAmount = static_cast<int>(lastSusceptibleEmmigrationRate * susceptiblePopulation);
	indeterminateImmigrationsAmount = static_cast<int>(lastIndeterminateImmigrationRate * indeterminatePopulation);
	indeterminateEmmigrationsAmount = static_cast<int>(lastIndeterminateEmmigrationRate * indeterminatePopulation);
	chronicImmigrationsAmount = static_cast<int>(lastChronicImmigrationRate * chronicPopulation);
	chronicEmmigrationsAmount = static_cast<int>(lastChronicEmmigrationRate * chronicPopulation);

	susceptiblePopulation = susceptiblePopulation + susceptibleImmigrationsAmount - susceptibleEmmigrationsAmount;
	indeterminatePopulation = indeterminatePopulation + indeterminateImmigrationsAmount - indeterminateEmmigrationsAmount;
	chronicPopulation = chronicPopulation + chronicImmigrationsAmount - chronicEmmigrationsAmount;

	sendOutput(msg.time(), setValues, asTuple(susceptibleImmigrationsAmount, susceptibleEmmigrationsAmount, indeterminateImmigrationsAmount, indeterminateEmmigrationsAmount, chronicImmigrationsAmount, chronicEmmigrationsAmount));
	sendOutput(msg.time(), applied, asTuple(susceptiblePopulation, acutePopulation, indeterminatePopulation, chronicPopulation));

	return *this;
}


double HumanMigrations::getRate(double mean, double deviation){
	std::normal_distribution<double> rateDistribution(mean, deviation);
	return abs(rateDistribution(randomGenerator));
}
