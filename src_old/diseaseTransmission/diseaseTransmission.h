#ifndef _DISEASE_TRANSMISSION_H_
#define _DISEASE_TRANSMISSION_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "DiseaseTransmission"
#define VECTOR_REQUEST 1
#define HUMANS_REQUEST 2
#define DOGS_REQUEST 3
#define NEW_INFECTED 4

class DiseaseTransmission : public Atomic {
  public:
    DiseaseTransmission(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );
    void vectorsReadyToFeed( const CollectMessage & );
    void requestToHumans( const CollectMessage & );
    void requestToDogs( const CollectMessage & );
    void transmissionForHumans();
    void transmissionForDogs();
    void transmitNewInfected( const CollectMessage & );
    double getDoubleFromRealTupleAt( const ExternalMessage &, int);

  private:
    const Port &newDay;
    const Port &vectorResponse;
    const Port &humansResponse;
    const Port &dogsResponse;
    Port &vectorRequest;
    Port &humansRequest;
    Port &dogsRequest;
    Port &transmitInfectedVectors;
    Port &transmitInfectedDogs;
    Port &transmitInfectedHumans;

    VTime frequency_time;
    int state;
    std::default_random_engine randomGenerator;

    //Constantes ---------------------------------------------------------------
    double transmissionRateOnSusceptibleHumans; //0.000150
    double dogsPreferenceFactor; //2/3

    double transmissionRateFromAcuteHumans; //0.000531
    double standardDeviationFromAcuteHumans; //DV: 0.000159
    std::normal_distribution<double> transmissionRateFromAcuteHumansDistribution;

    double transmissionRateFromIndeterminateHumans; //0.000166
    double standardDeviationFromIndeterminateHumans; //DV: 0.00005
    std::normal_distribution<double> transmissionRateFromIndeterminateHumansDistribution;

    double transmissionRateFromChronicHumans; //0.000166
    double standardDeviationFromChronicHumans; //DV: 0.00005
    std::normal_distribution<double> transmissionRateFromChronicHumansDistribution;

    double transmissionRateFromInfectedDogs; //0.038533
    double standardDeviationFromInfectedDogs; //DV: 0.01156
    std::normal_distribution<double> transmissionRateFromInfectedDogsDistribution;

    double transmissionRateOnSusceptibleDogs; //0.001661
    double standardDeviationOnSusceptibleDogs; //DV: 0.000498
    std::normal_distribution<double> transmissionRateOnSusceptibleDogsDistribution;

    double lagBetweenFeeds; //6 days

    //Variables ----------------------------------------------------------------
    double infectedVectors;
    double nonInfectedVectors;
    double allVectors;
    double susceptibleHumans;
    double acuteHumans;
    double indeterminateHumans;
    double chronicHumans;
    double susceptibleDogs;
    double infectedDogs;

    double infectedVectorsForHumans;
    double nonInfectedVectorsForHumans;
    double amountOfVectorsForHumans;

    double infectedVectorsForDogs;
    double nonInfectedVectorsForDogs;
    double amountOfVectorsForDogs;

    double newInfectedHumans;
    double newInfectedDogs;
    double newInfectedVectorsByHumans;
    double newInfectedVectorsByDogs;
};

#endif
