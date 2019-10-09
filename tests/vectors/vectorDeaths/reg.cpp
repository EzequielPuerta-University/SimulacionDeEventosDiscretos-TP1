#include "pmodeladm.h"
#include "register.h"

#include "vectorDeaths.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<VectorDeaths>(), ATOMIC_MODEL_NAME);
}
