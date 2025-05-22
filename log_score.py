# log_score.py
import requests
from datetime import datetime

def log_score(name, difficulty, time_sec):
    log_line = f"{datetime.now().isoformat()}| {name}| {difficulty}| {time_sec:.2f} sec\n"
    with open("scores.txt", "a") as f:
        f.write(log_line)

    # Optional: send to server
    try:
        response = requests.post("https://your-server.com/api/score", json={
            "name": name,
            "difficulty": difficulty,
            "time_sec": time_sec
        })
        response.raise_for_status()
    except Exception as e:
        print("Failed to send score:", e)

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 4:
        print("Usage: log_score.py <name> <difficulty> <time>")
    else:
        log_score(sys.argv[1], sys.argv[2], float(sys.argv[3]))

