[top]
components : population@humansPopulation mockDeaths@TupleGenerator mockManager@Generator
out : currentPopulation
link : out@mockManager getPopulation@population
link : queryPopulation@population currentPopulation
link : out@mockDeaths setDeaths@population

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

[mockDeaths]
frequency_time : 00:00:10:00
size : 4
first : 2000
second : 250
third : 750
fourth : 1000
fifth : 0
sixth : 0
