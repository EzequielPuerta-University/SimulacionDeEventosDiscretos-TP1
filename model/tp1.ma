[top]
components : transmissions@diseaseTransmission Vectors Dogs Humans semaphore@semaphoreForManagers
out : susceptibleVectors infectedVectors susceptibleDogs infectedDogs

link : dayFinished@Vectors vectorsPopulationComplete@semaphore
link : dayFinished@Dogs dogsPopulationComplete@semaphore
link : dayFinished@Humans humansPopulationComplete@semaphore
link : newDay@semaphore newDay@transmissions

link : dogsRequest@transmissions dogsRequest@Dogs
link : vectorRequest@transmissions vectorsRequest@Vectors
link : humansRequest@transmissions humansRequest@Humans
link : dogsResponse@Dogs dogsResponse@transmissions
link : vectorsResponse@Vectors vectorResponse@transmissions
link : humansResponse@Humans humansResponse@transmissions
link : transmitInfectedDogs@transmissions infections@Dogs
link : transmitInfectedVectors@transmissions infections@Vectors
link : transmitInfectedHumans@transmissions infections@Humans

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
link : infectionsApplied@susceptibles infected@infected
link : infectionsApplied@infected infectionsApplied@manager
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

[Vectors]
components : manager@vectorsManager susceptibles@susceptibleVectors infected@infectedVectors migrations@vectorMigrations births@vectorBirths deaths@vectorDeaths
in : initialSusceptiblePopulation initialInfectedPopulation vectorsRequest infections
out : currentPopulation vectorsResponse dayFinished
link : vectorsRequest vectorRequestPercentage@manager
link : susceptibleRequest@manager populationRequest@susceptibles
link : currentPopulation@susceptibles susceptibleResponse@manager
link : infectedRequest@manager populationRequest@infected
link : currentPopulation@infected infectedResponse@manager
link : vectorResponse@manager vectorsResponse
link : infections newInfections@manager
link : applyNewInfections@manager infected@susceptibles
link : infectionsApplied@susceptibles infected@infected
link : infectionsApplied@infected infectionsApplied@manager
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

[Humans]
components : manager@mockManager
in : initialSusceptiblePopulation initialInfectedPopulation humansRequest infections
out : currentPopulation humansResponse dayFinished
link : humansRequest humansRequest@manager

[mockmanager]
distribution : Constant
initial : 0
increment : 0
value : 0
