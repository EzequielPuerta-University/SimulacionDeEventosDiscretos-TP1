#ifndef _DELAY_H_
#define _DELAY_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


class Delay : public Atomic {
  public:
    Delay(const string &name = "Delay" );
    virtual string className() const {  return "Delay" ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &in;
    Port &out;

    VTime delay_time;

    double receivedValue;
};

#endif
