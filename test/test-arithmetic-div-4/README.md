# prog
## Human
```
32 / 2 / 2 / 2
```
## Source
```lisp
( write ( / 32 2 2 2 ) ) 
```
## Token Stream
```json
{"identifier":32}
{"identifier":"/"}
{"identifier":2}
{"identifier":"/"}
{"identifier":2}
{"identifier":"/"}
{"identifier":2}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"/"}
{"identifier":32}
{"identifier":2}
{"identifier":2}
{"identifier":2}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "/", 32, 2, 2, 2 ] ]

```
## Interpreter
```bash
4
```