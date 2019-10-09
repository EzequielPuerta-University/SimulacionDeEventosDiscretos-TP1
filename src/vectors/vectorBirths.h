#ifndef _VECTOR_BIRTHS_H_
#define _VECTOR_BIRTHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "VectorBirths"


class VectorBirths : public Atomic {
  public:
    VectorBirths(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &applyBirths;
    Port &susceptibleBirths;
    Port &infectedBirths;
    Port &birthsApplied;

    VTime frequency_time;

    double meanBirthRate;
    double standardDeviation;
    double birthRate;
    double susceptiblePopulation;
    double infectedPopulation;
    double susceptibleBirthsAmount;
    double infectedBirthsAmount;
    std::default_random_engine randomGenerator;
};

#endif
