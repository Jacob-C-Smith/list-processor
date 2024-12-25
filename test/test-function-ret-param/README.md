# prog
## Human
```

```
## Source
```lisp
(fun return_param ( (param p any) ) (p))
(write (return_param 5))
```
## Token Stream
```json
{"separator":"("}
{"identifier":"fun"}
{"identifier":"return_param"}
{"separator":"("}
{"separator":"("}
{"identifier":"param"}
{"identifier":"p"}
{"identifier":"any"}
{"separator":")"}
{"separator":")"}
{"separator":"("}
{"identifier":"p"}
{"separator":")"}
{"separator":")"}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"return_param"}
{"identifier":5}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "fun", "return_param", [ [ "param", "p", "any" ] ], [ "p" ] ]
[ "write", [ "return_param", 5 ] ]

```
## Interpreter
```bash
1
```