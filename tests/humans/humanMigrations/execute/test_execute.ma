[top]
components : migrations@humanMigrations mockManager@TupleGenerator
out : setValues applied
link : out@mockManager execute@migrations
link : setValues@migrations setValues
link : applied@migrations applied

[mockManager]
frequency_time : 00:00:10:00
size : 4
first : 600000
second : 30000
third : 120000
fourth : 250000
fifth : 0
sixth : 0
