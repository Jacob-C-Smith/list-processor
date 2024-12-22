# test-fused-4
## Source
```lisp
( print ( + ( * 2 2 ) 1 ) ( + ( * 2 2 ) 2 ) ( + ( * 2 2 ) 3 ) ) 
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
[ "print", [ "+", [ "*", "2", "2" ], "1" ], [ "+", [ "*", "2", "2" ], "2" ], [ "+", [ "*", "2", "2" ], "3" ] ]
```
## Interpreter
```bash
5
6
7
```