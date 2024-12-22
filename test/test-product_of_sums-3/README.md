# prog
## Human
```

```
## Source
```lisp
( print ( * ( + 2 2 ) ( + 2 2 ) ( + 2 2 ) ) ) 
```
## Token Stream
```json
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"*"}
{"separator":"("}
{"identifier":"+"}
{"identifier":"2"}
{"identifier":"2"}
{"separator":")"}
{"separator":"("}
{"identifier":"+"}
{"identifier":"2"}
{"identifier":"2"}
{"separator":")"}
{"separator":"("}
{"identifier":"+"}
{"identifier":"2"}
{"identifier":"2"}
{"separator":")"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "print", [ "*", [ "+", "2", "2" ], [ "+", "2", "2" ], [ "+", "2", "2" ] ] ]
```
## Interpreter
```bash
64
```