[top]
components : susceptiblePopulation@susceptibleDogs
out : infected deaths currentPopulation
link : infected@susceptiblePopulation infected
link : deaths@susceptiblePopulation deaths
link : currentPopulation@susceptiblePopulation currentPopulation

[susceptiblePopulation]
population : 150000
