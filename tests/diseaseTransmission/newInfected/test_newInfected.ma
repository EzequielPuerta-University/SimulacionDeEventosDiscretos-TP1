[top]
components : transmissions@diseaseTransmission vectorsResponse@TupleGenerator humansResponse@TupleGenerator dogsResponse@TupleGenerator
out : transmitInfectedVectors transmitInfectedHumans transmitInfectedDogs
link : out@vectorsResponse vectorResponse@transmissions
link : out@humansResponse humansResponse@transmissions
link : out@dogsResponse dogsResponse@transmissions
link : transmitInfectedVectors@transmissions transmitInfectedVectors
link : transmitInfectedHumans@transmissions transmitInfectedHumans
link : transmitInfectedDogs@transmissions transmitInfectedDogs

[vectorsResponse]
frequency_time : 00:00:10:00
size : 2
first : 1000
second : 500
third : 0
fourth : 0
fifth : 0
sixth : 0

[humansResponse]
frequency_time : 00:00:05:00
size : 4
first : 200
second : 50
third : 150
fourth : 100
fifth : 0
sixth : 0

[dogsResponse]
frequency_time : 00:00:08:00
size : 2
first : 750
second : 250
third : 0
fourth : 0
fifth : 0
sixth : 0
