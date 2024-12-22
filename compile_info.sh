# Source
printf "# Source\n"
cat $1

# Token stream
printf "\n# Token Stream\n"
cat $1 | ./build/eddy_lexer 2>/dev/null

# Abstract syntax tree
printf "\n# Abstract syntax tree\n"
cat $1 | ./build/eddy_lexer 2>/dev/null | ./build/eddy_syntax 2> /dev/null

# Interpreter output
printf "\n# Interpreter\n"
cat $1 | ./build/eddy_lexer 2>/dev/null | ./build/eddy_syntax 2>/dev/null | ./build/eddy_interpreter 2>/dev/null
