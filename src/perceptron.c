#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"../include/perceptron.h"
#include"../include/malloctools.h"

Perceptron make_perceptron(int w_size, double b, int range){
    double *w = (double*)malloc(w_size * sizeof(double));
    random_weight_init(w, w_size, range);
    Perceptron perceptron;
    MALLOC_CHECK(w);
    perceptron.weights_size = w_size;
    perceptron.bias = b;
    perceptron.weights = w;
    return perceptron;
}

//INIT AND FREE____

void random_weight_init(double* weights, int w_size, int range) {
    int i;
    for(i=0; i<w_size; i++){
        weights[i] = -range + ((float)rand() / RAND_MAX) * range*2;;
    }
}


void print_perceptron(Perceptron* perceptron){
    int i;
    printf("bias = %f \n [ ", perceptron->bias);
    for(i=0; i< perceptron->weights_size; i++){
        printf("w%d:%f ",i, perceptron->weights[i]);
    }
    printf("]\n");
}


void free_perceptron(Perceptron* perceptron){
    free(perceptron->weights);
}


// CALCULATE_ACTIVATION ____

double calculate_activation_function(double weighted_sum,
    ActivationFunction fun){
        switch (fun){
        case ACTIVATION_STEP:
            return calculate_activation_step_function(weighted_sum);
        case ACTIVATION_LINEAR:
            return calculate_activation_linear_function(weighted_sum);
        default:
            fprintf(stderr, "Erreur: Fonction d'activation non supportée.\n");
            exit(1);
        }
    }
    

int calculate_activation_step_function(double weighted_sum){
    return (weighted_sum > 0) ? 1 : 0;
}


int calculate_activation_linear_function(double weighted_sum){
    return weighted_sum;
}

// TRAINING ____

int trainPerceptron(Perceptron* p, double** data_inputs, 
    double expected_output[], int d_i_size, double learning_rate,
    double epsilon, ActivationFunction fun){
        int i, y, win = 0;;
        for(i = 0; i< d_i_size; i++){
            double weighted_sum = compute_weighted_sum( p, data_inputs[i], p->weights_size );
            double actual_output = calculate_activation_function(weighted_sum, fun);
            if(!compare_outputs(actual_output, expected_output[i], epsilon)){
                for(y=0; y < p->weights_size; y++){
                    printf("lose\n");
                    adjust_weights_bias(p, y, learning_rate, data_inputs[i], expected_output[i], actual_output);
                }
            }else{
                printf("win\n");
                win ++;
            }
        } double winrate = (win / d_i_size) * 100;
        printf("WINRATE : %f %%\n", winrate);
        if(winrate == 100.0){
            return 1;
        }
        return 0;
    }


double compute_weighted_sum(Perceptron* p, double inputs[], int i_size){
    double S = 0.0;
    int i;
    check_inputs_outputs(p, inputs, i_size);
    for(i=0; i<i_size; i++){
        S+= inputs[i] * p->weights[i];
    }
    S+= p->bias;
    return S;
}


void check_inputs_outputs(Perceptron* p, double xputs[], int x_size){//à modifier plus tard 
    if(xputs == NULL){
        fprintf(stderr, "Erreur d'xputs NULL \n");
        exit(1);
    }
    if(p->weights_size != x_size){
        fprintf(stderr, "Erreur de taille d'xputs \n");
        exit(1);
    }
}


void adjust_weights_bias(Perceptron* p, int w_index, double learning_rate,
double input[],  double expected_output, double actual_output ){
    double error = learning_rate * (expected_output - actual_output);
    p->weights[w_index] = p->weights[w_index] + error * input[w_index];
    p->bias = p->bias + error;
}

    
int compare_outputs(double expected_output, double actual_output,
double epsilon){
    if(fabs(actual_output - expected_output)<epsilon){
        return 1;
    }
    return 0;
}


double** make_data_inputs(double* data_inputs, int size1, int size2) {
    double** data_inputs_remake = (double**)malloc(size1 * sizeof(double*));
    for (int i = 0; i < size1; i++) {
        data_inputs_remake[i] = (double*)malloc(size2 * sizeof(double));
    }
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            data_inputs_remake[i][j] = data_inputs[i * size2 + j];
        }
    }
    return data_inputs_remake;
}


//PROMPT



double give_resulte_prompt(Perceptron* p, double input[], int i_size, ActivationFunction fun){
    int i;
    double weighted_sum = compute_weighted_sum( p, input, p->weights_size );
    double output = calculate_activation_function(weighted_sum, fun);
    printf("input > [%s]/ output > %f\n", input_prompt_str(input, i_size), output );
    return output;
}


char* input_prompt_str(double input[], int size){
    int i;
    int total_size = 0;
    for (i = 0; i < size; i++) {
        total_size += 20;
    }
    char* result = (char*)malloc(total_size * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0'; 
    for (i = 0; i < size; i++) {
        char buffer[20];
        sprintf(buffer, "Valeur : %.2f ", input[i]);
        strcat(result, buffer);
    }
    return result;
}




