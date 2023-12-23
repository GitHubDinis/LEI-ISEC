# -*- coding: utf-8 -*-
"""
Mini-Teste 3 (Minimização)
"""

# Importar biblioteca PuLP / Import PuLP library
from pulp import *

# Importar sub-modulo Pyplot da biblioteca Matplotlib
# Import sub-module Pyplot from libray Matplotlib
import matplotlib.pyplot as plt 

# Inicializar duas listas para guardar pontos extremos (PE) da região eficiente  
# e respetivos valores de z1 e z2 / Initialize two lists to save extreme points 
# (EP) of efficient region and respective values of z1 and z2
X=[]
Z=[]
# Criar variáveis de decisão / Create decision variables
x1=LpVariable("x1",lowBound=0)
x2=LpVariable("x2",lowBound=0)

# Para determinar PE usa abordagem da soma ponderada das duas funções objetivo
# To find EP use approach of the weighted sum of two objective functions
# Definir incremento de  alpha / Define step-size for alpha
step = 0.1
# Numero total de amostras / Total number of samples
n = int(1/step)
# Iterar para valores de alpha (peso) entre 0 e 1 
# Iterate through alpha (weight) values from 0 to 1 
for i in range(0,n+1):
        # Calcula valor de alpha / Calculate alpha value
        alpha=i/n 
        # Criar novo modelo / Create new model
        model=LpProblem("PLMO_2/MOLP_2", LpMinimize)
        # Adicionar funcao objetivo z = alpha*z1 + (1-alpha)*z2 
        # Add objective function z = alpha*z1 + (1-alpha)*z2 
        model += alpha*(x1 + 3*x2)+(1-alpha)*(x1-x2)
        # Adicionar restricoes / Add constraints
        model += -2*x1 + x2 <= 8
        model += 2*x1 + 3*x2 <= 30
        model += 5*x1 + 4*x2 <= 60
        model += x1 - 2*x2 <= 6
        # Resolver modelo / Solve model 
        model.solve()
        # Guardar cada nova solução determinada pois é PE da região eficiente
        # Save each new solution found since it is an EP of efficient region 
        if X.count([value(x1),value(x2)]) == 0:
                X=X+[[value(x1),value(x2)]]
                
# Mostra PE da região eficiente / Show EP of efficient region
print("Extreme points of the efficient region:\n",X)
# Calcula valores correspondentes de z1 e z2 
# Find corresponding values of z1 and z2
for i in range(0, len(X)):
    Z=Z+[[X[i][0]+X[i][1],2*X[i][0]]]
# Mostra imagem dos PE no espaço das funcoes objetivo 
# Show image of EP in objective function space
print("Images of these EP in objective function space:\n",Z)            

# Constroi vetores para os graficos / Set vectors for the graphics
XX1=[] # Valores do eixo de x1 / Values of x1 axis
XX2=[] # Valores do eixo de x2 / Values of x2 axis
ZZ1=[] # Valores do eixo de z1 / Values of z1 axis
ZZ2=[] # Valores do eixo de z2 / Values of z2 axis
for i in range(0, len(X)):
    XX1=XX1+[X[i][0]]
    XX2=XX2+[X[i][1]]
    ZZ1=ZZ1+[Z[i][0]]
    ZZ2=ZZ2+[Z[i][1]]
 
# Soluções ideal e anti-ideal / Ideal and anti-ideal solutions  
ideal=[min(ZZ1),min(ZZ2)]
anti_ideal=[max(ZZ1),max(ZZ2)] 
print("---> Ideal solution =",ideal)
print("---> Anti-ideal solution =",anti_ideal)

# Grafico no espaço das variaveis de decisao
# Graphic in the space of decision variables
# -- Inicializar tamanho da figura / Set figure size
plt.figure(figsize=(20,10))
# -- Criar grafico de linhas / Create line plot
plt.plot(XX1,XX2,color="green")
plt.scatter(XX1,XX2,color="red",linewidth=6.0)
# -- Adicionar legendas dos eixos / Add axis labels
plt.xlabel("x1",size=20)
plt.ylabel("x2",size=20)
# -- Adicionar titulo ao grafico / Add plot title
plt.title("Efficient region",size=32)
# -- Mostrar coordenadas dos PE / Show coordinates of EP
for i, j in zip(XX1,XX2):
   plt.text(i,j,'({}, {})'.format(round(i,2), round(j,2)))
# -- Mostrar grafico / Show plot
plt.show()
input("Press ENTER to continue...")
# Grafico no espaço das funcoes objetivo
# Graphic in the objective space
# -- Inicializar tamanho da figura / Set figure size
plt.figure(figsize=(20,10))
# -- Criar grafico de linhas / Create line plot
plt.plot(ZZ1,ZZ2,color="blue")
plt.scatter(ZZ1,ZZ2,color="red",linewidth=6.0)
# -- Adicionar legendas dos eixos / Add axis labels
plt.xlabel("z1",size=20)
plt.ylabel("z2",size=20)
# -- Adicionar titulo ao grafico / Add plot title
plt.title("Non-dominated region",size=32)
# -- Mostrar coordenadas dos PE / Show coordinates of EP
for i, j in zip(ZZ1,ZZ2):
    plt.text(i,j,'({}, {})'.format(round(i,2), round(j,2)))
# -- Mostrar grafico / Show plot
plt.show()

