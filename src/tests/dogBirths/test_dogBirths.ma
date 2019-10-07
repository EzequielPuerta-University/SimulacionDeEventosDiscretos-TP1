[top]
components : births@dogBirths
out : infectedBirths nonInfectedBirths
link : nonInfectedBirths@births nonInfectedBirths
link : infectedBirths@births infectedBirths

[births]
susceptiblePopulation : 150000
infectedPopulation : 70000
