#include "pmodeladm.h"
#include "register.h"

// #include "humanBirths.h"
// #include "susceptibleHumans.h"
// #include "infectedAcuteHumans.h"
// #include "infectedIndeterminateHumans.h"
// #include "infectedChronicHumans.h"
// #include "humanDeaths.h"

#include "diseaseTransmission.h"
#include "semaphoreForManagers.h"

#include "dogs/dogBirths.h"
#include "dogs/dogDeaths.h"
#include "dogs/dogMigrations.h"
#include "dogs/susceptibleDogs.h"
#include "dogs/infectedDogs.h"
#include "dogs/dogsManager.h"

void register_atomics_on(ParallelModelAdmin &admin){
	// admin.registerAtomic(NewAtomicFunction<HumanBirths>(), ATOMIC_MODEL_NAME);
	// admin.registerAtomic(NewAtomicFunction<SusceptibleHumans>(), ATOMIC_MODEL_NAME);
	// admin.registerAtomic(NewAtomicFunction<InfectedAcuteHumans>(), ATOMIC_MODEL_NAME);
	// admin.registerAtomic(NewAtomicFunction<InfectedIndeterminateHumans>(), ATOMIC_MODEL_NAME);
	// admin.registerAtomic(NewAtomicFunction<InfectedChronicHumans>(), ATOMIC_MODEL_NAME);
	// admin.registerAtomic(NewAtomicFunction<HumanDeaths>(), ATOMIC_MODEL_NAME);

	admin.registerAtomic(NewAtomicFunction<DiseaseTransmission>(), ATOMIC_MODEL_NAME);
	admin.registerAtomic(NewAtomicFunction<SemaphoreForManagers>(), ATOMIC_MODEL_NAME);

	admin.registerAtomic(NewAtomicFunction<DogBirths>(), ATOMIC_MODEL_NAME);
	admin.registerAtomic(NewAtomicFunction<DogDeaths>(), ATOMIC_MODEL_NAME);
	admin.registerAtomic(NewAtomicFunction<DogMigrations>(), ATOMIC_MODEL_NAME);
	admin.registerAtomic(NewAtomicFunction<SusceptibleDogs>(), ATOMIC_MODEL_NAME);
	admin.registerAtomic(NewAtomicFunction<InfectedDogs>(), ATOMIC_MODEL_NAME);
	admin.registerAtomic(NewAtomicFunction<DogsManager>(), ATOMIC_MODEL_NAME);
}
