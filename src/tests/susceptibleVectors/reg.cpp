#include "pmodeladm.h"
#include "register.h"

#include "susceptibleVectors.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<SusceptibleVectors>(), ATOMIC_MODEL_NAME);
}
