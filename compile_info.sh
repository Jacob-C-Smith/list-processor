# Clear
clear

printf "\033[94m[eddy] Compiling $1\033[0m\n\n"

# Source
printf "\033[94m# Source\033[0m\n"
cat $1

# Token stream
printf "\033[94m\n# Token Stream\033[0m\n"
cat $1 | ./build/eddy_lexer 2>/dev/null

# Abstract syntax tree
printf "\033[94m\n# Abstract syntax tree\033[0m\n"
cat $1 | ./build/eddy_lexer 2>/dev/null | ./build/eddy_syntax 2> /dev/null

# Interpreter output
printf "\033[94m\n# Interpreter\033[0m\n"
cat $1 | ./build/eddy_lexer 2>/dev/null | ./build/eddy_syntax 2>/dev/null | ./build/eddy_interpreter 2>/dev/null
