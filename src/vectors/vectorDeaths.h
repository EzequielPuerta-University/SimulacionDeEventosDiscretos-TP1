#ifndef _VECTOR_DEATHS_H_
#define _VECTOR_DEATHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

class VectorDeaths : public Atomic {
  public:
    VectorDeaths(const string &name = "VectorDeaths" );
    virtual string className() const {  return "VectorDeaths" ;}

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
    int susceptibleDeathsAmount;
    int infectedDeathsAmount;
    std::default_random_engine randomGenerator;
};

#endif
