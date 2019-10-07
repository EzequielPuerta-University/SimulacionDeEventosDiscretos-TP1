#ifndef _SUSCEPTIBLE_HUMANS_H_
#define _SUSCEPTIBLE_HUMANS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "SusceptibleHumans"


class SusceptibleHumans : public Atomic {
  public:

    SusceptibleHumans(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &births;
    Port &deaths;
    Port &infectedBites;
    Port &nonInfectedBites;

    VTime frequency_time;

    int population;
    int immigrationRate;
    int emigrationRate;
    int womanPercentage;
    int motherBirthRate;
};

#endif
