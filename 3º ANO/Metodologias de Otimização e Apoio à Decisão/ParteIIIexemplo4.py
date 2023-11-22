# -*- coding: utf-8 -*-
"""
Parte III - Exemplo 4
"""

from pandas import read_excel
from pulp import *

df1 = read_excel("Data_EX4.xlsx", nrows=2, usecols=(['Types of food','Minerals','Vitamins','Calcium','Prices']))

print("==> Dataframe 1\n", df1);

food_types = list(df1['Types of food'])
print("==> Food Types\n", food_types)

minerals = dict(zip(food_types, df1['Minerals']))
print("==> Minerals\n", minerals)

vitamins = dict(zip(food_types, df1['Vitamins']))
print("==> Vitamins\n", vitamins)

calcium = dict(zip(food_types, df1['Calcium']))
print("==> Calcium\n", calcium)

prices = dict(zip(food_types, df1['Prices']))
print("==> Prices\n", prices)

df2 = read_excel("Data_EX4.xlsx", nrows=3, usecols=(['Requirements']))

req = list(df2['Requirements'])
print("==> Requirements\n", req)

model = LpProblem("Dieta_Cachorros", LpMinimize);

x = LpVariable.dicts("x", food_types, lowBound=0)

model += lpSum([prices[i]*x[i] for i in food_types])

model += lpSum([minerals[i]*x[i] for i in food_types]) >= req[0]
model += lpSum([vitamins[i]*x[i] for i in food_types]) >= req[1]
model += lpSum([calcium[i]*x[i] for i in food_types]) >= req[2]

model.solve()

print("--------------- Resultados ---------------")
print(f"Estado: {model.status} <=> {LpStatus[model.status]}")
print(f"z* = {round(model.objective.value(), 2)}")
for var in model.variables():
    print(f"{var.name}* = {round(var.value(), 2)}")
for name, constraint in model.constraints.items():
    print(f"{name}: {round(constraint.value(), 2)}")