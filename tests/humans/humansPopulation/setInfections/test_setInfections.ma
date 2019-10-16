[top]
components : population@humansPopulation mockManager@Generator delay@Delay mockInfections@TupleGenerator
out : currentPopulation lastInfections
link : out@mockManager getPopulation@population
link : queryPopulation@population currentPopulation
link : out@mockInfections in@delay
link : out@delay setInfections@population
link : infectionsApplied@population lastInfections

[population]
susceptiblePopulation : 600000
acutePopulation : 30000
indeterminatePopulation : 120000
chronicPopulation : 250000

[mockManager]
distribution : Constant
initial : 1
increment : 0
value : 1

[delay]
delay_time : 00:00:05:00

[mockInfections]
frequency_time : 00:00:10:00
size : 1
first : 500
second : 0
third : 0
fourth : 0
fifth : 0
sixth : 0
