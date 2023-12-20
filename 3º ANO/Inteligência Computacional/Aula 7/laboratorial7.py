"""
Aula Laboratorial nยบ7

ACO - ANT COLONY OPTIMIZATION
"""

import os
import math 
import acopy

os.chdir("C:/Users/Utilizador/Desktop/ISEC - LEI/4º ANO/IC/AULAS/Aula 7/ant-colony-tsp-master")

# distรขncia euclidiana entre duas cidades

def distance(city1: dict, city2: dict):
    return math.sqrt((city1['x'] - city2['x']) ** 2 + (city1['y'] - city2['y']) ** 2)

# considerar instรขncia de menor dimensรฃo

cities = []
points = []
with open('C:/Users/Utilizador/Desktop/ISEC - LEI/4º ANO/IC/AULAS/Aula 7/ant-colony-tsp-master/data/chn31.txt') as f:
    for line in f.readlines():
        city = line.split(' ')
        cities.append(dict(index=int(city[0]), x=int(city[1]), y=int(city[2])))
        points.append((int(city[1]), int(city[2])))
cost_matrix = []
rank = len(cities)
for i in range(rank):
    row = []
    for j in range(rank):
        row.append(distance(cities[i], cities[j]))
    cost_matrix.append(row)
 
    aco = ACO(10, 100, 1.0, 10.0, 0.5, 10, 2)

""" 
    :param ant_count:
    :param generations:
    :param alpha: relative importance of pheromone
    :param beta: relative importance of heuristic information
    :param rho: pheromone residual coefficient
    :param q: pheromone intensity
    :param strategy: pheromone update strategy. 0 - ant-cycle, 1 - ant-quality, 2 - ant-density
"""