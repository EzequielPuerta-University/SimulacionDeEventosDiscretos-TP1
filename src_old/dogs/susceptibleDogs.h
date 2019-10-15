#ifndef _SUSCEPTIBLE_DOGS_H_
#define _SUSCEPTIBLE_DOGS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "SusceptibleDogs"
#define PASSIVE 0
#define POPULATION_REQUEST 1
#define INFECTIONS_APPLIED 2

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
    const Port &migrations;
    const Port &infected;
    Port &infectionsApplied;
    const Port &deaths;
    const Port &populationRequest;
    Port &currentPopulation;

    VTime frequency_time;

    int state;
    double population;
    double immigrants;
    double emmigrants;
    double lastInfections;
};

#endif
