# -*- coding: utf-8 -*-
"""
Parte V - Exemplo 6 (2ª Abordagem)
"""

from pulp import * 

import matplotlib.pyplot as plt

import pandas as pd


results = pd.DataFrame(columns=["alpha", "x1_opt", "x2_opt", "z1", "z2"])

x1 = LpVariable("x1", lowBound=0)
x2 = LpVariable("x2", lowBound=0)

step = 0.01

for i in range(0, 101, int(step*100)):
    model=LpProblem("PLMO_1", LpMaximize)
    alpha=i/100
    model += alpha*(2*x1+3*x2)+(1-alpha)*(4*x1-2*x2)
    model += x1 + x2 <= 10
    model += 2*x1 + x2 <= 15
    model.solve()
    results.loc[i] = [alpha,
                      value(x1),
                      value(x2),
                      value(alpha*(2*x1+3*x2)),
                      value((1-alpha)*(4*x1-2*x2))]

for i in range(0, 100, 15):
    print(results[i:i+15])
    input("Press ENTER key to continue...")
    
plt.figure(figsize=(20, 10))

plt.plot(results["alpha"], results["z1"], color="red", label="z1")
plt.plot(results["alpha"], results["z2"], color="blue", label="z2")

plt.xlabel("alpha (weigth)", size=20)
plt.ylabel("objective_values", size=20)

plt.title("Objective Functions z1 and z2", size=32)

plt.show()