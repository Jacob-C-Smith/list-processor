# prog
## Human
```

```
## Source
```lisp
( if ( == 5 5 ) ( print "eq" ) )
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
{"identifier":"print"}
{"identifier":"eq"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "if", [ "==", "5", "5" ], [ "print", "eq" ] ]
```
## Interpreter
```bash
eq
```