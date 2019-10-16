#ifndef _HUMAN_MIGRATIONS_H_
#define _HUMAN_MIGRATIONS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

class HumanMigrations : public Atomic {
  public:
    HumanMigrations(const string &name = "HumanMigrations" );
    virtual string className() const {  return "HumanMigrations" ;}

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
  	double indeterminateImmigrationRate;
  	double indeterminateImmigrationDeviation;
  	double indeterminateEmmigrationRate;
  	double indeterminateEmmigrationDeviation;
    double chronicImmigrationRate;
    double chronicImmigrationDeviation;
  	double chronicEmmigrationRate;
  	double chronicEmmigrationDeviation;

    double lastSusceptibleImmigrationRate;
  	double lastSusceptibleEmmigrationRate;
  	double lastIndeterminateImmigrationRate;
  	double lastIndeterminateEmmigrationRate;
    double lastChronicImmigrationRate;
    double lastChronicEmmigrationRate;
    double susceptibleImmigrationsAmount;
  	double susceptibleEmmigrationsAmount;
  	double indeterminateImmigrationsAmount;
  	double indeterminateEmmigrationsAmount;
    double chronicImmigrationsAmount;
  	double chronicEmmigrationsAmount;

    double susceptiblePopulation;
    double acutePopulation;
    double indeterminatePopulation;
    double chronicPopulation;
    std::default_random_engine randomGenerator;
};

#endif
