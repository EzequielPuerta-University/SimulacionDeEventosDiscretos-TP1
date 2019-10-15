#include "pmodeladm.h"
#include "register.h"

//MODELOS
#include "vectorsPopulation.h"
#include "vectorBirths.h"
#include "vectorDeaths.h"
#include "vectorMigrations.h"
#include "vectorsManager.h"

#include "dogsPopulation.h"
#include "dogBirths.h"
#include "dogDeaths.h"
#include "dogMigrations.h"
#include "dogsManager.h"

#include "humansPopulation.h"

//TESTS
#include "tupleGenerator.h"
#include "delay.h"

void register_atomics_on(ParallelModelAdmin &admin){
	//MODELOS
	admin.registerAtomic(NewAtomicFunction<VectorsPopulation>(), "VectorsPopulation");
	admin.registerAtomic(NewAtomicFunction<VectorBirths>(), "VectorBirths");
	admin.registerAtomic(NewAtomicFunction<VectorDeaths>(), "VectorDeaths");
	admin.registerAtomic(NewAtomicFunction<VectorMigrations>(), "VectorMigrations");
	admin.registerAtomic(NewAtomicFunction<VectorsManager>(), "VectorsManager");

	admin.registerAtomic(NewAtomicFunction<DogsPopulation>(), "DogsPopulation");
	admin.registerAtomic(NewAtomicFunction<DogBirths>(), "DogBirths");
	admin.registerAtomic(NewAtomicFunction<DogDeaths>(), "DogDeaths");
	admin.registerAtomic(NewAtomicFunction<DogMigrations>(), "DogMigrations");
	admin.registerAtomic(NewAtomicFunction<DogsManager>(), "DogsManager");

	admin.registerAtomic(NewAtomicFunction<HumansPopulation>(), "HumansPopulation");

	//TESTS
	admin.registerAtomic(NewAtomicFunction<TupleGenerator>(), "TupleGenerator");
	admin.registerAtomic(NewAtomicFunction<Delay>(), "Delay");
}
