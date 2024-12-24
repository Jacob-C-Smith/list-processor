# prog
## Human
```

```
## Source
```lisp
8 / 2( print ( / 8 4 ) ) 
```
## Token Stream
```json
{"identifier":"8"}
{"identifier":"/"}
{"identifier":"2"}
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"/"}
{"identifier":"8"}
{"identifier":"4"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
"8", "/", "2", [ "print", [ "/", "8", "4" ] ]
```
## Interpreter
```bash
```