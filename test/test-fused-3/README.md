# test-fused-3
## Source
```lisp
( print ( + ( * 2 2 ) 1 ) ( + ( * 2 2 ) 2 ) ) 
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
{"identifier":"1"}
{"separator":")"}
{"separator":"("}
{"identifier":"+"}
{"separator":"("}
{"identifier":"*"}
{"identifier":"2"}
{"identifier":"2"}
{"separator":")"}
{"identifier":"2"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "print", [ "+", [ "*", "2", "2" ], "1" ], [ "+", [ "*", "2", "2" ], "2" ] ]
```
## Interpreter
```bash
5
6
```