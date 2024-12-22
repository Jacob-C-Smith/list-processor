# prog
## Human
```

```
## Source
```lisp
( print ( * 3 2 1 ) ) 
```
## Token Stream
```json
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"*"}
{"identifier":"3"}
{"identifier":"2"}
{"identifier":"1"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "print", [ "*", "3", "2", "1" ] ]
```
## Interpreter
```bash
6
```