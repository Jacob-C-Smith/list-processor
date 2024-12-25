# prog
## Human
```
( 2 * 2 ) + 1
( 2 * 2 ) + 2
( 2 * 2 ) + 3
```
## Source
```lisp
( write ( + ( * 2 2 ) 1 ) ( + ( * 2 2 ) 2 ) ( + ( * 2 2 ) 3 ) ) 
```
## Token Stream
```json
{"separator":"("}
{"identifier":2}
{"identifier":"*"}
{"identifier":2}
{"separator":")"}
{"identifier":"+"}
{"identifier":1}
{"separator":"("}
{"identifier":2}
{"identifier":"*"}
{"identifier":2}
{"separator":")"}
{"identifier":"+"}
{"identifier":2}
{"separator":"("}
{"identifier":2}
{"identifier":"*"}
{"identifier":2}
{"separator":")"}
{"identifier":"+"}
{"identifier":3}
{"separator":"("}
{"identifier":"write"}
{"separator":"("}
{"identifier":"+"}
{"separator":"("}
{"identifier":"*"}
{"identifier":2}
{"identifier":2}
{"separator":")"}
{"identifier":1}
{"separator":")"}
{"separator":"("}
{"identifier":"+"}
{"separator":"("}
{"identifier":"*"}
{"identifier":2}
{"identifier":2}
{"separator":")"}
{"identifier":2}
{"separator":")"}
{"separator":"("}
{"identifier":"+"}
{"separator":"("}
{"identifier":"*"}
{"identifier":2}
{"identifier":2}
{"separator":")"}
{"identifier":3}
{"separator":")"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", [ "+", [ "*", 2, 2 ], 1 ], [ "+", [ "*", 2, 2 ], 2 ], [ "+", [ "*", 2, 2 ], 3 ] ]

```
## Interpreter
```bash
5
6
7
```