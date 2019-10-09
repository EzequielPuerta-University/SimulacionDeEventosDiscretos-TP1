#include "pmodeladm.h"
#include "register.h"

#include "dogsManager.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<DogsManager>(), ATOMIC_MODEL_NAME);
}
