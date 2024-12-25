# prog
## Human
```

```
## Source
```lisp
( set "x" 0 )
( while ( != ( get "x" ) 5 ) ( write ( set "x" (+ ( get "x" ) 1 ) ) ) )
```
## Token Stream
```json
{"separator":"("}
{"identifier":"set"}
{"identifier":"x"}
{"identifier":0}
{"separator":")"}
{"separator":"("}
{"identifier":"while"}
{"separator":"("}
{"identifier":"!="}
{"separator":"("}
{"identifier":"get"}
{"identifier":"x"}
{"separator":")"}
{"identifier":5}
{"separator":")"}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"set"}
{"identifier":"x"}
{"separator":"("}
{"identifier":"+"}
{"separator":"("}
{"identifier":"get"}
{"identifier":"x"}
{"separator":")"}
{"identifier":1}
{"separator":")"}
{"separator":")"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "set", "x", 0 ]
[ "while", [ "!=", [ "get", "x" ], 5 ], [ "write", [ "set", "x", [ "+", [ "get", "x" ], 1 ] ] ] ]

```
## Interpreter
```bash
1
2
3
4
5
```