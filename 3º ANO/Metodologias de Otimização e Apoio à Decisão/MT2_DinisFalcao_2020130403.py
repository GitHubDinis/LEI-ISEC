# -*- coding: utf-8 -*-
"""
Mini-Teste 2 - 2023/2024
Dinis Meireles de Sousa Falcão | 2020130403
"""

from pandas import read_excel
from pulp import *

df1 = read_excel("Data_MT2.xlsx", nrows=2, usecols=(['Carros', 'Tipo A', 'Tipo B', 'Capacidade', 'Disponibilidade', 'Profits']))
print("==> Dataframe 1\n", df1)

carros = list(df1['Carros'])
print("==> Carros\n", carros)

tipoA = dict(zip(carros, df1['Tipo A']))
print("==> Tipo A\n", tipoA)

tipoB = dict(zip(carros, df1['Tipo B']))
print("==> Tipo B\n", tipoB)

capacidade = dict(zip(carros, df1['Capacidade']))
print("==> Capacidade\n", capacidade)

disponibilidade = dict(zip(carros, df1['Disponibilidade']))
print("==> Disponibilidade\n", disponibilidade)

profits = dict(zip(carros, df1['Profits']))
print("==> Profits\n", profits)

df2 = read_excel("Data_MT2.xlsx", nrows=4, usecols=(['Vendas']))
print("==> Dataframe 2\n", df2)

vendas = list(df2["Vendas"])
print("==> Vendas\n", vendas)

model = LpProblem("Brinquedos", LpMaximize)

x = LpVariable.dicts("x", carros, lowBound=0, cat=LpInteger)

model += lpSum([profits[i]*x[i] for i in carros])

model += lpSum([tipoA[i] * x[i] for i in carros]) >= vendas[0]
model += lpSum([tipoB[i] * x[i] for i in carros]) >= vendas[1]
model += lpSum([capacidade[i] * x[i] for i in carros]) <= vendas[2]
model += lpSum([disponibilidade[i] * x[i] for i in carros]) <= vendas[3]

model.solve()

print("--------------- Resultados ---------------")
print(f"Estado: {model.status} <=> {LpStatus[model.status]}")
print(f"z* = {model.objective.value()}")
for var in model.variables():
    print(f"{var.name}* = {var.value()}")
for name, constraint in model.constraints.items():
    print(f"{name}: {constraint.value()}")  