[top]
components : transmissions@diseaseTransmission Vectors Dogs Humans
out : vectorsPopulation dogsPopulation humansPopulation

link : dayFinished@Vectors vectorsPopulation
link : dayFinished@Dogs dogsPopulation
link : dayFinished@Humans humansPopulation

link : dogsRequest@transmissions request@Dogs
link : vectorRequest@transmissions request@Vectors
link : humansRequest@transmissions request@Humans
link : response@Dogs dogsResponse@transmissions
link : response@Vectors vectorResponse@transmissions
link : response@Humans humansResponse@transmissions
link : transmitInfectedDogs@transmissions infections@Dogs
link : transmitInfectedVectors@transmissions infections@Vectors
link : transmitInfectedHumans@transmissions infections@Humans

[Dogs]
components : manager@dogsManager dogsPopulation@dogsPopulation migrations@dogMigrations births@dogBirths deaths@dogDeaths
in : initialSusceptiblePopulation initialInfectedPopulation request infections
out : currentPopulation response dayFinished
link : request execute@manager
link : getPopulation@manager getPopulation@dogsPopulation
link : queryPopulation@dogsPopulation population@manager
link : individualsInvolved@manager response
link : infections setInfections@manager
link : applyNewInfections@manager setInfections@dogsPopulation
link : infectionsApplied@dogsPopulation infectionsApplied@manager
link : applyMigrations@manager execute@migrations
link : setValues@migrations setMigrations@dogsPopulation
link : applied@migrations migrationsApplied@manager
link : applyBirths@manager execute@births
link : setValues@births setBirths@dogsPopulation
link : applied@births birthsApplied@manager
link : applyDeaths@manager execute@deaths
link : setValues@deaths setDeaths@dogsPopulation
link : applied@deaths deathsApplied@manager
link : finished@manager dayFinished

[dogsPopulation]
susceptiblePopulation : 12000
infectedPopulation : 18000

[Vectors]
components : manager@vectorsManager vectorsPopulation@vectorsPopulation migrations@vectorMigrations births@vectorBirths deaths@vectorDeaths
in : initialSusceptiblePopulation initialInfectedPopulation request infections
out : currentPopulation response dayFinished
link : request execute@manager
link : getPopulation@manager getPopulation@vectorsPopulation
link : queryPopulation@vectorsPopulation population@manager
link : individualsInvolved@manager response
link : infections setInfections@manager
link : applyNewInfections@manager setInfections@vectorsPopulation
link : infectionsApplied@vectorsPopulation infectionsApplied@manager
link : applyMigrations@manager execute@migrations
link : setValues@migrations setMigrations@vectorsPopulation
link : applied@migrations migrationsApplied@manager
link : applyBirths@manager execute@births
link : setValues@births setBirths@vectorsPopulation
link : applied@births birthsApplied@manager
link : applyDeaths@manager execute@deaths
link : setValues@deaths setDeaths@vectorsPopulation
link : applied@deaths deathsApplied@manager
link : finished@manager dayFinished

[vectorsPopulation]
susceptiblePopulation : 70000
infectedPopulation : 30000

[Humans]
components : manager@humansManager humansPopulation@humansPopulation migrations@humanMigrations births@humanBirths deaths@humanDeaths
in : initialSusceptiblePopulation initialInfectedPopulation request infections
out : currentPopulation response dayFinished
link : request execute@manager
link : getPopulation@manager getPopulation@humansPopulation
link : queryPopulation@humansPopulation population@manager
link : individualsInvolved@manager response
link : infections setInfections@manager
link : applyNewInfections@manager setInfections@humansPopulation
link : infectionsApplied@humansPopulation infectionsApplied@manager
link : applyMigrations@manager execute@migrations
link : setValues@migrations setMigrations@humansPopulation
link : applied@migrations migrationsApplied@manager
link : applyBirths@manager execute@births
link : setValues@births setBirths@humansPopulation
link : applied@births birthsApplied@manager
link : applyDeaths@manager execute@deaths
link : setValues@deaths setDeaths@humansPopulation
link : applied@deaths deathsApplied@manager
link : finished@manager dayFinished

[humansPopulation]
susceptiblePopulation : 6000
acutePopulation : 50
indeterminatePopulation : 1830
chronicPopulation : 1220
