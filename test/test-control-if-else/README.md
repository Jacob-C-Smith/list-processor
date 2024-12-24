# prog
## Human
```

```
## Source
```lisp
if 5 eq 5 print "eq"( if ( == 5 5 ) ( print "eq" ) )
```
## Token Stream
```json
{"identifier":"if"}
{"identifier":"5"}
{"identifier":"eq"}
{"identifier":"5"}
{"identifier":"print"}
{"identifier":"eq"}
{"identifier":"if"}
{"separator":"("}
{"identifier":"=="}
{"identifier":"5"}
{"identifier":"5"}
{"separator":")"}
{"separator":"("}
{"identifier":"print"}
{"identifier":"eq"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
"if", "5", "eq", "5", "print", "eq", "if", [ "==", "5", "5" ], [ "print", "eq" ] ]
```
## Interpreter
```bash
```