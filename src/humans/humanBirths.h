#ifndef _HUMAN_BIRTHS_H_
#define _HUMAN_BIRTHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

class HumanBirths : public Atomic {
  public:
    HumanBirths(const string &name = "HumanBirths" );
    virtual string className() const {  return "HumanBirths" ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    double getRate(double, double);

  private:
    const Port &execute;
    Port &setValues;
    Port &applied;

    double susceptibleMeanRate;
    double susceptibleStandardDeviation;
    double lastSusceptibleRate;
    double indeterminateMeanRate;
    double indeterminateStandardDeviation;
    double lastIndeterminateRate;
    double chronicMeanRate;
    double chronicStandardDeviation;
    double lastChronicRate;

    int susceptiblePopulation;
    int acutePopulation;
    int indeterminatePopulation;
    int chronicPopulation;
    int susceptibleBirthsAmount;
    int indeterminateBirthsAmount;
    int chronicBirthsAmount;
    double congenitalTransmissionProbability;
    std::default_random_engine randomGenerator;
};

#endif
