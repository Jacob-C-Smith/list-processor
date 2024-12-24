# prog
## Human
```

```
## Source
```lisp
1 + 2 + 3( print ( + 1 2 3 ) ) 
```
## Token Stream
```json
{"identifier":"1"}
{"identifier":"+"}
{"identifier":"2"}
{"identifier":"+"}
{"identifier":"3"}
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
"1", "+", "2", "+", "3", [ "print", [ "+", "1", "2", "3" ] ]
```
## Interpreter
```bash
```