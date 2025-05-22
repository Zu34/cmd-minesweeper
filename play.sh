#!/bin/sh

# Check if minesweeper executable exists, compile if not
if [ ! -f minesweeper ]; then
    echo "Compiling the Minesweeper game..."
    gcc main.c game.c map.c utils.c -o minesweeper
    if [ $? -ne 0 ]; then
        echo "Compilation failed. Exiting."
        exit 1
    fi
fi

echo "Welcome to Minesweeper!"
echo "Select difficulty:"
echo "1) Easy"
echo "2) Medium"
echo "3) Hard"
echo "4) Quit"

while true; do
    printf "Enter your choice (1-4): "
    read -r choice
    case $choice in
        1) difficulty="easy"; break ;;
        2) difficulty="medium"; break ;;
        3) difficulty="hard"; break ;;
        4) echo "Goodbye!"; exit 0 ;;
        *) echo "Invalid input, please enter 1, 2, 3, or 4." ;;
    esac
done

echo "Starting Minesweeper with difficulty: $difficulty"
./minesweeper "$difficulty"
