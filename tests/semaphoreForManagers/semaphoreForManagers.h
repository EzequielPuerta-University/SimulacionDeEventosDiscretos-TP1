#ifndef _SEMAPHORE_FOR_MANAGERS_H_
#define _SEMAPHORE_FOR_MANAGERS_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "SemaphoreForManagers"

class SemaphoreForManagers : public Atomic {
  public:
    SemaphoreForManagers(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &vectorsPopulationComplete;
    const Port &dogsPopulationComplete;
    const Port &humansPopulationComplete;
    Port &newDay;

    VTime frequency_time;

    bool isVectorsPopulationComplete;
    bool isDogsPopulationComplete;
    bool isHumansPopulationComplete;
};

#endif
