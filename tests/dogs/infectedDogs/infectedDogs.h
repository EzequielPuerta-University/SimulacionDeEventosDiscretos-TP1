#ifndef _INFECTED_DOGS_H_
#define _INFECTED_DOGS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "InfectedDogs"
#define POPULATION_REQUEST 1
#define PASSIVE 0

class InfectedDogs : public Atomic {
  public:
    InfectedDogs(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &births;
    const Port &migrations;
    const Port &deaths;
    const Port &populationRequest;
    Port &currentPopulation;

    VTime frequency_time;

    int state;
    double population;
    double immigrants;
    double emmigrants;
};

#endif
