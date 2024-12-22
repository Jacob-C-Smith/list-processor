# prog
## Human
```

```
## Source
```lisp
( print ( + 1 2 3 4 ) ) 
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
{"identifier":"4"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "print", [ "+", "1", "2", "3", "4" ] ]
```
## Interpreter
```bash
10
```