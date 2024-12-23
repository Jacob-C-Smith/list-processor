# prog
## Human
```

```
## Source
```lisp
( print ( == false false ) ( == false true ) ( == true false ) ( == true true ) )
```
## Token Stream
```json
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"=="}
{"identifier":"false"}
{"identifier":"false"}
{"separator":")"}
{"separator":"("}
{"identifier":"=="}
{"identifier":"false"}
{"identifier":"true"}
{"separator":")"}
{"separator":"("}
{"identifier":"=="}
{"identifier":"true"}
{"identifier":"false"}
{"separator":")"}
{"separator":"("}
{"identifier":"=="}
{"identifier":"true"}
{"identifier":"true"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "print", [ "==", "false", "false" ], [ "==", "false", "true" ], [ "==", "true", "false" ], [ "==", "true", "true" ] ]
```
## Interpreter
```bash
true
false
false
true
```