"""
Mini-Teste Prático 1
"""

from pulp import *

# Criar modelo
model = LpProblem("Queima-de-Lixo", LpMinimize)

# Definir variáveis de decisão
x1 = LpVariable("x1", 0)
x2 = LpVariable("x2", 0)
x3 = LpVariable("x3", 0)

# Adicionar função objetivo ao modelo
model += 13.8*x1 + 15.4*x2 + 18.2*x3

# Adicionar restrições ao modelo
model += x1 + x2 + x3 == 100
model += 1.4*x1 + 2.3*x2 <= 82
model += 9.1*x1 + 4.5*x2 <= 290
model += x1 <= 28
model += x2 <= 30

# Visualizar modelo
print("---------- Modelo ----------")
print(model)

# Resolver modelo
model.solve()

# Mostrar resultados
print("--------------- Resultados ---------------")
print(f"Estado: {model.status} <=> {LpStatus[model.status]}")
print(f"z* = {round(model.objective.value(), 2)}")
for var in model.variables():
    print(f"{var.name}* = {round(var.value(), 2)}")
for name, constraint in model.constraints.items():
    print(f"{name}: {round(constraint.value(), 2)}")