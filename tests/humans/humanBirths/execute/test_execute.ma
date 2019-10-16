[top]
components : births@humanBirths mockManager@TupleGenerator
out : setValues applied
link : out@mockManager execute@births
link : setValues@births setValues
link : applied@births applied

[mockManager]
frequency_time : 00:00:10:00
size : 4
first : 600000
second : 30000
third : 120000
fourth : 250000
fifth : 0
sixth : 0
