# test-fused-2
## Source
```lisp
( print ( + ( * 2 2 ) 3 ) ) 
```
## Token Stream
```json
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"+"}
{"separator":"("}
{"identifier":"*"}
{"identifier":"2"}
{"identifier":"2"}
{"separator":")"}
{"identifier":"3"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "print", [ "+", [ "*", "2", "2" ], "3" ] ]
```
## Interpreter
```bash
7
```