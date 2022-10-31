import tensorflow as tf
import tensorflow.keras as keras
import matplotlib.pyplot as plt
from keras.layers import Conv2D, Dense
from keras.layers import MaxPooling2D, Flatten
from keras.layers import UpSampling2D, Reshape
from keras.layers import BatchNormalization, Conv2DTranspose
from keras.layers import Input
from keras import optimizers
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split
import numpy as np
import argparse

#Parsing command line arguments
parser = argparse.ArgumentParser()
parser.add_argument("-d", action="store", dest="dataset", type=str)
parser.add_argument("-q", action="store", dest="queryset", type=str)
parser.add_argument("-od", action="store", dest="output_dataset_file", type=str)
parser.add_argument("-oq", action="store", dest="output_query_file", type=str)
args = parser.parse_args()
print("dataset:",args.dataset)
print("queryset:",args.queryset)
print("output_dataset_file:",args.output_dataset_file)
print("output_query_file:",args.output_query_file)

#mnist = tf.keras.datasets.mnist  #να μπει σε σχόλιο στο τέλος

#Load the training data and their labels
#(X_train, Y_train), (x_test, y_test) = mnist.load_data()        #να μπει σε σχόλιο στο τέλος
#################DATA FILE
def readMNIST(dataset_name):
  file = open(dataset_name, "rb")

  magic_number      = int.from_bytes(file.read(4), "big")
  number_of_images  = int.from_bytes(file.read(4), "big")
  number_of_rows    = int.from_bytes(file.read(4), "big")
  number_of_columns = int.from_bytes(file.read(4), "big")
  print("Magic number:     ",magic_number)
  print("Number of images: ",number_of_images)
  print("Number of rows:   ",number_of_rows)
  print("Number of columns:",number_of_columns)

  X = np.ndarray(shape=(number_of_images,number_of_rows,number_of_columns),
				dtype='uint8', order='C')

  curr_img = 0
  curr_row = 0
  curr_col = 0
  for i in range(0,number_of_images*number_of_rows*number_of_columns):
    byte = file.read(1)
    X[curr_img][curr_row][curr_col] = int.from_bytes(byte, "big")
    curr_col = curr_col + 1
    if curr_col == number_of_columns:
      curr_col = 0
      curr_row = curr_row + 1
    if curr_row == number_of_rows:
      curr_row = 0
      curr_img = curr_img + 1
    if i % (number_of_rows*number_of_columns*5000) == 0:
      print("Just loaded imgage number:",int(i/(number_of_rows*number_of_columns)))
  file.close()
  return X

X_train = readMNIST(args.dataset)
x_test = readMNIST(args.queryset)

#reshape dataset to have a single channel
X_train = X_train.reshape((X_train.shape[0], 28, 28, 1))

# convert from uint8  to floats
X_train = X_train.astype('float32')
# normalize to range 0-1
X_train = X_train / 255.0


#split the training data into two parts: a training and a validation set
train_X, valid_X, train_ground, valid_ground = train_test_split(X_train, X_train, test_size=0.25, random_state=13)

batch_size = 64
epochs = 150
inChannel = 1
x, y = 28, 28
input_img = Input(shape = (x, y, inChannel))


def encoder(input_img):

  #input_img 28x28x1
  conv1 = Conv2D(32, (3,3), activation='relu', padding='same')(input_img)   #28 x 28 x 32
  conv1 = BatchNormalization()(conv1)
  pool1 = MaxPooling2D(pool_size=(2,2))(conv1)  #14 x 14 x 32
  conv2 = Conv2D(64, (3,3), activation='relu', padding='same')(pool1) #14 x 14 x 64
  conv2 = BatchNormalization()(conv2)
  pool2 = MaxPooling2D(pool_size=(2,2))(conv2)  #7 x 7 x 64
  conv3 = Conv2D(128, (3,3), activation='relu', padding='same')(pool2) #7 x 7 x 128
  conv3 = BatchNormalization()(conv3)
  conv4 = Conv2D(256, (3,3), activation='relu', padding='same')(conv3) #7 x 7 x 256
  encoded = BatchNormalization()(conv4)
  #NEW LAYERS!!!
  flatten = Flatten()(encoded)  # (None , 12544)
  dense1 = Dense(10, activation="relu")(flatten) # (None , 20)
  return dense1

def decoder(dense1):
  dense2 = Dense(12544, activation="relu")(dense1) # (None ,12544)
  reshape = Reshape((7,7,256))(dense2)
  conv10 = Conv2DTranspose(256, (3,3), activation='relu', padding='same')(reshape) #7 x 7 x 256
  conv10 = BatchNormalization()(conv10)
  conv4 = Conv2DTranspose(128, (3, 3), activation='relu', padding='same')(conv10)  #7 x 7 x 128
  conv4 = BatchNormalization()(conv4)
  conv5 = Conv2DTranspose(64, (3, 3), activation='relu', padding='same')(conv4) # 14 x 14 x 64
  conv5 = BatchNormalization()(conv5)
  up1 = UpSampling2D((2,2))(conv5)             #14 x 14 x 128
  conv6 = Conv2DTranspose(32, (3, 3), activation='relu', padding='same')(up1) # 14 x 14 x 32
  conv6 = BatchNormalization()(conv6)
  up2 = UpSampling2D((2,2))(conv6) # 28 x 28 x 32
  decoded = Conv2DTranspose(1, (3, 3), activation='sigmoid', padding='same')(up2) # 28 x 28 x 1
  return decoded


autoencoder = keras.Model(input_img, decoder(encoder(input_img)))        #!!
autoencoder.compile(loss='mean_squared_error', optimizer = optimizers.RMSprop())  #!!
autoencoder_train = autoencoder.fit(train_X, train_ground, batch_size=batch_size, epochs=epochs, verbose=1,validation_data=(valid_X, valid_ground))  #!!!


epochs_loss = autoencoder_train.history['loss']
epochs_val_loss = autoencoder_train.history['val_loss']
epochs_range = range(epochs)
plt.figure()
plt.plot(epochs_range, epochs_loss, 'purple', label='Training loss')
plt.plot(epochs_range, epochs_val_loss, 'green', label='Validation loss')
plt.xlabel("Epochs")
plt.title('Training and validation loss')
plt.legend()
plt.show()



# Getting the weights from the trained autoencoder that corespond to the encoder weights
only_enc_weights = autoencoder.get_weights()[0:26]

# Creating new model that is only an encoder
encoder1 = keras.Model(input_img, encoder(input_img))
encoder1.compile(loss='mean_squared_error', optimizer = optimizers.RMSprop())

# Setting the optimal weights we already found
encoder1.set_weights(only_enc_weights)

# Runing out model over X_train and x_test to get representations with reduced dimensions
res_train = encoder1.predict(X_train)
res_query = encoder1.predict(x_test)


def normalize_0_25500(values):
    actual_bounds = [0,0]
    actual_bounds[0] = min([min(decad) for decad in values])
    actual_bounds[1] = max([max(decad) for decad in values])
    return [[int(0 + (num - actual_bounds[0]) * (25500 - 0) / (actual_bounds[1] - actual_bounds[0])) for num in decad] for decad in values]

# Normalizin the values in range [0,25500]
res_train_norm = normalize_0_25500(res_train)
res_query_norm = normalize_0_25500(res_query)

# Creating output datasets acording to MNIST format (with reduced dimensions)
# Training Dataset
f1 = open(args.output_dataset_file, "xb") # change name to be taken as input
f1.write((21).to_bytes(4, "big"))                          # magic number
f1.write((np.shape(res_train_norm)[0]).to_bytes(4, "big")) # number of images
f1.write((1).to_bytes(4, "big"))                           # number of rows
f1.write(len(res_train_norm[0]).to_bytes(4, "big"))        # number of columns
for decad in res_train_norm:
  for num in decad:
    f1.write((num).to_bytes(2, "big"))
f1.close()
#Testting-Query Dataset
f2 = open(args.output_query_file, "xb") # change name to be taken as input
f2.write((42).to_bytes(4, "big"))                          # magic number
f2.write((np.shape(res_query_norm)[0]).to_bytes(4, "big")) # number of images
f2.write((1).to_bytes(4, "big"))                           # number of rows
f2.write((len(res_query_norm[0])).to_bytes(4, "big"))      # number of columns
for decad in res_query_norm:
  for num in decad:
    f2.write((num).to_bytes(2, "big"))
f2.close()