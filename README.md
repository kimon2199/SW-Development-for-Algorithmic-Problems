# SW-Development-for-Algorithmic-Problems

[Senior Project / Software Development for Algorithmic Problems](https://www.di.uoa.gr/en/studies/undergraduate/261) @ [University of Athens](https://www.di.uoa.gr/en) Winter 2020

## Description

This project is a C++ implementation of LSH (Locality-Sensitive Hashing) and Hypercube algorithms for Approximate Nearest Neighbor Search, as well as K-means clustering algorithm. It also implements a convolutional autoencoder in TensorFlow/Keras. 

## Features

- **Approximate Nearest Neighbor Search**
  - LSH (Locality-Sensitive Hashing)
  - Hypercube algorithm
  - Brute force search implementation for comparison

- **Clustering**
  - K-means clustering
  - Lloyd's algorithm
  - Silhouette scoring
  - Objective function evaluation

- **Dimensionality Reduction**
  - Autoencoder-based neural network
  - MNIST-format compatible input/output
  - Configurable output dimensions

## Requirements

### C++ Components
- C++11 or higher
- g++ compiler
- Make

### Python Component
- Python 3.x
- TensorFlow
- Keras
- NumPy
- Scikit-learn
- Matplotlib

## Installation

1. Clone the repository
2. Compile the C++ components:
```bash
cd ANN && make
cd ../Clustering && make
```
3. Install Python dependencies:
```bash
pip install tensorflow numpy scikit-learn matplotlib
```


## Usage

### Dimensionality Reduction
```bash
python reduce.py -d <dataset_file> -q <query_file> -od <output_dataset_file> -oq <output_query_file>
```

### ANN Search
```bash
./search -d <input_file> -q <query_file> -k <neighbors> -L <hash_tables> -o <output_file>
```

### Clustering
```bash
./cluster -d <input_file> -c <configuration_file> -o <output_file>
```
