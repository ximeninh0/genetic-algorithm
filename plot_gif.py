import json
import pandas as pd
import matplotlib.pyplot as plt
from PIL import Image
import io

# ===== 1) LOAD JSON =====
with open("data.json", "r") as f:
    data = json.load(f)

city_pos = {}
for code, xy in data["cities"]:
    city_pos[ code ] = xy  # salva tipo: 'A': [12, 72]

# ===== 2) LOAD CSV =====
df = pd.read_csv("history.csv")

frames = []

# ===== 3) GENERATE FRAMES =====
for i, row in df.iterrows():
    if(i > 50 and i % 5 != 0):
        continue

    route = row['route']  # "AOPLT..." -> ['A','O','P','L','T',...]
    route = list(map(int, route.split('-')))
    # print(route)

    xs = [city_pos[c][0] for c in route]
    ys = [city_pos[c][1] for c in route]

    fig, ax = plt.subplots()
    ax.scatter(xs, ys)
    ax.plot(xs, ys)  # linha da rota
    
    # nome de cada cidade em cima do ponto
    for c in route:
        ax.text(city_pos[c][0], city_pos[c][1], c)

    ax.set_title(f"Generation {row['generation']} Best: {row['best']}")
    
    buf = io.BytesIO()
    plt.savefig(buf, format='png')
    plt.close(fig)
    buf.seek(0)
    frames.append(Image.open(buf))

# ===== 4) MAKE GIF =====
frames[0].save("anim_circ.gif", save_all=True, append_images=frames[1:], duration=200, loop=0)
