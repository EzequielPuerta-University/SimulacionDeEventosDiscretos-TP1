[top]
components : migrations@dogMigrations mockManager@TupleGenerator
out : setValues applied
link : out@mockManager execute@migrations
link : setValues@migrations setValues
link : applied@migrations applied

[mockManager]
frequency_time : 00:00:10:00
size : 2
first : 15000
second : 135000
third : 0
fourth : 0
fifth : 0
sixth : 0
