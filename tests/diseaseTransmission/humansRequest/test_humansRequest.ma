[top]
components : transmissions@diseaseTransmission mockManager@TupleGenerator
out : humansRequest
link : out@mockManager vectorResponse@transmissions
link : humansRequest@transmissions humansRequest

[mockManager]
frequency_time : 00:00:10:00
size : 2
first : 1000
second : 500
third : 0
fourth : 0
fifth : 0
sixth : 0
