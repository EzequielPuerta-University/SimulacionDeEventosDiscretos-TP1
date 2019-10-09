#include "pmodeladm.h"
#include "register.h"

#include "dogDeaths.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<DogDeaths>(), ATOMIC_MODEL_NAME);
}
