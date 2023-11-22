# -*- coding: utf-8 -*-
"""
Parte V - Exemplo 6 (1ª Abordagem)
"""

from pulp import *

model = LpProblem("PMLO 1", LpMaximize)

x1 = LpVariable("x1", lowBound=0)
x2 = LpVariable("x2", lowBound=0)


model += 4*x1 - 2*x2

model += x1 + x2 <= 10
model += 2*x1 + x2 <= 15
model += 2*x1 + 3*x2 >= 30

print(model)

model.solve()

print("--------------- Resultados ---------------")
print(f"Estado: {model.status} <=> {LpStatus[model.status]}")
print(f"z* = {round(model.objective.value(), 2)}")
for var in model.variables():
    print(f"{var.name}* = {round(var.value(), 2)}")
for name, constraint in model.constraints.items():
    print(f"{name}: {round(constraint.value(), 2)}")