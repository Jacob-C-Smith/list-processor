# prog
## Human
```

```
## Source
```lisp
( fun return_1 ( ) 1 )
( write ( return_1 ) )```
## Token Stream
```json
{"separator":"("}
{"identifier":"fun"}
{"identifier":"return_1"}
{"separator":"("}
{"separator":")"}
{"identifier":1}
{"separator":")"}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"return_1"}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "fun", "return_1", [  ]1 ]
[ "write", [ "return_1" ] ]

```
## Interpreter
```bash
```