#!/bin/bash

SCOREFILE="scores.txt"

function show_scores() {
    local diff="$1"
    echo "---- High Scores for $diff ----"
    if [ -f "$SCOREFILE" ]; then
        grep " $diff " "$SCOREFILE" | sort -k3n | head -10
    else
        echo "No scores yet."
    fi
}

function add_score() {
    local name="$1"
    local diff="$2"
    local time="$3"
    echo "$name $diff $time" >> "$SCOREFILE"
    echo "Score added!"
}

case "$1" in
    show)
        show_scores "$2"
        ;;
    add)
        if [ $# -ne 4 ]; then
            echo "Usage: $0 add <name> <difficulty> <time_in_seconds>"
            exit 1
        fi
        add_score "$2" "$3" "$4"
        ;;
    *)
        echo "Usage: $0 show <difficulty> | add <name> <difficulty> <time_in_seconds>"
        ;;
esac
