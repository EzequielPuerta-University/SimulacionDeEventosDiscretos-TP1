#ifndef _DOG_DEATHS_H_
#define _DOG_DEATHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "DogDeaths"


class DogDeaths : public Atomic {
  public:
    DogDeaths(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    double getDeathRate();

  private:
    const Port &applyDeaths;
    Port &susceptibleDeaths;
    Port &infectedDeaths;
    Port &deathsApplied;

    VTime frequency_time;

    double meanDeathRate;
    double standardDeviation;
    double deathRate;
    double susceptiblePopulation;
    double infectedPopulation;
    double susceptibleDeathsAmount;
    double infectedDeathsAmount;
    std::default_random_engine randomGenerator;
};

#endif
