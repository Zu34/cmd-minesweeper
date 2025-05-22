import sys
from datetime import datetime

def log_score(player_name, difficulty, elapsed_time):
    difficulty_map = {1: "Easy", 2: "Medium", 3: "Hard"}
    difficulty_label = difficulty_map.get(difficulty, "Unknown")
    with open("scores.txt", "a") as f:
        f.write(f"{datetime.now()} | {player_name} | {difficulty_label} | {elapsed_time:.2f} sec\n")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: log_score.py <player_name> <score>")
        sys.exit(1)

    log_score(sys.argv[1], sys.argv[2])
