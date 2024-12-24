# prog
## Human
```

```
## Source
```lisp
1 + 2( print ( + 1 2 ) ) 
```
## Token Stream
```json
{"identifier":"1"}
{"identifier":"+"}
{"identifier":"2"}
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
"1", "+", "2", [ "print", [ "+", "1", "2" ] ]
```
## Interpreter
```bash
```