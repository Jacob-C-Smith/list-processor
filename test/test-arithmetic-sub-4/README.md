# prog
## Human
```
15 - 4 - 3 - 2 - 1
```
## Source
```lisp
( write ( - 15 4 3 2 1 ) ) 
```
## Token Stream
```json
{"identifier":15}
{"identifier":"-"}
{"identifier":4}
{"identifier":"-"}
{"identifier":3}
{"identifier":"-"}
{"identifier":2}
{"identifier":"-"}
{"identifier":1}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"-"}
{"identifier":15}
{"identifier":4}
{"identifier":3}
{"identifier":2}
{"identifier":1}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "-", 15, 4, 3, 2, 1 ] ]

```
## Interpreter
```bash
5
```