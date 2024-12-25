# prog
## Human
```
1 + 2 + 3
```
## Source
```lisp
( write ( + 1 2 3 ) ) 
```
## Token Stream
```json
{"identifier":"1"}
{"identifier":"+"}
{"identifier":"2"}
{"identifier":"+"}
{"identifier":"3"}
{"separator":"("}
{"identifier":"write"}
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
[ "write", [ "+", "1", "2", "3" ] ]
```
## Interpreter
```bash
6
```