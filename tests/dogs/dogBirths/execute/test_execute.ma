[top]
components : births@dogBirths mockManager@TupleGenerator
out : setValues applied
link : out@mockManager execute@births
link : setValues@births setValues
link : applied@births applied
link : applied@births setByTuple@mockManager

[mockManager]
frequency_time : 00:00:10:00
size : 2
first : 15000
second : 135000
third : 0
fourth : 0
fifth : 0
sixth : 0
