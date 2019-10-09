#include "pmodeladm.h"
#include "register.h"

#include "dogBirths.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<DogBirths>(), ATOMIC_MODEL_NAME);
}
