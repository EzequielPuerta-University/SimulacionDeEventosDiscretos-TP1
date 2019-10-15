#ifndef _DOG_MIGRATIONS_H_
#define _DOG_MIGRATIONS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "DogMigrations"


class DogMigrations : public Atomic {
  public:
    DogMigrations(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    double getRate(double, double);

  private:
    const Port &applyMigrations;
    Port &susceptibleMigrations;
    Port &infectedMigrations;
    Port &migrationsApplied;

    VTime frequency_time;

    double susceptibleImmigrationRate;
    double susceptibleImmigrationDeviation;
  	double susceptibleEmmigrationRate;
  	double susceptibleEmmigrationDeviation;
  	double infectedImmigrationRate;
  	double infectedImmigrationDeviation;
  	double infectedEmmigrationRate;
  	double infectedEmmigrationDeviation;

    double currentSusceptibleImmigrationRate;
  	double currentSusceptibleEmmigrationRate;
  	double currentInfectedImmigrationRate;
  	double currentInfectedEmmigrationRate;
    double susceptibleImmigrationsAmount;
  	double susceptibleEmmigrationsAmount;
  	double infectedImmigrationsAmount;
  	double infectedEmmigrationsAmount;

    double susceptiblePopulation;
    double infectedPopulation;
    std::default_random_engine randomGenerator;
};

#endif
