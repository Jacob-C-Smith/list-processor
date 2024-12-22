# prog
## Human
```

```
## Source
```lisp
( print ( + 1 2 3 ) ) 
```
## Token Stream
```json
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"+"}
{"identifier":"1"}
{"identifier":"2"}
{"identifier":"3"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "print", [ "+", "1", "2", "3" ] ]
```
## Interpreter
```bash
6
```