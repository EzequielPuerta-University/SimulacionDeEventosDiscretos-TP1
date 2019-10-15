#ifndef _VECTORS_POPULATION_H_
#define _VECTORS_POPULATION_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

#define PASSIVE 0
#define POPULATION_REQUEST 1
#define INFECTIONS_APPLIED 2

class VectorsPopulation : public Atomic {
  public:
    VectorsPopulation(const string &name = "VectorsPopulation" );
    virtual string className() const {  return "VectorsPopulation" ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &setBirths;
    const Port &setDeaths;
    const Port &setMigrations;
    const Port &setInfections;
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
