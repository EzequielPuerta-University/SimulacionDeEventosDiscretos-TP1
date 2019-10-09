#include "pmodeladm.h"
#include "register.h"

#include "vectorsManager.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<VectorsManager>(), ATOMIC_MODEL_NAME);
}
