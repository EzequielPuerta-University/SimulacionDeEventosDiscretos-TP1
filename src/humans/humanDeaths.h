#ifndef _HUMAN_DEATHS_H_
#define _HUMAN_DEATHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "HumanDeaths"


class HumanDeaths : public Atomic {
  public:

    HumanDeaths(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &births;
    Port &infectedBirths;
    Port &nonInfectedBirths;

    VTime frequency_time;

    int susceptiblePopulation;
    int infectedIndeterminatePopulation;
    int infectedChronicPopulation;

    int susceptibleMotherBirthRate;
    int indeterminateMotherBirthRate;
    int chronicMotherBirthRate;
    int congenitalTransmissionProbability;
};

#endif
