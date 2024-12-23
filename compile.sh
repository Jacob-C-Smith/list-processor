
# Source
cat $1 |

# Token streams
./build/eddy_lexer 2>/dev/null |

# Abstract syntax tree
./build/eddy_syntax 2>/dev/null |

# Interpreter output
./build/eddy_interpreter 2>/dev/null

