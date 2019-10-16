#include "utils.h"
#include "atomic.h"


int getValueFromTupleAt(const ExternalMessage &msg, int index){
	return (Tuple<Real>::from_value(msg.value())[index]).value();
}

int getValueFrom(const ExternalMessage &msg){
	return Real::from_value(msg.value()).value();
}

double getValueAsDoubleFrom(const ExternalMessage &msg){
	return Real::from_value(msg.value()).value();
}

Real asTuple(int first){
	return Real(first);
}

Tuple<Real> asTuple(int first, int second){
	Tuple<Real> tuple{Real(first), Real(second)};
	return tuple;
}

Tuple<Real> asTuple(int first, int second, int third){
	Tuple<Real> tuple{Real(first), Real(second), Real(third)};
	return tuple;
}

Tuple<Real> asTuple(int first, int second, int third, int fourth){
	Tuple<Real> tuple{Real(first), Real(second), Real(third), Real(fourth)};
	return tuple;
}

Tuple<Real> asTuple(int first, int second, int third, int fourth, int fifth){
	Tuple<Real> tuple{Real(first), Real(second), Real(third), Real(fourth), Real(fifth)};
	return tuple;
}

Tuple<Real> asTuple(int first, int second, int third, int fourth, int fifth, int sixth){
	Tuple<Real> tuple{Real(first), Real(second), Real(third), Real(fourth), Real(fifth), Real(sixth)};
	return tuple;
}

Tuple<Real> asTuple(int first, int second, int third, int fourth, int fifth, int sixth, int seventh){
	Tuple<Real> tuple{Real(first), Real(second), Real(third), Real(fourth), Real(fifth), Real(sixth), Real(seventh)};
	return tuple;
}

Tuple<Real> asTuple(int first, int second, int third, int fourth, int fifth, int sixth, int seventh, int eighth){
	Tuple<Real> tuple{Real(first), Real(second), Real(third), Real(fourth), Real(fifth), Real(sixth), Real(seventh), Real(eighth)};
	return tuple;
}
