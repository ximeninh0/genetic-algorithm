#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <ctime>
#include <experimental/random>
#include <random>
#include <algorithm>
#include <fstream>
#include <chrono>
#include "Entities/Gene.h"
#include "Entities/Individual.h"
#include "Entities/Point.h"
#include "Entities/Population.h"
#include "Tools/Tools.h"
#include "Genetics/Reproduction.h"
#include "Genetics/Mutation.h"
#include "Genetics/GeneticAlgorithm.h"
#include <thread>

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(int elite_size, int tx_mut_indv, int tx_mut_gene)
{
    this->elite_size = elite_size;
    this->mutation_indv_tx = tx_mut_indv;
    this->mutation_gene_tx = tx_mut_gene;
}

Individual GeneticAlgorithm::RunGeneticAlgorithim(Population &population, int epochs, int tournament_size)
{
    // Inicialização dos objetos de mutação e reprodução
    Reproduction reproducion_tools(this->elite_size, tournament_size);
    Mutation mutation_tools(this->mutation_indv_tx, this->mutation_gene_tx);
    Tools tools; // Ferramenta para o thread principal (ex: print_progress)

    // --- Configuração do Log ---
    std::ofstream history("history.csv");
    if (!history.is_open())
    {
        std::cerr << "Erro ao abrir arquivo de histórico.\n";
    }
    history << "generation,best,average,worst,route\n";

    // --- Configuração das Threads ---
    const int num_thread = thread::hardware_concurrency();
    vector<thread> threads;
    vector<Tools> thread_tools(num_thread); // <-- CORREÇÃO: Inicializa um 'Tools' para cada thread (para RNG)

    int num_children_to_create = population.get_size() - population.get_elitism_size();
    vector<Individual> offspring_population;
    offspring_population.reserve(num_children_to_create); // Bom!

    // <-- CORREÇÃO: Armazenamento para os resultados de CADA thread
    vector<vector<Individual>> all_local_offsprings(num_thread);

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < epochs - 1; i++)
    {
        tools.print_progress(i, epochs);
        population.sort_individuals(); // Ordena os pais para o 'elitism' e 'get_best_fit'

        // --- Limpa os dados da época anterior ---
        threads.clear();
        offspring_population.clear();
        for (auto &local_vec : all_local_offsprings)
        {
            local_vec.clear(); // Limpa os filhos da geração passada
        }

        // --- Distribuição de Trabalho ---
        int base_work_per_thread = num_children_to_create / num_thread;
        int remainder_work = num_children_to_create % num_thread;

        // --- 1. FORK: Inicia as Threads ---
        for (int t = 0; t < num_thread; t++)
        {
            // Passa 't' por valor! Captura o resto por referência
            threads.emplace_back([&, t]
                                 {
                int work_for_thread = base_work_per_thread;
                if (t == 0) // <-- CORREÇÃO: Thread 0 pega o "resto" do trabalho
                {
                    work_for_thread += remainder_work;
                }

                // Garante que o vetor local tenha espaço
                all_local_offsprings[t].reserve(work_for_thread);

                for (int j = 0; j < work_for_thread; j++)
                {
                    // Assumindo que suas funções "thread_safe" pegam um 'Tools' para o RNG
                    Individual& parent1 = reproducion_tools.thread_safe_tournament_selection(population, reproducion_tools.tournament_size, thread_tools[t]);
                    Individual& parent2 = reproducion_tools.thread_safe_tournament_selection(population, reproducion_tools.tournament_size, thread_tools[t]);

                    Individual child = reproducion_tools.thread_safe_gen_child_by_crossover(parent1, parent2, thread_tools[t]);

                    mutation_tools.thread_safe_mutate_indv_by_inverse(child, thread_tools[t]);

                    child.get_fitness(); // Preenche o cache de fitness em paralelo

                    // <-- CORREÇÃO: Salva no vetor externo dedicado a esta thread
                    all_local_offsprings[t].push_back(child);
                } });
        }

        // --- 2. JOIN: Espera todas as threads terminarem ---
        for (auto &t : threads)
        {
            t.join();
        }

        // --- 3. COMBINE: Lógica da Thread Principal (O que você pediu) ---

        // A. Junta os 'local_offspring' de todas as threads
        for (int t = 0; t < num_thread; t++)
        {
            // Usa 'std::move' para transferir eficientemente os filhos
            // sem copiá-los
            offspring_population.insert(
                offspring_population.end(),
                std::make_move_iterator(all_local_offsprings[t].begin()),
                std::make_move_iterator(all_local_offsprings[t].end()));
        }

        // B. Adiciona a elite (os melhores da geração anterior)
        for (int e = 0; e < population.get_elitism_size(); e++)
        {
            offspring_population.push_back(population.get_individuals_ref()[e]);
        }

        // C. Define a nova população e seleciona os melhores
        population.set_individuals(offspring_population);
        population.sort_individuals(); // Ordena todos (filhos + elite)
        population.get_individuals_ref().resize(population.get_size()); // Trunca, mantendo apenas os 'size_p' melhores

        // --- 4. LOG: Registra os dados da *nova* geração ---
        // <-- CORREÇÃO: Movido para DEPOIS da atualização da população
        int best = population.get_best_fit();
        float avg = population.get_average_fit();
        int worst = population.get_worst_fit();

        history << population.get_generation() << "," << best << "," << avg << "," << worst << ","
                << population.get_individuals_ref()[0].get_first_gene().get_name() << "-";

        for (Gene &g : population.get_individuals_ref()[0].get_chromossome_ref())
            history << g.get_name() << "-";

        history << population.get_individuals_ref()[0].get_first_gene().get_name();
        history << "\n";
        history.flush();

        population.set_generation(population.get_generation() + 1);
    }

    auto duration = std::chrono::high_resolution_clock::now() - start;
    history.close();

    // --- Finalização ---
    population.sort_individuals(); // Ordena a última geração
    cout << "\n----------Ultima populacao----------" << endl;
    population.print_population();

    long long ms = chrono::duration_cast<chrono::milliseconds>(duration).count();
    cout << "Tempo decorrido: " << ms << " milissegundos" << endl;

    return population.get_individuals()[0];
}