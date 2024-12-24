# prog
## Human
```

```
## Source
```lisp
4 * 3 * 2 * 1( print ( * 4 3 2 1 ) ) 
```
## Token Stream
```json
{"identifier":"4"}
{"identifier":"*"}
{"identifier":"3"}
{"identifier":"*"}
{"identifier":"2"}
{"identifier":"*"}
{"identifier":"1"}
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"*"}
{"identifier":"4"}
{"identifier":"3"}
{"identifier":"2"}
{"identifier":"1"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
"4", "*", "3", "*", "2", "*", "1", [ "print", [ "*", "4", "3", "2", "1" ] ]
```
## Interpreter
```bash
```