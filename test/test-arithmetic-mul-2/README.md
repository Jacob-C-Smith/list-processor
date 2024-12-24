# prog
## Human
```

```
## Source
```lisp
2 * 1( print ( * 2 1 ) ) 
```
## Token Stream
```json
{"identifier":"2"}
{"identifier":"*"}
{"identifier":"1"}
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"*"}
{"identifier":"2"}
{"identifier":"1"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
"2", "*", "1", [ "print", [ "*", "2", "1" ] ]
```
## Interpreter
```bash
```