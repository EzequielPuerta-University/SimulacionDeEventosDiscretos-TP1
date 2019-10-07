#include "pmodeladm.h"
#include "register.h"

#include "susceptibleDogs.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<SusceptibleDogs>(), ATOMIC_MODEL_NAME);
}
