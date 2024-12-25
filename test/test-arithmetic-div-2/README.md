# prog
## Human
```
8 / 2
```
## Source
```lisp
( write ( / 8 4 ) ) 
```
## Token Stream
```json
{"identifier":"8"}
{"identifier":"/"}
{"identifier":"2"}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"/"}
{"identifier":"8"}
{"identifier":"4"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "/", "8", "4" ] ]
```
## Interpreter
```bash
2
```