#ifndef _TUPLE_GENERATOR_H_
#define _TUPLE_GENERATOR_H_

#include <random>

#include "atomic.h"
#include "VTime.h"


class TupleGenerator : public Atomic {
  public:
    TupleGenerator(const string &name = "TupleGenerator" );
    virtual string className() const {  return "TupleGenerator" ;}

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &setByTuple;
    Port &out;

    VTime frequency_time;

    int size;
    int first;
    int second;
    int third;
    int fourth;
    int fifth;
    int sixth;
};

#endif
