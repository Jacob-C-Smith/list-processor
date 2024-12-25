# prog
## Human
```
0 & 0
0 & 1
1 & 0
1 & 1
```
## Source
```lisp
( write ( or 0 0 ) ( or 0 1 ) ( or 1 0 ) ( or 1 1 ) )
```
## Token Stream
```json
{"identifier":0}
{"identifier":"&"}
{"identifier":0}
{"identifier":0}
{"identifier":"&"}
{"identifier":1}
{"identifier":1}
{"identifier":"&"}
{"identifier":0}
{"identifier":1}
{"identifier":"&"}
{"identifier":1}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"or"}
{"identifier":0}
{"identifier":0}
{"separator":")"}
{"separator":"("}
{"identifier":"or"}
{"identifier":0}
{"identifier":1}
{"separator":")"}
{"separator":"("}
{"identifier":"or"}
{"identifier":1}
{"identifier":0}
{"separator":")"}
{"separator":"("}
{"identifier":"or"}
{"identifier":1}
{"identifier":1}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "or", 0, 0 ], [ "or", 0, 1 ], [ "or", 1, 0 ], [ "or", 1, 1 ] ]

```
## Interpreter
```bash
false
true
true
true
```