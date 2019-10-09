#include "pmodeladm.h"
#include "register.h"

#include "humansManager.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<HumansManager>(), ATOMIC_MODEL_NAME);
}
