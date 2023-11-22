# -*- coding: utf-8 -*-
"""
Parte IV - Exemplo 5 (2ª Versão)
"""

from pandas import read_excel
from pulp import *

df1 = read_excel("Data_EX5.xlsx", nrows=2, usecols=(['Wood', 'Hand labour', 'Profits']))

print("==> Dataframe 1\n", df1)

wood = list(df1['Wood'])
print("==> Wood\n", wood)

hand_labour = list(df1['Hand labour'])
print("==> Hand labour\n", hand_labour)

profits = list(df1['Profits'])
print("==> Profits\n", profits)

df2 = read_excel("Data_EX5.xlsx", nrows=2, usecols=(['Resources']))
print("==> Dataframe 2\n", df2)

resources = list(df2['Resources'])
print("==> Resources\n", resources)

model = LpProblem("Carpinteiro", LpMaximize)

x = {j: LpVariable(name=f"x{j}", lowBound=0, cat=LpInteger) for j in range(1,3)}

model += lpSum([profits[j]*x[j+1] for j in range(2)])

model += lpSum([wood[j] * x[j+1] for j in range(2)]) <= resources[0]
model += lpSum([hand_labour[j] * x[j+1] for j in range(2)]) <= resources[1]

model.solve()

print("--------------- Resultados ---------------")
print(f"Estado: {model.status} <=> {LpStatus[model.status]}")
print(f"z* = {model.objective.value()}")
for var in model.variables():
    print(f"{var.name}* = {var.value()}")
for name, constraint in model.constraints.items():
    print(f"{name}: {constraint.value()}")  
