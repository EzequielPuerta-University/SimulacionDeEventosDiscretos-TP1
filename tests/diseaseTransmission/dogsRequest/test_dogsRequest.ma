[top]
components : transmissions@diseaseTransmission vectorsResponse@TupleGenerator humansResponse@TupleGenerator
out : dogsRequest
link : out@vectorsResponse vectorResponse@transmissions
link : out@humansResponse humansResponse@transmissions
link : dogsRequest@transmissions dogsRequest

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
