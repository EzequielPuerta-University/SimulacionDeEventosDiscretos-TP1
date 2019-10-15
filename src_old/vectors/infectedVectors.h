#ifndef _INFECTED_VECTORS_H_
#define _INFECTED_VECTORS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "InfectedVectors"
#define PASSIVE 0
#define POPULATION_REQUEST 1
#define INFECTIONS_APPLIED 2

class InfectedVectors : public Atomic {
  public:
    InfectedVectors(const string &name = ATOMIC_MODEL_NAME );
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
    double lastInfections;
};

#endif
