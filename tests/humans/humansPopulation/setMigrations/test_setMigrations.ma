[top]
components : population@dogsPopulation mockMigrations@TupleGenerator mockManager@Generator
out : currentPopulation
link : out@mockManager getPopulation@population
link : queryPopulation@population currentPopulation
link : out@mockMigrations setMigrations@population

[population]
susceptiblePopulation : 15000
infectedPopulation : 135000

[mockManager]
distribution : Constant
initial : 1
increment : 0
value : 1

[mockMigrations]
frequency_time : 00:00:10:00
size : 4
first : 10
second : 7
third : 4
fourth : 2
fifth : 0
