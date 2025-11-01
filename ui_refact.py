import json
import time
import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

class GeneticUI:
    def __init__(self, master):
        self.master = master
        self.master.title("Evolução do Algoritmo Genético")

        # Configuração do gráfico
        self.fig = Figure(figsize=(6, 4), dpi=100)
        self.ax = self.fig.add_subplot(111)
        self.ax.set_title("Fitness Médio por Geração")
        self.ax.set_xlabel("Geração")
        self.ax.set_ylabel("Fitness")

        self.canvas = FigureCanvasTkAgg(self.fig, master=self.master)
        self.canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

        # Dados da simulação
        self.generations = []
        self.avg_fitness = []

        self.update_graph()

    def update_graph(self):
        try:
            with open("generation_data.json", "r") as f:
                data = json.load(f)

            gen = data["generation"]
            avg = data["avg_fitness"]

            # Atualiza apenas se for nova geração
            if len(self.generations) == 0 or gen != self.generations[-1]:
                self.generations.append(gen)
                self.avg_fitness.append(avg)

                self.ax.clear()
                self.ax.plot(self.generations, self.avg_fitness, color="blue")
                self.ax.set_title("Fitness Médio por Geração")
                self.ax.set_xlabel("Geração")
                self.ax.set_ylabel("Fitness")
                self.canvas.draw()
        except FileNotFoundError:
            pass
        except json.JSONDecodeError:
            pass

        # Atualiza a cada 1 segundo
        self.master.after(1000, self.update_graph)

if __name__ == "__main__":
    root = tk.Tk()
    app = GeneticUI(root)
    root.mainloop()
