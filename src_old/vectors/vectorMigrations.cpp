#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "vectorMigrations.h"

using namespace std;

VectorMigrations::VectorMigrations(const string &name) :
	Atomic(name),
	applyMigrations(addInputPort("applyMigrations")),
	susceptibleMigrations(addOutputPort("susceptibleMigrations")),
	infectedMigrations(addOutputPort("infectedMigrations")),
	migrationsApplied(addOutputPort("migrationsApplied")),
	frequency_time(0,0,0,1){
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
	if(msg.port() == applyMigrations){
		susceptiblePopulation = (Tuple<Real>::from_value(msg.value())[0]).value();
		infectedPopulation = (Tuple<Real>::from_value(msg.value())[1]).value();
	}
	holdIn(AtomicState::active, VTime::Zero);
	return *this;
}


Model &VectorMigrations::internalFunction(const InternalMessage &msg){
	passivate();
	return *this ;
}


Model &VectorMigrations::outputFunction(const CollectMessage &msg){
	currentSusceptibleImmigrationRate = getRate(susceptibleImmigrationRate, susceptibleImmigrationDeviation);
	currentSusceptibleEmmigrationRate = getRate(susceptibleEmmigrationRate, susceptibleEmmigrationDeviation);
	currentInfectedImmigrationRate = getRate(infectedImmigrationRate, infectedImmigrationDeviation);
	currentInfectedEmmigrationRate = getRate(infectedEmmigrationRate, infectedEmmigrationDeviation);

	susceptibleImmigrationsAmount = static_cast<int>(currentSusceptibleImmigrationRate * susceptiblePopulation);
	susceptibleEmmigrationsAmount = static_cast<int>(currentSusceptibleEmmigrationRate * susceptiblePopulation);
	infectedImmigrationsAmount = static_cast<int>(currentInfectedImmigrationRate * infectedPopulation);
	infectedEmmigrationsAmount = static_cast<int>(currentInfectedEmmigrationRate * infectedPopulation);

	susceptiblePopulation = susceptiblePopulation + susceptibleImmigrationsAmount - susceptibleEmmigrationsAmount;
	infectedPopulation = infectedPopulation + infectedImmigrationsAmount - infectedEmmigrationsAmount;

	Tuple<Real> migrationsValue{Real(susceptiblePopulation), Real(infectedPopulation)};
	Tuple<Real> susceptibleMigrationsValue{Real(susceptibleImmigrationsAmount), Real(susceptibleEmmigrationsAmount)};
	Tuple<Real> infectedMigrationsValue{Real(infectedImmigrationsAmount), Real(infectedEmmigrationsAmount)};
	sendOutput(msg.time(), susceptibleMigrations, susceptibleMigrationsValue);
	sendOutput(msg.time(), infectedMigrations, infectedMigrationsValue);
	sendOutput(msg.time(), migrationsApplied, migrationsValue);

	return *this;
}


double VectorMigrations::getRate(double mean, double deviation){
	std::normal_distribution<double> rateDistribution(mean, deviation);
	return abs(rateDistribution(randomGenerator));
}
