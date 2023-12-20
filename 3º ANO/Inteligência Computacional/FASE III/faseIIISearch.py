# -*- coding: utf-8 -*-
"""
Fase III - Aprendizagem por Transferência (Grid Search e Random Search)
"""

import os
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from tensorflow.keras.preprocessing.image import img_to_array, load_img
from tensorflow.keras.applications.vgg16 import VGG16
from tensorflow.keras.applications.vgg16 import preprocess_input
from keras.models import Sequential
from keras.layers import Dense, Flatten, Dropout
from tensorflow.keras.utils import to_categorical
from sklearn.model_selection import GridSearchCV, RandomizedSearchCV
from sklearn.metrics import accuracy_score
from sklearn.utils import shuffle


# Carregar os dados de treino
train = "C:/Users/Utilizador/Desktop/ISEC - LEI/4º ANO/1º SEMESTRE/IC/FASE III/train.csv"

# Carregar os dados de treino para um DataFrame do "Pandas"
data = pd.read_csv(train)

# Selecionar aleatoriamente 5% do total de imagens do DataSet
data = data.sample(frac=0.05, random_state=42)

# Separar os valores da tabela do DataFrame
image_names = data['image_name'].tolist()
labels = data['label'].tolist()

# Redefinir as proporções para 60% treino, 20% validação, 20% teste
X_temp, X_test, y_temp, y_test = train_test_split(
    image_names, labels, test_size=0.2, random_state=42
)
X_train, X_val, y_train, y_val = train_test_split(
    X_temp, y_temp, test_size=0.25, random_state=42
)

# Converter as listas para DataFrames
y_train_df = pd.DataFrame({'label': y_train})
y_test_df = pd.DataFrame({'label': y_test})
y_val_df = pd.DataFrame({'label': y_val})

# Contar o número de imagens para cada label no conjunto de treino
label_counts_train = y_train_df['label'].value_counts()

# Imprimir o número de imagens para cada label no conjunto de treino
print("Número de imagens por label no conjunto de treino:")
for label, count in label_counts_train.items():
    print(f'Label: {label}, Número de Imagens: {count}')

# Contar o número de imagens para cada label no conjunto de teste
label_counts_test = y_test_df['label'].value_counts()

# Imprimir o número de imagens para cada label no conjunto de teste
print("\nNúmero de imagens por label no conjunto de teste:")
for label, count in label_counts_test.items():
    print(f'Label: {label}, Número de Imagens: {count}')

# Contar o número de imagens para cada label no conjunto de validação
label_counts_val = y_val_df['label'].value_counts()

# Imprimir o número de imagens para cada label no conjunto de validação
print("\nNúmero de imagens por label no conjunto de validação:")
for label, count in label_counts_val.items():
    print(f'Label: {label}, Número de Imagens: {count}')

# Função para carregar e redimensionar imagens
def load_and_process_image(image_name, target_size=(224, 224)):
    image_path = os.path.join("C:/Users/Utilizador/Desktop/ISEC - LEI/4º ANO/1º SEMESTRE/IC/FASE III/images", image_name)
    img = load_img(image_path, target_size=target_size)
    img_array = img_to_array(img)
    img_array = preprocess_input(img_array)
    return img_array

# Carregar e redimensionar imagens de treino, teste e validação
X_train = np.array([load_and_process_image(img) for img in X_train])
X_test = np.array([load_and_process_image(img) for img in X_test])
X_val = np.array([load_and_process_image(img) for img in X_val])

# One-hot encode das labels
num_classes = len(np.unique(labels))
y_train = to_categorical(y_train, num_classes)
y_test = to_categorical(y_test, num_classes)
y_val = to_categorical(y_val, num_classes)

# Função para criar o modelo Keras
def create_model(hidden_layer_sizes=(128,), dropout_rate=0.5):
    base_model = VGG16(weights='imagenet', include_top=False, input_shape=(224, 224, 3))
    
    for layer in base_model.layers:
        layer.trainable = False
    
    model = Sequential()
    model.add(base_model)
    model.add(Flatten())
    model.add(Dense(256, activation='relu'))
    model.add(Dropout(dropout_rate))
    model.add(Dense(num_classes, activation='softmax'))
    
    model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
    
    return model

# Parâmetros para a pesquisa em grelha
param_grid = {
    'hidden_layer_sizes': [(128,), (256,), (512,)],
    'dropout_rate': [0.2, 0.5, 0.8],  # Adicione valores desejados para dropout
}

# Pesquisa em grelha
best_grid_model = None
best_grid_score = float('-inf')

for hidden_size in param_grid['hidden_layer_sizes']:
    for dropout_rate in param_grid['dropout_rate']:
        model = create_model(hidden_layer_sizes=hidden_size, dropout_rate=dropout_rate)
        model.fit(X_train, y_train, epochs=10, batch_size=32, verbose=0)
        score = model.evaluate(X_val, y_val)[1]  # Use accuracy as the score
        print(f'Parameters: hidden_size={hidden_size}, dropout_rate={dropout_rate}, Score: {score}')
        
        if score > best_grid_score:
            best_grid_score = score
            best_grid_model = model

# Parâmetros para a pesquisa aleatória
param_dist = {
    'hidden_layer_sizes': [(128,), (256,), (512,)],
    'dropout_rate': [0.2, 0.5, 0.8],  # Adicione valores desejados para dropout
}

# Pesquisa aleatória
n_iter_search = 10
best_random_model = None
best_random_score = float('-inf')

for _ in range(n_iter_search):
    hidden_size = (np.random.choice(param_dist['hidden_layer_sizes'][0]),)
    dropout_rate = np.random.choice(param_dist['dropout_rate'])
    model = create_model(hidden_layer_sizes=hidden_size, dropout_rate=dropout_rate)
    model.fit(X_train, y_train, epochs=10, batch_size=32, verbose=0)
    score = model.evaluate(X_val, y_val)[1]  # Use accuracy as the score
    print(f'Parameters: hidden_size={hidden_size}, dropout_rate={dropout_rate}, Score: {score}')
    
    if score > best_random_score:
        best_random_score = score
        best_random_model = model



# Treinamento e avaliação dos modelos otimizados no conjunto de teste
y_pred_grid = best_grid_model.predict(X_test)
accuracy_grid = accuracy_score(np.argmax(y_test, axis=1), np.argmax(y_pred_grid, axis=1))

y_pred_random = best_random_model.predict(X_test)
accuracy_random = accuracy_score(np.argmax(y_test, axis=1), np.argmax(y_pred_random, axis=1))

# Comparação de desempenho
print("Accuracy da Pesquisa em Grelha:", accuracy_grid)
print("Accuracy da Pesquisa Aleatória:", accuracy_random)