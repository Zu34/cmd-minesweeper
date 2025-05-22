import sys
from datetime import datetime

def log_score(player_name, score):
    with open("scores.txt", "a") as f:
        f.write(f"{datetime.now()}: {player_name} - {score}\n")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: log_score.py <player_name> <score>")
        sys.exit(1)

    log_score(sys.argv[1], sys.argv[2])
