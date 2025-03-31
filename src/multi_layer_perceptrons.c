#include<stdio.h>
#include<stdlib.h>
#include "../include/multi_layer_perceptrons.h"



MLP new_mlp(int num_layers, Neuron** perceptrons, int* perceptron_per_layer, ActT* function_layers){
    MLP mlp;
    mlp.num_layers = num_layers;
    mlp.perceptron_per_layer = perceptron_per_layer;
    mlp.function_layers = init_function_layers(function_layers, num_layers);
    mlp.perceptrons = (Perceptron**)malloc(sizeof(Perceptron**));
    //int_mlp_perceptrons(&mlp);
    return mlp;
}

void init_mlp_perceptrons(MLP* mlp, int num_imput, double bias, int range){//PAS FINI
    int i ,j;
    for(i=0; i< mlp->num_layers; i++){
        int size_layer= mlp->perceptron_per_layer[i];
        mlp->perceptrons[i] = (Perceptron*)malloc(size_layer*sizeof(Perceptron*));
        for(j=0; j< size_layer; j++){
            int num_perseptron = mlp->perceptron_per_layer[i];//refliechie 
            mlp->perceptrons[i][j].bias = 0;
            mlp->perceptrons[i][j].num_weights = num_perseptron;
            mlp->perceptrons[i][j].weights = (double*)malloc(num_perseptron*sizeof(double*));//reflechie 
            mlp->perceptrons[i][j].act_fun = mlp->function_layers[i];
        }
    }
}

ActF* init_function_layers(ActT* type_layers, int num_layers){
    ActF* activation_functions = (ActF*)malloc(num_layers*sizeof(ActF*));
    int i;
    for(i=0; i<num_layers; i++){
        activation_functions[i] = init_activation_function(type_layers[i]);
    }
}



void train_mlp(MLP* mlp, TrainingConfig conf, Dataset datas){
    int layer;
    for (layer = 0; layer<mlp->num_layers; layer++){

    }
}