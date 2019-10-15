#ifndef _DOG_DEATHS_H_
#define _DOG_DEATHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

class DogDeaths : public Atomic {
  public:
    DogDeaths(const string &name = "DogDeaths" );
    virtual string className() const {  return "DogDeaths" ;}

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
