# -*- coding: utf-8 -*-
"""
Fase III - Aprendizagem por Transferência (VGG16 default)
"""

import os
import numpy as np
import pandas as pd
import pickle
from sklearn.model_selection import train_test_split
from tensorflow.keras.preprocessing.image import img_to_array, load_img
from tensorflow.keras.applications.vgg16 import VGG16
from tensorflow.keras.applications.vgg16 import preprocess_input
from tensorflow.keras import layers, models
from tensorflow.keras.utils import to_categorical

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

# NOVO ______________________________________________________________________

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

# Carregar a arquitetura VGG16 pré-treinada
base_model = VGG16(weights='imagenet', include_top=False, input_shape=(224, 224, 3))

# Congelar as camadas convolucionais
for layer in base_model.layers:
    layer.trainable = False

# Criar um modelo sequencial
model = models.Sequential()

# Adicionar as camadas convolucionais da VGG16 ao modelo
model.add(base_model)

# Adicionar camadas densas para a classificação
model.add(layers.Flatten())
model.add(layers.Dense(165, activation='relu'))
model.add(layers.Dropout(0.3))
model.add(layers.Dense(num_classes, activation='softmax'))

# Compilar o modelo
model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

# Treinar o modelo
model.fit(X_train, y_train, epochs=10, validation_data=(X_val, y_val))

# Avaliar o modelo no conjunto de teste
test_loss, test_acc = model.evaluate(X_test, y_test)
print(f'Acuracy no conjunto de teste: {test_acc}')

# Salvar o modelo
filename = 'modelo_final.pkl'
with open(filename, 'wb') as file:  
    pickle.dump(model, file)