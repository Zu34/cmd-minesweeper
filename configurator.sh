#!/bin/bash

CONFIG_FILE="minesweeper.cfg"

if [ ! -f "$CONFIG_FILE" ]; then
  echo "Config file not found, creating default..."
  cat > "$CONFIG_FILE" << EOF
board_size=10
bomb_easy=10
bomb_medium=50
bomb_hard=100
EOF
fi

echo "Current settings:"
cat "$CONFIG_FILE"
echo

echo "Enter new values or press enter to keep current."

read -p "Board size (default 10): " board_size
read -p "Bombs Easy (default 10): " bomb_easy
read -p "Bombs Medium (default 50): " bomb_medium
read -p "Bombs Hard (default 100): " bomb_hard

# Helper update config or keep old
update_config() {
  local key=$1
  local new_value=$2
  local default_value=$3

  if [ -n "$new_value" ]; then
    sed -i "s/^$key=.*/$key=$new_value/" "$CONFIG_FILE"
  else
    # If key not found, add it
    if ! grep -q "^$key=" "$CONFIG_FILE"; then
      echo "$key=$default_value" >> "$CONFIG_FILE"
    fi
  fi
}

update_config board_size "$board_size" 10
update_config bomb_easy "$bomb_easy" 10
update_config bomb_medium "$bomb_medium" 50
update_config bomb_hard "$bomb_hard" 100

echo
echo "Updated settings:"
cat "$CONFIG_FILE"
