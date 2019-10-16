[top]
components : population@dogsPopulation mockInfections@TupleGenerator
out : currentPopulation lastInfections
link : queryPopulation@population currentPopulation
link : out@mockInfections setInfections@population
link : infectionsApplied@population getPopulation@population
link : infectionsApplied@population lastInfections

[population]
susceptiblePopulation : 15000
infectedPopulation : 135000

[mockInfections]
frequency_time : 00:00:10:00
size : 1
first : 5
second : 0
third : 0
fourth : 0
fifth : 0
sixth : 0
