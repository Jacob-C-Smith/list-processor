# prog
## Human
```
1 + 2
```
## Source
```lisp
( write ( + 1 2 ) ) 
```
## Token Stream
```json
{"identifier":1}
{"identifier":"+"}
{"identifier":2}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"+"}
{"identifier":1}
{"identifier":2}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "+", 1, 2 ] ]

```
## Interpreter
```bash
3
```