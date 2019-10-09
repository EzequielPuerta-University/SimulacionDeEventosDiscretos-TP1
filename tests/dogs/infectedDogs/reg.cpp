#include "pmodeladm.h"
#include "register.h"

#include "infectedDogs.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<InfectedDogs>(), ATOMIC_MODEL_NAME);
}
