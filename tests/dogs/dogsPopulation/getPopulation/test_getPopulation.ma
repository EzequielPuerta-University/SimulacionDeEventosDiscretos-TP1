[top]
components : population@dogsPopulation mockManager@Generator
out : currentPopulation
link : out@mockManager getPopulation@population
link : queryPopulation@population currentPopulation

[population]
susceptiblePopulation : 15000
infectedPopulation : 135000

[mockManager]
distribution : Constant
initial : 1
increment : 0
value : 1
