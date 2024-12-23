{
    printf "%s", $2
    for (I=3; I<=NF; I++)
        printf " > %s", $I
    printf "\n"
}