#include "pmodeladm.h"
#include "register.h"

#include "vectorBirths.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<VectorBirths>(), ATOMIC_MODEL_NAME);
}
