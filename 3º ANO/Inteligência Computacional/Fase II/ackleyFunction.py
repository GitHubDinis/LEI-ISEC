# -*- coding: utf-8 -*-
"""
Created on Mon Nov 20 01:14:52 2023

@author: Utilizador
"""
import numpy as np
from SwarmPackagePy import aba

def ackley_function(x):
    n = len(x)
    sum1 = np.sum(x**2)
    sum2 = np.sum(np.cos(2 * np.pi * x))
    return -20 * np.exp(-0.2 * np.sqrt(sum1 / n)) - np.exp(sum2 / n) + 20 + np.e

# Parâmetros do PSO
n_agents = 30
function_dim = 3
iteration_count = 1000
lower_bound = -5
upper_bound = 5

# Criação da instância do PSO
pso_optimizer_2d = aba(n_agents, ackley_function, lower_bound, upper_bound, function_dim, iteration_count)

# Obtém o melhor valor e a melhor posição encontrados
best_value_2d = pso_optimizer_2d.get_Gbest()
best_position_2d = pso_optimizer_2d.get_Gbest()
print(f"Best Position (2D): {best_position_2d}")
print(f"Best Value (3D): {best_value_2d}")