printf "# $(printf "$1" | awk -F'/' '{print $3}')\n"

# Source
printf "## Human\n"
printf "\`\`\`\n"
cat $(printf "%s\n" $ | awk -F'/' '{print $3 ""}')
printf "\n\`\`\`\n"

# Source
printf "## Source\n"
printf "\`\`\`lisp\n"
cat $2 | cat - $1
printf "\`\`\`"

# Token stream
printf "\n## Token Stream\n"
printf "\`\`\`json\n"
cat $2 | cat - $1 | ./../build/lexer 2>/dev/null
printf "\`\`\`"

# Abstract syntax tree
printf "\n## Abstract syntax tree\n"
printf "\`\`\`json\n"
cat $2 | cat - $1 | ./../build/lexer 2>/dev/null | ./../build/syntax 2> /dev/null
printf "\`\`\`"

# Interpreter output
printf "\n## Interpreter\n"
printf "\`\`\`bash\n"
cat $2 | cat - $1 | ./../build/lexer 2>/dev/null | ./../build/syntax 2>/dev/null | ./../build/interpreter 2>/dev/null
printf "\`\`\`"