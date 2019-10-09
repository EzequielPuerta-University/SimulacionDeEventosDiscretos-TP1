#include "pmodeladm.h"
#include "register.h"

#include "dogMigrations.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<DogMigrations>(), ATOMIC_MODEL_NAME);
}
