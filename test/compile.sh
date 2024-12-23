
# Source
#printf "%s\n%s\n%s\n" $1 $2 $3 

cat $2 | cat $1 - |

# Token streams
./../build/lexer 2>/dev/null |

# Abstract syntax tree
./../build/syntax 2>/dev/null |

# Interpreter output
./../build/interpreter > $3 2> /dev/null

