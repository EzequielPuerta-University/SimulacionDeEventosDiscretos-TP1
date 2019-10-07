#ifndef _HUMANS_H_
#define _HUMANS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "Humans"


class Humans : public Atomic {
  public:

    Humans(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &births;
    Port &deaths;

    VTime frequency_time;

    int susceptiblePopulation;
    int acutePopulation;
    int indeterminatePopulation;
    int chronicPopulation;

    int susceptiblePopulationImmigrationRate;
    int indeterminatePopulationImmigrationRate;
    int chronicPopulationImmigrationRate;
    int susceptiblePopulationEmigrationRate;
    int indeterminatePopulationEmigrationRate;
    int chronicPopulationEmigrationRate;

    int womanPercentage;
    int susceptibleMotherBirthRate;
    int indeterminateMotherBirthRate;
    int chronicMotherBirthRate;
    int congenitalTransmissionProbability;

    std::uniform_int_distribution<int> dist;
    std::mt19937 rng;
};

#endif
