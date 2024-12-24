# prog
## Human
```

```
## Source
```lisp
1 + 2 + 3 + 4( print ( + (1 2) (3 4) ) ) 
```
## Token Stream
```json
{"identifier":"1"}
{"identifier":"+"}
{"identifier":"2"}
{"identifier":"+"}
{"identifier":"3"}
{"identifier":"+"}
{"identifier":"4"}
{"separator":"("}
{"identifier":"print"}
{"separator":"("}
{"identifier":"+"}
{"separator":"("}
{"identifier":"1"}
{"identifier":"2"}
{"separator":")"}
{"separator":"("}
{"identifier":"3"}
{"identifier":"4"}
{"separator":")"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
"1", "+", "2", "+", "3", "+", "4", [ "print", [ "+", [ "1", "2" ], [ "3", "4" ] ] ]
```
## Interpreter
```bash
```