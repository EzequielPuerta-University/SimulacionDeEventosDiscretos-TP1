[top]
components : births@vectorBirths
out : infectedBirths nonInfectedBirths
link : nonInfectedBirths@births nonInfectedBirths
link : infectedBirths@births infectedBirths

[births]
susceptiblePopulation : 150000
infectedPopulation : 70000
