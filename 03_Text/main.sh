#!/bin/sh

alias echo="/bin/echo -e"

TIMEOUT=1
[ $# -ge 1 ] && TIMEOUT=$1
[ $# -ge 1 ] && [ "$1" = "-h" ] || [ "$1" = "--help" ] && echo "Usage: main.sh [<timeout in seconds>]" && exit 0

text=`cat`

mapText() {
  while IFS= read raw_line; do
    IFS=, read -r line_i line <<< "$raw_line"
    echo -n "$line" | sed 's/\(.\)/'$line_i',\1\n/g' | nl -ba -s, -w1
  done <<< "`echo -n "$1" | nl -ba -s, -w1`"
}

clear;
while IFS= read line; do
  IFS=, read -r col row char <<< "$line"
  #echo "'$col' '$row' '$char'" && continue
  tput cup $row $col 
  echo -n $char
  sleep ${TIMEOUT}s
done <<< "`mapText "$text" | shuf`"

tput cup $((`echo "$text" | wc -l` + 1)) 0
