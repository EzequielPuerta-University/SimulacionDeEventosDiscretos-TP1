#ifndef _DOG_MIGRATIONS_H_
#define _DOG_MIGRATIONS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

class DogMigrations : public Atomic {
  public:
    DogMigrations(const string &name = "DogMigrations" );
    virtual string className() const {  return "DogMigrations" ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    double getRate(double, double);

  private:
    const Port &execute;
    Port &setValues;
    Port &applied;

    double susceptibleImmigrationRate;
    double susceptibleImmigrationDeviation;
  	double susceptibleEmmigrationRate;
  	double susceptibleEmmigrationDeviation;
  	double infectedImmigrationRate;
  	double infectedImmigrationDeviation;
  	double infectedEmmigrationRate;
  	double infectedEmmigrationDeviation;

    double lastSusceptibleImmigrationRate;
  	double lastSusceptibleEmmigrationRate;
  	double lastInfectedImmigrationRate;
  	double lastInfectedEmmigrationRate;
    double susceptibleImmigrationsAmount;
  	double susceptibleEmmigrationsAmount;
  	double infectedImmigrationsAmount;
  	double infectedEmmigrationsAmount;

    double susceptiblePopulation;
    double infectedPopulation;
    std::default_random_engine randomGenerator;
};

#endif
