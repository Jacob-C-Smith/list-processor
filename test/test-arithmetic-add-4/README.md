# prog
## Human
```
1 + 2 + 3 + 4
```
## Source
```lisp
( write ( + 1 2 3 4 ) ) 
```
## Token Stream
```json
{"identifier":1}
{"identifier":"+"}
{"identifier":2}
{"identifier":"+"}
{"identifier":3}
{"identifier":"+"}
{"identifier":4}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"+"}
{"identifier":1}
{"identifier":2}
{"identifier":3}
{"identifier":4}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "+", 1, 2, 3, 4 ] ]

```
## Interpreter
```bash
10
```