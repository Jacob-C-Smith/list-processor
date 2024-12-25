# prog
## Human
```

```
## Source
```lisp
hello
( set "name" "Jake" )
( write (get "name"))
```
## Token Stream
```json
{"separator":"("}
{"identifier":"set"}
{"identifier":"name"}
{"identifier":"Jake"}
{"separator":")"}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"get"}
{"identifier":"name"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "set", "name", "Jake" ]
[ "write", [ "get", "name" ] ]

```
## Interpreter
```bash
"Jake"
```