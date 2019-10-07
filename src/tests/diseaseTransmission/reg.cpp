#include "pmodeladm.h"
#include "register.h"

#include "diseaseTransmission.h"

void register_atomics_on(ParallelModelAdmin &admin){
	admin.registerAtomic(NewAtomicFunction<DiseaseTransmission>(), ATOMIC_MODEL_NAME);
}
