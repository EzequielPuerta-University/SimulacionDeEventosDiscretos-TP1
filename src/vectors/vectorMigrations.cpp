#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "vectorMigrations.h"
#include "utils.h"

using namespace std;

VectorMigrations::VectorMigrations(const string &name) :
	Atomic(name),
	execute(addInputPort("execute")),
	setValues(addOutputPort("setValues")),
	applied(addOutputPort("applied")){
}


Model &VectorMigrations::initFunction(){
	susceptibleImmigrationRate = 0.20;
	susceptibleImmigrationDeviation = 0.06;
	susceptibleEmmigrationRate = 0.21;
	susceptibleEmmigrationDeviation = 0.063;
	infectedImmigrationRate = 0.22;
	infectedImmigrationDeviation = 0.066;
	infectedEmmigrationRate = 0.21;
	infectedEmmigrationDeviation = 0.063;
	passivate();
	return *this;
}


Model &VectorMigrations::externalFunction(const ExternalMessage &msg){
	if(msg.port() == execute){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		infectedPopulation = getValueFromTupleAt(msg,1);
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &VectorMigrations::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &VectorMigrations::outputFunction(const CollectMessage &msg){
	lastSusceptibleImmigrationRate = getRate(susceptibleImmigrationRate, susceptibleImmigrationDeviation);
	lastSusceptibleEmmigrationRate = getRate(susceptibleEmmigrationRate, susceptibleEmmigrationDeviation);
	lastInfectedImmigrationRate = getRate(infectedImmigrationRate, infectedImmigrationDeviation);
	lastInfectedEmmigrationRate = getRate(infectedEmmigrationRate, infectedEmmigrationDeviation);

	susceptibleImmigrationsAmount = static_cast<int>(lastSusceptibleImmigrationRate * susceptiblePopulation);
	susceptibleEmmigrationsAmount = static_cast<int>(lastSusceptibleEmmigrationRate * susceptiblePopulation);
	infectedImmigrationsAmount = static_cast<int>(lastInfectedImmigrationRate * infectedPopulation);
	infectedEmmigrationsAmount = static_cast<int>(lastInfectedEmmigrationRate * infectedPopulation);

	susceptiblePopulation = susceptiblePopulation + susceptibleImmigrationsAmount - susceptibleEmmigrationsAmount;
	infectedPopulation = infectedPopulation + infectedImmigrationsAmount - infectedEmmigrationsAmount;

	sendOutput(msg.time(), setValues, asTuple(susceptibleImmigrationsAmount, susceptibleEmmigrationsAmount, infectedImmigrationsAmount, infectedEmmigrationsAmount));
	sendOutput(msg.time(), applied, asTuple(susceptiblePopulation, infectedPopulation));

	return *this;
}


double VectorMigrations::getRate(double mean, double deviation){
	std::normal_distribution<double> rateDistribution(mean, deviation);
	return abs(rateDistribution(randomGenerator));
}
