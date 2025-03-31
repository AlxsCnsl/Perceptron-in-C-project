#ifndef MULTI_LAYER_PERCEPTRON_H
#define MULTI_LAYER_PERCEPTRON_H
#include"perceptron.h"

#define MLP MultiLayerPerceptrons
#define Neuron Perceptron
#define ActT ActivationType
#define ActF ActivationFunction

typedef struct {
    int num_layers;
    Perceptron** perceptrons;
    int* perceptron_per_layer;
    ActF* function_layers;
}MultiLayerPerceptrons;

//INIT
MLP new_mlp(int num_layers, Neuron** perceptrons, int* perceptron_per_layer, ActT* act_fun_per_layer);
void int_mlp_perceptrons(MLP* mlp, int num_imput, double bias, int range);
ActF* init_function_layers(ActT* type_layers, int num_layers);

void train_mlp(MLP* mlp, TrainingConfig conf, Dataset datas);
#endif