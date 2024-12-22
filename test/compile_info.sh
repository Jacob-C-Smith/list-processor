printf "# $(printf "$1" | awk -F'/' '{print $2}')\n"
# Source
printf "## Source\n"
printf "\`\`\`lisp\n"
cat $1
printf "\`\`\`"

# Token stream
printf "\n## Token Stream\n"
printf "\`\`\`json\n"
cat $1 | ./../build/eddy_lexer 2>/dev/null
printf "\`\`\`"

# Abstract syntax tree
printf "\n## Abstract syntax tree\n"
printf "\`\`\`json\n"
cat $1 | ./../build/eddy_lexer 2>/dev/null | ./../build/eddy_syntax 2> /dev/null
printf "\`\`\`"

# Interpreter output
printf "\n## Interpreter\n"
printf "\`\`\`bash\n"
cat $1 | ./../build/eddy_lexer 2>/dev/null | ./../build/eddy_syntax 2>/dev/null | ./../build/eddy_interpreter 2>/dev/null
printf "\`\`\`"