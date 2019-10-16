[top]
components : population@dogsPopulation mockBirths@TupleGenerator mockManager@Generator
out : currentPopulation
link : out@mockManager getPopulation@population
link : queryPopulation@population currentPopulation
link : out@mockBirths setBirths@population

[population]
susceptiblePopulation : 15000
infectedPopulation : 135000

[mockManager]
distribution : Constant
initial : 1
increment : 0
value : 1

[mockBirths]
frequency_time : 00:00:10:00
size : 2
first : 2
second : 8
third : 0
fourth : 0
fifth : 0
sixth : 0
