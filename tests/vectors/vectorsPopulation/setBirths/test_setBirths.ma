[top]
components : population@vectorsPopulation mockBirths@TupleGenerator mockManager@Generator
out : currentPopulation
link : out@mockManager getPopulation@population
link : queryPopulation@population currentPopulation
link : out@mockBirths setBirths@population

[population]
susceptiblePopulation : 700000
infectedPopulation : 300000

[mockManager]
distribution : Constant
initial : 1
increment : 0
value : 1

[mockBirths]
frequency_time : 00:00:10:00
size : 2
first : 1000
second : 500
third : 0
fourth : 0
fifth : 0
