#ifndef _HUMANS_POPULATION_H_
#define _HUMANS_POPULATION_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

#define PASSIVE 0
#define POPULATION_REQUEST 1
#define INFECTIONS_APPLIED 2

class HumansPopulation : public Atomic {
  public:
    HumansPopulation(const string &name = "HumansPopulation" );
    virtual string className() const {  return "HumansPopulation" ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    double getRate(double, double);
    void applyCures();
    void applyDiseaseProgression();

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
    int acutePopulation;
    int indeterminatePopulation;
    int chronicPopulation;

    int susceptibleImmigrants;
    int susceptibleEmmigrants;
    int indeterminateImmigrants;
    int indeterminateEmmigrants;
    int chronicImmigrants;
    int chronicEmmigrants;

    double acuteCureRate;
    double acuteCureDeviation;
  	double indeterminateCureRate;
  	double indeterminateCureDeviation;

    // double acuteBloodTransmissionRate;
    // double acuteBloodTransmissionDeviation;
    // double indeterminateBloodTransmissionRate;
    // double indeterminateBloodTransmissionDeviation;
    // double chronicBloodTransmissionRate;
    // double chronicBloodTransmissionDeviation;

    double acuteProgressionRate;
    double acuteProgressionDeviation;
    double indeterminateProgressionRate;
    double indeterminateProgressionDeviation;

    int lastInfections;
    std::default_random_engine randomGenerator;
};

#endif
