# rules.py

def bomb_count(level):
    if level == 1:
        return 10
    elif level == 2:
        return 50
    elif level == 3:
        return 100
    else:
        return 0
