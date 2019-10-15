#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "dogMigrations.h"
#include "utils.h"

using namespace std;

DogMigrations::DogMigrations(const string &name) :
	Atomic(name),
	execute(addInputPort("execute")),
	setValues(addOutputPort("setValues")),
	applied(addOutputPort("applied")){
}


Model &DogMigrations::initFunction(){
	susceptibleImmigrationRate = 0.000055;
	susceptibleImmigrationDeviation = 0.000031;
	susceptibleEmmigrationRate = 0.000061;
	susceptibleEmmigrationDeviation = 0.000046;
	infectedImmigrationRate = 0.000493;
	infectedImmigrationDeviation = 0.000148;
	infectedEmmigrationRate = 0.000548;
	infectedEmmigrationDeviation = 0.000164;
	passivate();
	return *this;
}


Model &DogMigrations::externalFunction(const ExternalMessage &msg){
	if(msg.port() == execute){
		susceptiblePopulation = getValueFromTupleAt(msg,0);
		infectedPopulation = getValueFromTupleAt(msg,1);
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &DogMigrations::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &DogMigrations::outputFunction(const CollectMessage &msg){
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


double DogMigrations::getRate(double mean, double deviation){
	std::normal_distribution<double> rateDistribution(mean, deviation);
	return abs(rateDistribution(randomGenerator));
}
