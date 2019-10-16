#ifndef _DISEASE_TRANSMISSION_H_
#define _DISEASE_TRANSMISSION_H_

#include <random>

#include "atomic.h"
#include "VTime.h"

#define VECTOR_REQUEST 1
#define HUMANS_REQUEST 2
#define DOGS_REQUEST 3
#define NEW_INFECTED 4

class DiseaseTransmission : public Atomic {
  public:
    DiseaseTransmission(const string &name = "DiseaseTransmission" );
    virtual string className() const {  return "DiseaseTransmission" ;}

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
    double getRate(double, double);

  private:
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
    double transmissionRateFromInfectedVectorsToSusceptibleHumans;
    double dogsPreferenceFactor;

    double transmissionRateFromAcuteHumans;
    double standardDeviationFromAcuteHumans;

    double transmissionRateFromIndeterminateHumans;
    double standardDeviationFromIndeterminateHumans;

    double transmissionRateFromChronicHumans;
    double standardDeviationFromChronicHumans;

    double transmissionRateFromInfectedDogs;
    double standardDeviationFromInfectedDogs;

    double transmissionRateOnSusceptibleDogs;
    double standardDeviationOnSusceptibleDogs;

    double lagBetweenFeeds; //6 days

    //Variables ----------------------------------------------------------------
    int infectedVectors;
    int nonInfectedVectors;
    int allVectors;
    int susceptibleHumans;
    int acuteHumans;
    int indeterminateHumans;
    int chronicHumans;
    int susceptibleDogs;
    int infectedDogs;

    int infectedVectorsForHumans;
    int nonInfectedVectorsForHumans;
    int amountOfVectorsForHumans;

    int infectedVectorsForDogs;
    int nonInfectedVectorsForDogs;
    int amountOfVectorsForDogs;

    int newInfectedHumans;
    int newInfectedDogs;
    int newInfectedVectorsByHumans;
    int newInfectedVectorsByDogs;
};

#endif
