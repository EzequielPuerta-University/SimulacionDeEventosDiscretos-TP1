#ifndef _VECTORS_MANAGER_H_
#define _VECTORS_MANAGER_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

#define POPULATION_REQUEST 1
#define PREPARE_RESPONSE 2
#define NEW_INFECTIONS 3
#define MIGRATIONS 4
#define BIRTHS 5
#define DEATHS 6
#define FINISH 7

class VectorsManager : public Atomic {
  public:
    VectorsManager(const string &name = "VectorsManager" );
    virtual string className() const {  return "VectorsManager" ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    void prepareIndividualsInvolved( const CollectMessage & );

  private:
    const Port &execute;
    Port &getPopulation;
    const Port &population;
    Port &individualsInvolved;
    const Port &setInfections;
    Port &applyNewInfections;
    const Port &infectionsApplied;
    Port &applyMigrations;
    const Port &migrationsApplied;
    Port &applyBirths;
    const Port &birthsApplied;
    Port &applyDeaths;
    const Port &deathsApplied;
    Port &finished;

    int state;
    int vectorPercentage;
    int susceptiblePopulation;
    int infectedPopulation;
    int susceptibleIndividualsInvolved;
    int infectedIndividualsInvolved;
    int diseaseTransmissions;
    std::default_random_engine randomGenerator;
};

#endif
