[top]
components : population@vectorsPopulation mockManager@Generator
out : currentPopulation
link : out@mockManager getPopulation@population
link : queryPopulation@population currentPopulation

[population]
susceptiblePopulation : 700000
infectedPopulation : 300000

[mockManager]
distribution : Constant
initial : 1
increment : 0
value : 1
