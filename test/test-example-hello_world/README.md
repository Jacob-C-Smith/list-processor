# prog
## Human
```
Print "Hello, World!"
```
## Source
```lisp
( write "Hello, World!" )
```
## Token Stream
```json
{"identifier":"Print"}
{"identifier":"Hello, World!"}
{"separator":"("}
{"identifier":"write"}
{"identifier":"Hello, World!"}
{"separator":")"}
```
## Abstract syntax tree
```json
[ "write", "Hello, World!" ]

```
## Interpreter
```bash
"Hello, World!"
```