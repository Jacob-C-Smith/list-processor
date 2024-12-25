# prog
## Human
```

```
## Source
```lisp
(fun return_2 () 2)
(write (return_2))```
## Token Stream
```json
{"separator":"("}
{"identifier":"fun"}
{"identifier":"return_2"}
{"separator":"("}
{"separator":")"}
{"identifier":2}
{"separator":")"}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"return_2"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "fun", "return_2", [  ]2 ]
[ "write", [ "return_2" ] ]

```
## Interpreter
```bash
```