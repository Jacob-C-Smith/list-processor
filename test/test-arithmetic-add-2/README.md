# prog
## Human
```

```
## Source
```lisp
( print ( + 1 2 ) ) 
```
## Token Stream
```json
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"+"}
{"identifier":"1"}
{"identifier":"2"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "print", [ "+", "1", "2" ] ]
```
## Interpreter
```bash
3
```