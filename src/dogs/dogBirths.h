#ifndef _DOG_BIRTHS_H_
#define _DOG_BIRTHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "DogBirths"


class DogBirths : public Atomic {
  public:
    DogBirths(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &currentSusceptiblePopulation;
    const Port &currentInfectedPopulation;
    Port &infectedBirths;
    Port &nonInfectedBirths;

    VTime frequency_time;

    int susceptiblePopulation;
    int infectedPopulation;

    int susceptibleMotherBirthRate;
    int infectedMotherBirthRate;
    int congenitalTransmissionProbability;

    std::mt19937 randomGenerator;
};

#endif