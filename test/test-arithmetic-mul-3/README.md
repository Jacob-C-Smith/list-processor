# prog
## Human
```
3 * 2 * 1
```
## Source
```lisp
( write ( * 3 2 1 ) ) 
```
## Token Stream
```json
{"identifier":3}
{"identifier":"*"}
{"identifier":2}
{"identifier":"*"}
{"identifier":1}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"*"}
{"identifier":3}
{"identifier":2}
{"identifier":1}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "*", 3, 2, 1 ] ]

```
## Interpreter
```bash
6
```