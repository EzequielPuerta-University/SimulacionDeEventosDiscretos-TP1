#ifndef _HUMAN_BIRTHS_H_
#define _HUMAN_BIRTHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "HumanBirths"


class HumanBirths : public Atomic {
  public:

    HumanBirths(const string &name = ATOMIC_MODEL_NAME );
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
