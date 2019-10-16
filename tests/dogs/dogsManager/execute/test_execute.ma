[top]
components : manager@dogsManager population@dogsPopulation births@dogBirths deaths@dogDeaths migrations@dogMigrations mockGenerator@TupleGenerator mockGenerator2@TupleGenerator delay@Delay
out : currentBirths currentDeaths currentMigrations currentInfections currentPopulation
link : out@mockGenerator execute@manager
link : getPopulation@manager getPopulation@population
link : queryPopulation@population population@manager
link : queryPopulation@population currentPopulation
link : out@mockGenerator2 in@delay
link : out@delay setInfections@manager
link : out@delay currentInfections
link : applyNewInfections@manager setInfections@population
link : infectionsApplied@population infectionsApplied@manager

link : applyMigrations@manager execute@migrations
link : setValues@migrations setMigrations@population
link : setValues@migrations currentMigrations
link : applied@migrations migrationsApplied@manager

link : applyBirths@manager execute@births
link : setValues@births setBirths@population
link : setValues@births currentBirths
link : applied@births birthsApplied@manager

link : applyDeaths@manager execute@deaths
link : setValues@deaths setDeaths@population
link : setValues@deaths currentDeaths
link : applied@deaths deathsApplied@manager

[population]
susceptiblePopulation : 15000
infectedPopulation : 135000

[mockGenerator]
frequency_time : 00:00:10:00
size : 1
first : 50
second : 0
third : 0
fourth : 0
fifth : 0
sixth : 0

[delay]
delay_time : 00:00:05:00

[mockGenerator2]
frequency_time : 00:00:10:00
size : 1
first : 20
second : 0
third : 0
fourth : 0
fifth : 0
sixth : 0
