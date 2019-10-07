#ifndef _INFECTED_DOGS_H_
#define _INFECTED_DOGS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "InfectedDogs"


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
    const Port &infectedBites;
    const Port &nonInfectedBites;
    Port &infected;
    Port &deaths;
    Port &arrivals;
    Port &departures;

    VTime frequency_time;

    int population;
    int immigrationRate;
    int emigrationRate;
};

#endif
