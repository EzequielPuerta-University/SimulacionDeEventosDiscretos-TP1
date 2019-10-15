[top]
components : population@humansPopulation mockManager@Generator
out : currentPopulation
link : out@mockManager getPopulation@population
link : queryPopulation@population currentPopulation

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
