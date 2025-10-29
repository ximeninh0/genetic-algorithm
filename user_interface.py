import streamlit as st
import matplotlib.pyplot as plt
import json

# ********************************
# Após rodar o programa em C++ com: 
# g++ -Iinclude src/main.cpp src/Entities/*.cpp src/Tools/*.cpp src/Genetics/*.cpp -o main
# ./main
# ********************************
# 1: Criar e executar venv
# 2: pip install -r requirements.txt
# 3: python user_interface.py
# 4: Em outro terminal executar: 
#  Streamlit run user_interface.py
# ********************************


# Carrega os dados
with open("data.json") as f:
    data = json.load(f)

points = data["points"]
best_route = data["route"]

# Caso a rota contenha índices maiores que o número de pontos,
# ainda é bom garantir que eles estejam dentro do intervalo válido:
num_points = len(points)
best_route = [i % num_points for i in best_route]

xs, ys = zip(*points)
rx, ry = zip(*[points[i] for i in best_route])

fig, ax = plt.subplots()
ax.scatter(xs, ys, color="blue", label="Pontos")
ax.plot(rx, ry, color="orange", label="Melhor rota")

for i, (x, y) in enumerate(points):
    ax.text(x + 0.1, y + 0.1, str(i), fontsize=9)

ax.legend()
st.pyplot(fig)
