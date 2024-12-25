# prog
## Human
```
if 5 eq 5 print "eq"
```
## Source
```lisp
( if ( == 5 5 ) ( write 1 ) )
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
{"identifier":"write"}
{"identifier":"1"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "if", [ "==", "5", "5" ], [ "write", "1" ] ]
```
## Interpreter
```bash
"1"
```