import pandas as pd

def detect_leak(data):
    threshold = data.mean() + data.std() * 1.5
    leaks = data[data > threshold]
    return leaks

flow_data = pd.Series([2.1, 2.3, 2.2, 2.5, 3.0, 7.5, 2.4])
leak_points = detect_leak(flow_data)

print("Leak detected at indices:", leak_points.index.tolist())