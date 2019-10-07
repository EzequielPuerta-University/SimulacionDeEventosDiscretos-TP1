[top]
components : infectedPopulation@infectedDogs
out : deaths currentPopulation
link : deaths@infectedPopulation deaths
link : currentPopulation@infectedPopulation currentPopulation

[infectedPopulation]
population : 70000
