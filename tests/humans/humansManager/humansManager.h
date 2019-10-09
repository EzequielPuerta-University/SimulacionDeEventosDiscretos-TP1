#ifndef _HUMANS_MANAGER_H_
#define _HUMANS_MANAGER_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "HumansManager"
#define CURES 0
#define SUSCEPTIBLE_REQUEST 1
#define ACUTE_REQUEST 2
#define INDETERMINATE_REQUEST 3
#define CHRONIC_REQUEST 4
#define PREPARE_RESPONSE 5
#define NEW_INFECTIONS 6
#define MIGRATIONS 7
#define BIRTHS 8
#define DEATHS 9
#define FINISH 10

class HumansManager : public Atomic {
  public:
    HumansManager(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    void prepareHumansToBeBitten( const CollectMessage & );
    double getDoubleFromRealTupleAt( const ExternalMessage &, int);

  private:
    const Port &humansToBeBittenRequest;
    const Port &susceptibleResponse;
    const Port &acuteResponse;
    const Port &indeterminateResponse;
    const Port &chronicResponse;
    const Port &newInfections;
    const Port &curesApplied;
    const Port &infectionsApplied;
    const Port &migrationsApplied;
    const Port &birthsApplied;
    const Port &deathsApplied;
    Port &humansResponse;
    Port &susceptibleRequest;
    Port &acuteRequest;
    Port &indeterminateRequest;
    Port &chronicRequest;
    Port &applyCures;
    Port &applyNewInfections;
    Port &applyMigrations;
    Port &applyBirths;
    Port &applyDeaths;
    Port &dayFinished;

    VTime frequency_time;

    int state;
    double humansToBeBittenAmount;
    double susceptiblePopulation;
    double acutePopulation;
    double indeterminatePopulation;
    double chronicPopulation;
    double susceptibleHumansToBeBitten;
    double acuteHumansToBeBitten;
    double indeterminateHumansToBeBitten;
    double chronicHumansToBeBitten;
    double diseaseTransmissions;
    Tuple<Real> currentPopulation;
    std::default_random_engine randomGenerator;
};

#endif
