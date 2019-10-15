#ifndef _DOGS_POPULATION_H_
#define _DOGS_POPULATION_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "DogsPopulation"
#define PASSIVE 0
#define POPULATION_REQUEST 1
#define INFECTIONS_APPLIED 2

class DogsPopulation : public Atomic {
  public:
    DogsPopulation(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &setBirths;
    const Port &setMigrations;
    const Port &setInfections;
    const Port &setDeaths;
    Port &infectionsApplied;
    const Port &getPopulation;
    Port &queryPopulation;

    int state;
    int susceptiblePopulation;
    int infectedPopulation;
    int susceptibleImmigrants;
    int susceptibleEmmigrants;
    int infectedImmigrants;
    int infectedEmmigrants;
    int lastInfections;
};

#endif
