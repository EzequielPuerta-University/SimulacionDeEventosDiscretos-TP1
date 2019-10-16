[top]
components : manager@humansManager population@humansPopulation births@humanBirths deaths@humanDeaths migrations@humanMigrations mockGenerator@TupleGenerator mockGenerator2@TupleGenerator delay@Delay
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
susceptiblePopulation : 600000
acutePopulation : 30000
indeterminatePopulation : 120000
chronicPopulation : 250000

[mockGenerator]
frequency_time : 00:00:10:00
size : 1
first : 1000
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
first : 250
second : 0
third : 0
fourth : 0
fifth : 0
sixth : 0
