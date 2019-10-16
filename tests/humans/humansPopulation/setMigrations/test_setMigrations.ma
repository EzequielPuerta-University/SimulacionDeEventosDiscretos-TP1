[top]
components : population@humansPopulation mockManager@Generator delay@Delay mockMigrations@TupleGenerator
out : currentPopulation
link : out@mockManager in@delay
link : out@delay getPopulation@population
link : queryPopulation@population currentPopulation
link : out@mockMigrations setMigrations@population

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

[mockMigrations]
frequency_time : 00:00:10:00
size : 6
first : 1000
second : 2000
third : 3000
fourth : 4000
fifth : 5000
sixth : 6000
