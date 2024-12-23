# prog
## Human
```

```
## Source
```lisp
( print ( != "" "" ) ( != "a" "" ) ( != "" "a" ) ( != "a" "a" ) ( != "a" "b" ) ( != "b" "a" ) ( != "b" "b" ) )
```
## Token Stream
```json
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"!="}
{"identifier":""}
{"identifier":""}
{"separator":")"}
{"separator":"("}
{"identifier":"!="}
{"identifier":"a"}
{"identifier":""}
{"separator":")"}
{"separator":"("}
{"identifier":"!="}
{"identifier":""}
{"identifier":"a"}
{"separator":")"}
{"separator":"("}
{"identifier":"!="}
{"identifier":"a"}
{"identifier":"a"}
{"separator":")"}
{"separator":"("}
{"identifier":"!="}
{"identifier":"a"}
{"identifier":"b"}
{"separator":")"}
{"separator":"("}
{"identifier":"!="}
{"identifier":"b"}
{"identifier":"a"}
{"separator":")"}
{"separator":"("}
{"identifier":"!="}
{"identifier":"b"}
{"identifier":"b"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "print", [ "!=", "", "" ], [ "!=", "a", "" ], [ "!=", "", "a" ], [ "!=", "a", "a" ], [ "!=", "a", "b" ], [ "!=", "b", "a" ], [ "!=", "b", "b" ] ]
```
## Interpreter
```bash
false
true
true
false
true
true
false
```