# prog
## Human
```
2 - 1
```
## Source
```lisp
( write ( - 2 1 ) ) 
```
## Token Stream
```json
{"identifier":2}
{"identifier":"-"}
{"identifier":1}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"-"}
{"identifier":2}
{"identifier":1}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "-", 2, 1 ] ]

```
## Interpreter
```bash
-3
```