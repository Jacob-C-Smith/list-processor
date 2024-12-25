# prog
## Human
```

```
## Source
```lisp
( if ( == "5" "5" ) ( write "eq" ) )
```
## Token Stream
```json
{"separator":"("}
{"identifier":"if"}
{"separator":"("}
{"identifier":"=="}
{"identifier":"5"}
{"identifier":"5"}
{"separator":")"}
{"separator":"("}
{"identifier":"write"}
{"identifier":"eq"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "if", [ "==", "5", "5" ], [ "write", "eq" ] ]
```
## Interpreter
```bash
"eq"
```