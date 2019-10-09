#ifndef _SUSCEPTIBLE_VECTORS_H_
#define _SUSCEPTIBLE_VECTORS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "SusceptibleVectors"


class SusceptibleVectors : public Atomic {
  public:
    SusceptibleVectors(const string &name = ATOMIC_MODEL_NAME );
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

    double population;
    double immigrants;
    double emmigrants;
};

#endif
