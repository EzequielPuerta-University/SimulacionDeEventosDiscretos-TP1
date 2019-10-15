#ifndef _DOGS_MANAGER_H_
#define _DOGS_MANAGER_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "DogsManager"
#define SUSCEPTIBLE_REQUEST 1
#define INFECTED_REQUEST 2
#define PREPARE_RESPONSE 3
#define NEW_INFECTIONS 4
#define MIGRATIONS 5
#define BIRTHS 6
#define DEATHS 7
#define FINISH 8

class DogsManager : public Atomic {
  public:
    DogsManager(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    void prepareDogsToBeBitten( const CollectMessage & );
    double getDoubleFromRealTupleAt( const ExternalMessage &, int);

  private:
    const Port &dogsToBeBittenRequest;
    const Port &susceptibleResponse;
    const Port &infectedResponse;
    const Port &newInfections;
    const Port &infectionsApplied;
    const Port &migrationsApplied;
    const Port &birthsApplied;
    const Port &deathsApplied;
    Port &dogsResponse;
    Port &susceptibleRequest;
    Port &infectedRequest;
    Port &applyNewInfections;
    Port &applyMigrations;
    Port &applyBirths;
    Port &applyDeaths;
    Port &dayFinished;

    VTime frequency_time;

    int state;
    double dogsToBeBittenAmount;
    double susceptiblePopulation;
    double infectedPopulation;
    double susceptibleDogsToBeBitten;
    double infectedDogsToBeBitten;
    double diseaseTransmissions;
    Tuple<Real> currentPopulation;
    std::default_random_engine randomGenerator;
};

#endif
