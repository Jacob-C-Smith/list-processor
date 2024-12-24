# prog
## Human
```

```
## Source
```lisp
32 / 2 / 2 / 2( print ( / 32 2 2 2 ) ) 
```
## Token Stream
```json
{"identifier":"32"}
{"identifier":"/"}
{"identifier":"2"}
{"identifier":"/"}
{"identifier":"2"}
{"identifier":"/"}
{"identifier":"2"}
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"/"}
{"identifier":"32"}
{"identifier":"2"}
{"identifier":"2"}
{"identifier":"2"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
"32", "/", "2", "/", "2", "/", "2", [ "print", [ "/", "32", "2", "2", "2" ] ]
```
## Interpreter
```bash
```