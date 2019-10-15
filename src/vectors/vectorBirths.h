#ifndef _VECTOR_BIRTHS_H_
#define _VECTOR_BIRTHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

class VectorBirths : public Atomic {
  public:
    VectorBirths(const string &name = "VectorBirths" );
    virtual string className() const {  return "VectorBirths" ;}

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
