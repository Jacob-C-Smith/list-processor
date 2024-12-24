# prog
## Human
```

```
## Source
```lisp
( 2 * 2 ) + ( 2 * 2 ) + ( 2 * 2 ) + ( 2 * 2 )( print ( + ( * 2 2 ) ( * 2 2 ) ( * 2 2 ) ( * 2 2 ) ) ) 
```
## Token Stream
```json
{"separator":"("}
{"identifier":"2"}
{"identifier":"*"}
{"identifier":"2"}
{"separator":")"}
{"identifier":"+"}
{"separator":"("}
{"identifier":"2"}
{"identifier":"*"}
{"identifier":"2"}
{"separator":")"}
{"identifier":"+"}
{"separator":"("}
{"identifier":"2"}
{"identifier":"*"}
{"identifier":"2"}
{"separator":")"}
{"identifier":"+"}
{"separator":"("}
{"identifier":"2"}
{"identifier":"*"}
{"identifier":"2"}
{"separator":")"}
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"+"}
{"separator":"("}
{"identifier":"*"}
{"identifier":"2"}
{"identifier":"2"}
{"separator":")"}
{"separator":"("}
{"identifier":"*"}
{"identifier":"2"}
{"identifier":"2"}
{"separator":")"}
{"separator":"("}
{"identifier":"*"}
{"identifier":"2"}
{"identifier":"2"}
{"separator":")"}
{"separator":"("}
{"identifier":"*"}
{"identifier":"2"}
{"identifier":"2"}
{"separator":")"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "2", "*", "2" ], "+", [ "2", "*", "2" ], "+", [ "2", "*", "2" ], "+", [ "2", "*", "2" ], [ "print", [ "+", [ "*", "2", "2" ], [ "*", "2", "2" ], [ "*", "2", "2" ], [ "*", "2", "2" ] ] ]
```
## Interpreter
```bash
[eddy] No binding for "2"
```