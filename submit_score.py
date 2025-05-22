import sys
import requests

def submit_score(name, difficulty, time_sec):
    url = "https://your-api.example.com/submit_score"
    data = {
        "player": name,
        "difficulty": difficulty,
        "time": time_sec
    }
    response = requests.post(url, json=data)
    print(f"Server responded: {response.status_code} {response.text}")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: submit_score.py <name> <difficulty> <time_sec>")
        sys.exit(1)

    submit_score(sys.argv[1], sys.argv[2], float(sys.argv[3]))
