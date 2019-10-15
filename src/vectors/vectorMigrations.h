#ifndef _VECTOR_MIGRATIONS_H_
#define _VECTOR_MIGRATIONS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

class VectorMigrations : public Atomic {
  public:
    VectorMigrations(const string &name = "VectorMigrations" );
    virtual string className() const {  return "VectorMigrations" ;}

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
