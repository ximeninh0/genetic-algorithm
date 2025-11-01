import pandas as pd
import matplotlib.pyplot as plt

history = pd.read_csv("history.csv")

plt.figure(figsize=(10, 6))
plt.plot(history["generation"], history["best"], label="Melhor Fitness", linewidth=2)
plt.plot(history["generation"], history["average"], label="Fitness Médio", linestyle="--")
plt.plot(history["generation"], history["worst"], label="Pior Fitness", linestyle=":")

plt.title("Evolução do Fitness ao Longo das Gerações")
plt.xlabel("Geração")
plt.ylabel("Fitness")
plt.legend()
plt.grid(True)
plt.show()