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

  private:
    const Port &currentSusceptibleDeaths;
    const Port &currentInfectedDeaths;

    VTime frequency_time;

    double susceptibleDeaths;
    double infectedDeaths;
};

#endif
