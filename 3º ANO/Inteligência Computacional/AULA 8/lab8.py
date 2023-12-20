# -*- coding: utf-8 -*-
"""
Lab 8.0 (27/11/2023) - IC
"""


from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Conv2D, AveragePooling2D, Flatten
import tensorflow as tf

mnist = tf.keras.datasets.mnist
(x_train, y_train), (x_test, y_test) = mnist.load_data()
x_train, x_test = x_train / 255.0, x_test / 255.0
# Instancia uma rede “Densa” em tf.Keras:

"""    
model = tf.keras.models.Sequential([
 tf.keras.layers.Flatten(input_shape=(28, 28)),
 tf.keras.layers.Dense(128, activation='relu'),
 tf.keras.layers.Dropout(0.2),
 tf.keras.layers.Dense(10, activation='softmax')
])


model.compile(optimizer='adam',
 loss='sparse_categorical_crossentropy',
 metrics=['accuracy'])
#Treina a rede
model.fit(x_train, y_train, epochs=10)
#Avalia para dados de teste
model.evaluate(x_test, y_test, verbose=2)
"""

# Modelo “LeNet”
model = Sequential()
# C1 Convolutional Layer
model.add(tf.keras.layers.Conv2D(6, kernel_size=(5, 5), strides=(1, 1), activation='tanh',
input_shape=(28,28,1), padding='same'))
# S2 Pooling Layer
model.add(tf.keras.layers.AveragePooling2D(pool_size=(2, 2), strides=(1, 1), padding='valid'))
# C3 Convolutional Layer
model.add(tf.keras.layers.Conv2D(12, kernel_size=(5, 5), strides=(1, 1), activation='tanh',
padding='valid'))
# S4 Pooling Layer
model.add(tf.keras.layers.AveragePooling2D(pool_size=(2, 2), strides=(2, 2), padding='valid'))
# C5 Fully Connected Convolutional Layer
model.add(tf.keras.layers.Conv2D(24, kernel_size=(5, 5), strides=(1, 1), activation='tanh',
padding='valid'))
#Flatten the CNN output so that we can connect it with fully connected layers
model.add(tf.keras.layers.Flatten())
# FC6 Fully Connected Layer
model.add(tf.keras.layers.Dense(32, activation='relu'))
#Output Layer
model.add(tf.keras.layers.Dense(10, activation='softmax'))

model.compile(optimizer='adam',
 loss='sparse_categorical_crossentropy',
 metrics=['accuracy'])
#Treina a rede
model.fit(x_train, y_train, epochs=5)
#Avalia para dados de teste
model.evaluate(x_test, y_test, verbose=2)