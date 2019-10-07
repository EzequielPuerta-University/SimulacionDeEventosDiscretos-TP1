#ifndef _SUSCEPTIBLE_DOGS_H_
#define _SUSCEPTIBLE_DOGS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "SusceptibleDogs"


class SusceptibleDogs : public Atomic {
  public:
    SusceptibleDogs(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &births;
    const Port &infectedVectors;
    const Port &nonInfectedVectors;
    const Port &immigrants;
    const Port &emmigrants;
    Port &infected;
    Port &deaths;
    Port &currentPopulation;

    VTime frequency_time;

    double population;
    double deathRate;
    double standardDeviation;
    std::default_random_engine randomGenerator;
};

#endif
