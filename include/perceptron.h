#ifndef PERCEPTRON_H
#define PERCEPTRON_H

typedef enum{
    ACTIVATION_STEP,
    ACTIVATION_LINEAR,
} ActivationFunction;

typedef struct {
    int weights_size;
    double *weights;//pointeur vers les poids
    double bias;
}Perceptron;

typedef struct{
    int time;
    int max_win;
    double learning_rate;
    double epsilon;
}TrainingConfig;

typedef struct{
    double** inputs;
    double* expected_outputs;
    int size;
}Dataset;


//INIT AND FREE ____
Perceptron make_perceptron(int w_size, double b, int range);

void random_weight_init(double *weights, int w_size, int range);

void print_perceptron(Perceptron *perceptron);

void free_perceptron(Perceptron *perceptron);


// CALCULATE_ACTIVATION ____
int calculate_activation_step_function(double weighted_sum);

int calculate_activation_linear_function(double weighted_sum);

double calculate_activation_function(double weighted_sum,
    ActivationFunction fun);


// TRAINING ____
TrainingConfig new_training_config(int time, int max_win,
double learning_rate, double epsilon);

Dataset new_dataset(double* inputs, int row_size, int column_size,  double* expected_outputs);

int trainPerceptron(Perceptron* p, Dataset data, TrainingConfig conf, ActivationFunction fun);

void multiTrainPerceptron(Perceptron* p, Dataset data, TrainingConfig conf, ActivationFunction fun);

double compute_weighted_sum(Perceptron* p, double inputs[], int i_size);

void check_inputs_outputs(Perceptron* p, double xputs[], int i_size);

void adjust_weights_bias(Perceptron* p, int w_index, double learning_rate,
    double input[],  double expected_output, double actual_output );

int compare_outputs(double expected_output, double actual_output,
    double epsilon);

double** make_data_inputs(double* data_inputs, int row_size, int column_size);


//PROMPTE ___
double give_resulte_prompt(Perceptron* p, double input[], int i_size, ActivationFunction fun);

char* input_prompt_str(double input[], int size);

#endif