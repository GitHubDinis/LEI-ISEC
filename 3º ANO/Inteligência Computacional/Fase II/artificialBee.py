import os
import pandas as pd
from SwarmPackagePy import aba
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
data = data.sample(frac=0.05, random_state=42)

# Separar os valores da tabela do DataFrame
image_names = data['image_name'].tolist()
labels = data['label'].tolist()

# Separar as imagens em conjuntos de treino e teste, usando 80% para treino e 20% para teste
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

# Função para carregar e redimensionar imagens
def load_and_process_image(image_name, target_size=(28, 28)):
    image_path = os.path.join("C:/Users/Utilizador/Desktop/ISEC - LEI/4º ANO/IC/FASE II/FASE II/images", image_name)
    img = load_img(image_path, target_size=target_size)
    img_array = img_to_array(img)
    img_array /= 255.0

    return img_array

# Carregar e redimensionar imagens de treino e teste
X_train = np.array([load_and_process_image(img) for img in X_train])
X_test = np.array([load_and_process_image(img) for img in X_test])

# Função de avaliação para o ABA
def evaluate_model(params):
    learning_rate = params[0]
    num_neurons = int(params[1])

    # Construir o modelo de rede neural
    model = MLPClassifier(hidden_layer_sizes=(num_neurons,), max_iter=100)

    # Treinar o modelo nos dados de treino
    model.fit(X_train.reshape(X_train.shape[0], -1), y_train)

    # Avaliar o modelo nos dados de teste
    y_pred = model.predict(X_test.reshape(X_test.shape[0], -1))
    accuracy = accuracy_score(y_test, y_pred)

    return 1.0 / accuracy  # Objetivo é minimizar, então usamos a inversa da acurácia como fitness

# Parâmetros do ABA
n_agents = 50
lb = [0.001, 2]  # Limites inferiores para taxa de aprendizado e número de neurônios
ub = [0.1, 20]   # Limites superiores para taxa de aprendizado e número de neurônios
dimension = 2
iterations = 100

# Criação da instância da classe ABA
aba_nn = aba(n_agents, evaluate_model, lb, ub, dimension, iterations)

print(f"Best Parameters - {aba_nn.get_Gbest()}")

# Obter os melhores hiperparâmetros
best_hyperparameters = aba_nn.get_Gbest()

#
print("Best Parameters: ", best_hyperparameters)

# Avaliar o modelo final com os melhores hiperparâmetros
final_model = MLPClassifier(hidden_layer_sizes=(int(best_hyperparameters[1]),), max_iter=100)
final_model.fit(X_train.reshape(X_train.shape[0], -1), y_train)
y_pred_final = final_model.predict(X_test.reshape(X_test.shape[0], -1))
accuracy_final = accuracy_score(y_test, y_pred_final)
print("Accuracy on Test Data (after optimization): {:.2f}%".format(accuracy_final * 100))
print("Best Hyperparameters:")
print("Learning Rate:", best_hyperparameters[0])
print("Number of Neurons:", int(best_hyperparameters[1]))
