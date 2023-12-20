# -*- coding: utf-8 -*-
"""
Fase III - Aprendizagem por Transferência (TESTE)
"""

import os
import numpy as np
import pandas as pd
import pickle
from sklearn.model_selection import train_test_split
from tensorflow.keras.preprocessing.image import img_to_array, load_img
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.applications.vgg16 import preprocess_input

# Função para carregar e redimensionar imagens
def load_and_process_image(image_name, target_size=(224, 224)):
    image_path = os.path.join("C:/Users/Utilizador/Desktop/ISEC - LEI/4º ANO/1º SEMESTRE/IC/FASE III/images", image_name)
    img = load_img(image_path, target_size=target_size)
    img_array = img_to_array(img)
    img_array = preprocess_input(img_array)
    return img_array

# Carregar os dados de teste
test_csv_path = "C:/Users/Utilizador/Desktop/ISEC - LEI/4º ANO/1º SEMESTRE/IC/FASE III/teste.csv"
test_data = pd.read_csv(test_csv_path)

# Separar os valores da tabela do DataFrame
test_image_names = test_data['image_name'].tolist()
test_labels = test_data['label'].tolist()

# Imprimir o número de imagens por label no conjunto de teste
label_counts_test = pd.Series(test_labels).value_counts()
print("Número de imagens por label no conjunto de teste:")
for label, count in label_counts_test.items():
    print(f'Label: {label}, Número de Imagens: {count}')

# Carregar e processar imagens de teste
num_classes = len(np.unique(test_labels))
X_test = np.array([load_and_process_image(img) for img in test_image_names])
y_test = to_categorical(test_labels, num_classes)

# Carregar o modelo
filename = 'modelo_final.pkl'
with open(filename, 'rb') as file:
    loaded_model = pickle.load(file)

# Avaliar o modelo no conjunto de teste
loaded_model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
test_loss, test_acc = loaded_model.evaluate(X_test, y_test)
print(f'Acurácia no conjunto de teste: {test_acc}')

from sklearn.metrics import confusion_matrix
import seaborn as sns
import matplotlib.pyplot as plt

# Prever as classes para o conjunto de teste
y_pred = loaded_model.predict(X_test)
y_pred_classes = np.argmax(y_pred, axis=1)
y_true = np.argmax(y_test, axis=1)

# Calcular a matriz de confusão
conf_matrix = confusion_matrix(y_true, y_pred_classes)

# Plotar a matriz de confusão
plt.figure(figsize=(10, 8))
sns.heatmap(conf_matrix, annot=True, fmt='d', cmap='Blues', xticklabels=np.unique(test_labels), yticklabels=np.unique(test_labels))
plt.title('Matriz de Confusão')
plt.xlabel('Predict')
plt.ylabel('Real')
plt.show()

