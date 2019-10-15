#ifndef _DOG_BIRTHS_H_
#define _DOG_BIRTHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

class DogBirths : public Atomic {
  public:
    DogBirths(const string &name = "DogBirths" );
    virtual string className() const {  return "DogBirths" ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    double getRate();

  private:
    const Port &execute;
    Port &setValues;
    Port &applied;

    double meanRate;
    double standardDeviation;
    double lastRate;
    int susceptiblePopulation;
    int infectedPopulation;
    int susceptibleBirthsAmount;
    int infectedBirthsAmount;
    double congenitalTransmissionProbability;
    std::default_random_engine randomGenerator;
};

#endif
