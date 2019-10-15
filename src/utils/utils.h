#ifndef _UTILS_H
#define _UTILS_H
#include "atomic.h"

int getValueFromTupleAt( const ExternalMessage &, int);
int getValueFrom(const ExternalMessage &msg);
Real asTuple(int);
Tuple<Real> asTuple(int, int);
Tuple<Real> asTuple(int, int, int);
Tuple<Real> asTuple(int, int, int, int);
Tuple<Real> asTuple(int, int, int, int, int);
Tuple<Real> asTuple(int, int, int, int, int, int);
Tuple<Real> asTuple(int, int, int, int, int, int, int);
Tuple<Real> asTuple(int, int, int, int, int, int, int, int);

#endif
