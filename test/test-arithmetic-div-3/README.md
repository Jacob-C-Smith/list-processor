# prog
## Human
```
16 / 4 / 2
```
## Source
```lisp
( write ( / 16 4 2 ) ) 
```
## Token Stream
```json
{"identifier":"16"}
{"identifier":"/"}
{"identifier":"4"}
{"identifier":"/"}
{"identifier":"2"}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"/"}
{"identifier":"16"}
{"identifier":"4"}
{"identifier":"2"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "/", "16", "4", "2" ] ]
```
## Interpreter
```bash
2
```