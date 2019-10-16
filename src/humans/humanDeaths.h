#ifndef _HUMAN_DEATHS_H_
#define _HUMAN_DEATHS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

class HumanDeaths : public Atomic {
  public:
    HumanDeaths(const string &name = "HumanDeaths" );
    virtual string className() const {  return "HumanDeaths" ;}

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
    double acuteMeanRate;
    double acuteStandardDeviation;
    double lastAcuteRate;
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
    int susceptibleDeathsAmount;
    int acuteDeathsAmount;
    int indeterminateDeathsAmount;
    int chronicDeathsAmount;
    std::default_random_engine randomGenerator;
};

#endif
