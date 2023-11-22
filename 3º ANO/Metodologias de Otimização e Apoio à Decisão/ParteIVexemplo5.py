# -*- coding: utf-8 -*-
"""
Parte IV - Exemplo 5
"""

from pandas import read_excel
from pulp import *

df1 = read_excel("Data_EX5.xlsx", nrows=2, usecols=(['Bench models', 'Wood', 'Hand labour', 'Profits']))

print("==> Dataframe 1\n", df1)

bench_models = list(df1['Bench models'])
print("==> Bench models\n", bench_models);

wood = dict(zip(bench_models, df1['Wood']))
print("==> Wood\n", wood)
      
hand_labour = dict(zip(bench_models, df1['Hand labour']))
print("==> Hand labour\n", hand_labour)

profits = dict(zip(bench_models, df1['Profits']))
print("==> Profits\n", profits)

df2 = read_excel("Data_EX5.xlsx", nrows=2, usecols=(['Resources']))
print("==> Dataframe 2\n", df2)

resources = list(df2['Resources'])
print("==> Resources\n", resources)

model = LpProblem("Carpinteiro", LpMaximize)

x = LpVariable.dicts("x", bench_models, lowBound=0, cat=LpInteger)

model += lpSum([profits[i]*x[i] for i in bench_models])

model += lpSum([wood[i] * x[i] for i in bench_models]) <= resources[0]
model += lpSum([hand_labour[i] * x[i] for i in bench_models]) <= resources[1]

model.solve()

print("--------------- Resultados ---------------")
print(f"Estado: {model.status} <=> {LpStatus[model.status]}")
print(f"z* = {model.objective.value()}")
for var in model.variables():
    print(f"{var.name}* = {var.value()}")
for name, constraint in model.constraints.items():
    print(f"{name}: {constraint.value()}")    