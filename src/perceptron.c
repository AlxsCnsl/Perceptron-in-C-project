#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"../include/perceptron.h"
#include"../include/malloctools.h"


//INIT AND FREE____

Perceptron make_perceptron(int num_w, double bias, int range_weight, ActivationFunction function){
    double *w = (double*)malloc(num_w * sizeof(double));
    random_weight_init(w, num_w, range_weight);
    Perceptron perceptron;
    MALLOC_CHECK(w);
    perceptron.num_weights = num_w;
    perceptron.bias = bias;
    perceptron.weights = w;
    perceptron.act_fun = function;
    return perceptron;
}


void random_weight_init(double* weights, int num_w, int range) {
    int i;
    for(i=0; i<num_w; i++){
        weights[i] = -range + ((float)rand() / RAND_MAX) * range*2;;
    }
}


void print_perceptron(Perceptron* perceptron){
    int i;
    printf("bias = %f \n [ ", perceptron->bias);
    for(i=0; i< perceptron->num_weights; i++){
        printf("w%d:%f ",i, perceptron->weights[i]);
    }
    printf("]\n");
}


void free_perceptron(Perceptron* perceptron){
    free(perceptron->weights);
}



// CALCULATE_ACTIVATION ____

int calculate_activation_step_function(double weighted_sum){
    return (weighted_sum > 0) ? 1 : 0;
}


double calculate_activation_linear_function(double weighted_sum){
    return weighted_sum;
}


double calculate_activation_sigmoid_function(double weighted_sum){
    return (1/(1+exp(-weighted_sum)));
}


double calculate_activation_function(double weighted_sum,
ActivationFunction fun){
    switch (fun){
    case ACTIVATION_STEP:
        return calculate_activation_step_function(weighted_sum);
    case ACTIVATION_LINEAR:
        return calculate_activation_linear_function(weighted_sum);
    case ACTIVATION_SIGMOID:
        return calculate_activation_sigmoid_function(weighted_sum);
    default:
        fprintf(stderr, "Erreur: Fonction d'activation non supportée.\n");
        exit(1);
    }
}



// TRAINING ____

TrainingConfig new_training_config(int epoch, int max_win,
double learning_rate, double epsilon){
    TrainingConfig conf;
    conf.epoch = epoch;
    conf.max_win = max_win;
    conf.learning_rate = learning_rate;
    conf.epsilon = epsilon;
    return conf;
}


Dataset new_dataset(double* inputs, int row_size, int column_size,  double* expected_outputs){// À MODIFIER / RETIRER APRES MODIFS
    Dataset data;
    data.inputs = make_data_inputs(inputs, row_size, column_size);
    data.size = row_size;
    data.expected_outputs = expected_outputs;
    return data;
}


int trainPerceptron(Perceptron* p, Dataset data, TrainingConfig conf){
    int i, y, win = 0;;
    for(i = 0; i< data.size; i++){
        double weighted_sum = compute_weighted_sum( p, data.inputs[i], p->num_weights );
        double actual_output = calculate_activation_function(weighted_sum, p->act_fun);
        if(!compare_outputs(actual_output, data.expected_outputs[i], conf.epsilon)){
            for(y=0; y < p->num_weights; y++){
                printf("lose\n");
                adjust_weights_bias(p, y, conf.learning_rate, data.inputs[i], data.expected_outputs[i], actual_output);
            }
        }else{
            printf("win\n");
            win ++;
        }
    } double winrate = ((double)win / data.size) * 100;
    printf("WINRATE : %f %%\n", winrate);
    print_perceptron(p);//TEST ICI
    if(winrate == 100.0){
        return 1;
    }
    return 0;
}

void multiTrainPerceptron(Perceptron* p, Dataset data, TrainingConfig conf){
    int win_counter = 0; 
    int i;
    for(i = 0; i< conf.epoch; i ++){
        printf("EPOCH = %d/%d\n", i, conf.epoch);
        if(trainPerceptron(p, data, conf) == 1){
            win_counter ++;
        }else{
            win_counter = 0;
        }
        if(win_counter == conf.max_win){
            break;
        }
    }
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
    if(p->num_weights != x_size){
        fprintf(stderr, "Erreur de taille d'xputs \n");
        exit(1);
    }
}


void adjust_weights_bias(Perceptron* p, int w_index, double learning_rate,
double input[],  double expected_output, double actual_output){
    switch (p->act_fun){
        case ACTIVATION_STEP:
            return adjust_weigths_bias_step_linear(p, w_index, learning_rate, input, expected_output, actual_output);
        case ACTIVATION_LINEAR:
            return adjust_weigths_bias_step_linear(p, w_index, learning_rate, input, expected_output, actual_output);
        case ACTIVATION_SIGMOID:
            return adjust_weigths_bias_sigmoid(p, w_index, learning_rate, input, expected_output, actual_output);
        default:
            fprintf(stderr, "Erreur: Fonction d'activation non supportée.\n");
            exit(1);
        }
}


void adjust_weigths_bias_step_linear(Perceptron* p, int w_index, double learning_rate,
double input[],  double expected_output, double actual_output ){
    double error = learning_rate * (expected_output - actual_output);
    p->weights[w_index] = p->weights[w_index] + error * input[w_index];
    p->bias = p->bias + error;
}


void adjust_weigths_bias_sigmoid(Perceptron* p, int w_index, double learning_rate,
double input[],  double expected_output, double actual_output){
    double error = learning_rate * (expected_output - actual_output);
    double sigmo_prime = actual_output*(1-actual_output);
    p->weights[w_index] = p->weights[w_index] + error * sigmo_prime * input[w_index];
    p->bias = p->bias + error * sigmo_prime;
}


    
int compare_outputs(double expected_output, double actual_output,
double epsilon){
    if(fabs(actual_output - expected_output)<epsilon){
        return 1;
    }
    return 0;
}


double** make_data_inputs(double* data_inputs,  int row_size, int column_size) {
    double** data_inputs_remake = (double**)malloc(row_size * sizeof(double*));
    for (int i = 0; i < row_size; i++) {
        data_inputs_remake[i] = (double*)malloc(column_size * sizeof(double));
    }
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < column_size; j++) {
            data_inputs_remake[i][j] = data_inputs[i * column_size + j];
        }
    }
    return data_inputs_remake;
}



//PROMPT

double get_output_perceptron(Perceptron* p, double input[], int i_size){
    int i;
    double weighted_sum = compute_weighted_sum( p, input, p->num_weights );
    double output = calculate_activation_function(weighted_sum, p->act_fun);
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
