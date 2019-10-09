#include "pmodeladm.h"
#include "register.h"

#include "semaphoreForManagers.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<SemaphoreForManagers>(), ATOMIC_MODEL_NAME);
}
