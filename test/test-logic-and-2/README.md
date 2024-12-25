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
( write ( and 0 0 ) ( and 0 1 ) ( and 1 0 ) ( and 1 1 ) )
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
{"identifier":"and"}
{"identifier":0}
{"identifier":0}
{"separator":")"}
{"separator":"("}
{"identifier":"and"}
{"identifier":0}
{"identifier":1}
{"separator":")"}
{"separator":"("}
{"identifier":"and"}
{"identifier":1}
{"identifier":0}
{"separator":")"}
{"separator":"("}
{"identifier":"and"}
{"identifier":1}
{"identifier":1}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "and", 0, 0 ], [ "and", 0, 1 ], [ "and", 1, 0 ], [ "and", 1, 1 ] ]

```
## Interpreter
```bash
false
false
false
true
```