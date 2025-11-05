import json
import pandas as pd
import matplotlib.pyplot as plt
from PIL import Image
import io

with open("data.json", "r") as f:
    data = json.load(f)

city_pos = {}
for code, xy in data["cities"]:
    city_pos[code] = xy  # salva tipo: 'A': [12, 72]
df = pd.read_csv("history.csv")

solution_index = df.last_valid_index()
gen = df['generation'][solution_index]
best = df['best'][solution_index]
average = df['average'][solution_index]
worst = df['worst'][solution_index]
route = df['route'][solution_index]

route = list(map(int, route.split('-')))
xs = [city_pos[c][0] for c in route]
ys = [city_pos[c][1] for c in route]

fig, ax = plt.subplots()
ax.scatter(xs, ys)
ax.plot(xs, ys)  # linha da rota

# nome de cada cidade em cima do ponto
for c in route:
    ax.text(city_pos[c][0], city_pos[c][1], c)

ax.set_title(f"Generation {gen} Best: {best}")

plt.title(f"Geração: {gen} Fit: {best}")
plt.xlabel("Geração")
plt.ylabel("Fitness")
plt.legend()
plt.grid(True)
plt.show()
# frames.append(Image.open(buf))