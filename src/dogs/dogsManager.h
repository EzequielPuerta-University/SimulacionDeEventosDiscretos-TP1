#ifndef _DOGS_MANAGER_H_
#define _DOGS_MANAGER_H_

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

class DogsManager : public Atomic {
  public:
    DogsManager(const string &name = "DogsManager" );
    virtual string className() const {  return "DogsManager" ;}

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
    int individualsInvolvedTotalAmount;
    int susceptiblePopulation;
    int infectedPopulation;
    int susceptibleIndividualsInvolved;
    int infectedIndividualsInvolved;
    int diseaseTransmissions;
    std::default_random_engine randomGenerator;
};

#endif
