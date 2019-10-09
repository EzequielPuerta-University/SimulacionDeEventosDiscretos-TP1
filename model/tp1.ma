[top]
components : transmissions@diseaseTransmission Dogs semaphore@semaphoreForManagers
out : susceptibleDogs infectedDogs
link : newDay@semaphore newDay@transmissions
link : dayFinished@Dogs dogsPopulationComplete@semaphore
link : dogsRequest@transmissions dogsRequest@Dogs
link : dogsResponse@Dogs dogsResponse@transmissions
link : transmitInfectedDogs@transmissions infections@Dogs

[Dogs]
components : manager@dogsManager susceptibles@susceptibleDogs infected@infectedDogs migrations@dogMigrations births@dogBirths deaths@dogDeaths
in : initialSusceptiblePopulation initialInfectedPopulation dogsRequest infections
out : currentPopulation dogsResponse dayFinished
link : dogsRequest dogsToBeBittenRequest@manager
link : susceptibleRequest@manager populationRequest@susceptibles
link : currentPopulation@susceptibles susceptibleResponse@manager
link : infectedRequest@manager populationRequest@infected
link : currentPopulation@infected infectedResponse@manager
link : dogsResponse@manager dogsResponse
link : infections newInfections@manager
link : applyNewInfections@manager infected@susceptibles
link : infectionsApplied@susceptibles infectionsApplied@manager
link : applyMigrations@manager applyMigrations@migrations
link : susceptibleMigrations@migrations migrations@susceptibles
link : infectedMigrations@migrations migrations@infected
link : migrationsApplied@migrations migrationsApplied@manager
link : applyBirths@manager applyBirths@births
link : susceptibleBirths@births births@susceptibles
link : infectedBirths@births births@infected
link : birthsApplied@births birthsApplied@manager
link : applyDeaths@manager applyDeaths@deaths
link : susceptibleDeaths@deaths deaths@susceptibles
link : infectedDeaths@deaths deaths@infected
link : deathsApplied@deaths deathsApplied@manager
link : dayFinished@manager dayFinished

[susceptibles]
population : 15000

[infected]
population : 135000
