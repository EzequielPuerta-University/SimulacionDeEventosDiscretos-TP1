#ifndef _VECTORS_MANAGER_H_
#define _VECTORS_MANAGER_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "VectorsManager"
#define SUSCEPTIBLE_REQUEST 1
#define INFECTED_REQUEST 2
#define PREPARE_RESPONSE 3
#define NEW_INFECTIONS 4
#define MIGRATIONS 5
#define BIRTHS 6
#define DEATHS 7
#define FINISH 8

class VectorsManager : public Atomic {
  public:
    VectorsManager(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    void prepareVectorsToFeed( const CollectMessage & );
    double getDoubleFromRealTupleAt( const ExternalMessage &, int);

  private:
    const Port &vectorRequestPercentage;
    const Port &susceptibleResponse;
    const Port &infectedResponse;
    const Port &newInfections;
    const Port &infectionsApplied;
    const Port &migrationsApplied;
    const Port &birthsApplied;
    const Port &deathsApplied;
    Port &vectorResponse;
    Port &susceptibleRequest;
    Port &infectedRequest;
    Port &applyNewInfections;
    Port &applyMigrations;
    Port &applyBirths;
    Port &applyDeaths;
    Port &dayFinished;

    VTime frequency_time;

    int state;
    double vectorPercentage;
    double susceptiblePopulation;
    double infectedPopulation;
    double susceptibleVectorsToFeed;
    double infectedVectorsToFeed;
    double diseaseTransmissions;
    Tuple<Real> currentPopulation;
    std::default_random_engine randomGenerator;
};

#endif
