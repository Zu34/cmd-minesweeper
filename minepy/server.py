from flask import Flask, request, jsonify

app = Flask(__name__)

# In-memory storage of scores 
scores = []

@app.route('/api/score', methods=['POST'])
def add_score():
    data = request.get_json()
    if not data:
        return jsonify({"error": "Missing JSON data"}), 400
    
    name = data.get("name")
    difficulty = data.get("difficulty")
    time_sec = data.get("time_sec")
    
    if not (name and difficulty and isinstance(time_sec, (int, float))):
        return jsonify({"error": "Missing or invalid fields"}), 400
    
    # Store the score
    scores.append({
        "name": name,
        "difficulty": difficulty,
        "time_sec": time_sec
    })
    
    return jsonify({"message": "Score added"}), 201

@app.route('/api/scores', methods=['GET'])
def get_scores():
    sorted_scores = sorted(scores, key=lambda x: x["time_sec"])
    return jsonify(sorted_scores)

if __name__ == '__main__':
    app.run(debug=True, port=5000)
