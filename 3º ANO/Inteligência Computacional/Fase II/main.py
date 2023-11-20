# -*- coding: utf-8 -*-
"""
Fase II - Inteligência Computacional
"""

import os
import pandas as pd
from SwarmPackagePy import pso
from SwarmPackagePy import animation, animation3D
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score
from tensorflow.keras.preprocessing.image import img_to_array, load_img
import numpy as np

# Carregar os dados de treino
train = "C:/Users/Utilizador/Desktop/ISEC - LEI/4º ANO/IC/FASE II/FASE II/train.csv"

# Carregar os dados de treino para um DataFrame do "Pandas"
data = pd.read_csv(train)

# Selecionar aleatoriamente 50% do total de imagens
data = data.sample(frac=0.30, random_state=42)

# Separar os valores da tabela do DataFrame
image_names = data['image_name'].tolist()
labels = data['label'].tolist()

# Imprimir o <image_name> e o respetivo <label>
for image_name, label in zip(image_names, labels):
    print(f'Image Name: {image_name}, Label: {label}')

# Separar as imagens em conjuntos de treino e teste
X_train, X_test, y_train, y_test = train_test_split(data['image_name'], data['label'], test_size=0.2, random_state=42)

# Contar o número de imagens para cada label no conjunto de treino
label_counts_train = y_train.value_counts()

# Imprimir o número de imagens para cada label no conjunto de treino
print("Número de imagens por label no conjunto de treino:")
for label, count in label_counts_train.items():
    print(f'Label: {label}, Número de Imagens: {count}')

# Contar o número de imagens para cada label no conjunto de teste
label_counts_test = y_test.value_counts()

# Imprimir o número de imagens para cada label no conjunto de teste
print("\nNúmero de imagens por label no conjunto de teste:")
for label, count in label_counts_test.items():
    print(f'Label: {label}, Número de Imagens: {count}')

# FunÃ§Ã£o para carregar e redimensionar imagens
def load_and_process_image(image_name, target_size=(28, 28)):
    image_path = os.path.join("C:/Users/Utilizador/Desktop/ISEC - LEI/4º ANO/IC/FASE II/FASE II/images", image_name)
    img = load_img(image_path, target_size=target_size)
    img_array = img_to_array(img)
    img_array /= 255.0

    return img_array

# Carregar e redimensionar imagens de treino e teste
X_train = np.array([load_and_process_image(img) for img in X_train])
X_test = np.array([load_and_process_image(img) for img in X_test])

# Construir o modelo de rede neural
model = MLPClassifier(hidden_layer_sizes=(300,), max_iter=100)  # Exemplo bÃ¡sico de MLP

# Treinar o modelo nos dados de treino
model.fit(X_train.reshape(X_train.shape[0], -1), y_train)

# Avaliar o modelo nos dados de teste
y_pred = model.predict(X_test.reshape(X_test.shape[0], -1))
accuracy = accuracy_score(y_test, y_pred)
print("Accuracy on Test Data (before optimization): {:.2f}%".format(accuracy * 100))

# FunÃ§Ã£o de avaliaÃ§Ã£o para o PSO
def evaluate(params):
    hidden_layer_sizes = tuple(map(int, params))
    model = MLPClassifier(hidden_layer_sizes=hidden_layer_sizes, max_iter=100)
    model.fit(X_train.reshape(X_train.shape[0], -1), y_train)
    y_pred = model.predict(X_test.reshape(X_test.shape[0], -1))
    accuracy = accuracy_score(y_test, y_pred)
    return -accuracy  # Maximizar a acurÃ¡cia

# Definir os limites para cada hiperparÃ¢metro
lb = [50, 50]  # Limite inferior para os hiperparÃ¢metros
ub = [200, 200]  # Limite superior para os hiperparÃ¢metros

# Criar o otimizador PSO
optimizer = pso(n=10, function=evaluate, lb=lb, ub=ub, dimension=2, iteration=10)

print(f"Best Parameters - {optimizer.get_Gbest()}")

best_hidden_layer_sizes = tuple(map(int, optimizer.get_Gbest()))
print("Best Parameters: ", best_hidden_layer_sizes)

best_model = MLPClassifier(hidden_layer_sizes=best_hidden_layer_sizes, max_iter=100)
best_model.fit(X_train.reshape(X_train.shape[0], -1), y_train)
y_pred_best = best_model.predict(X_test.reshape(X_test.shape[0], -1))
accuracy_best = accuracy_score(y_test, y_pred_best)
print("Accuracy on Test Data (after optimization): {:.2f}%".format(accuracy_best * 100))

animation(optimizer.get_agents(), evaluate, 50, 200)
animation3D(optimizer.get_agents(), evaluate, 50, 200)