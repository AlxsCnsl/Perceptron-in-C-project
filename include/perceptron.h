#ifndef PERCEPTRON_H
#define PERCEPTRON_H

typedef enum{
    ACTIVATION_STEP,
    ACTIVATION_LINEAR,
    ACTIVATION_SIGMOID,
}ActivationType;

typedef enum{
    GRADIENT_DESCENT,
    ADAM,
}WeightUpdateType;

typedef struct{
    double (*activation)(double x);
    double (*activation_prime)(double x);
}ActivationFunction;

typedef struct {
    int num_weights;
    double *weights;//Inputs tab
    double bias;
    ActivationFunction act_fun;
}Perceptron;

typedef void (*WeightUpdateFunction)(Perceptron* p, int w_index, double learning_rate,
    double input[],  double expected_output, double actual_output);

typedef struct{
    int epoch;
    int max_win;
    double learning_rate;
    double epsilon;
    WeightUpdateFunction function;
}TrainingConfig;

typedef struct{
    double** inputs;
    double* expected_outputs;
    int size;
}Dataset;


//INIT AND FREE ____
Perceptron make_perceptron(int num_weights, double b, int range_weight, ActivationType act_type);

ActivationFunction init_activation_function(ActivationType act_type);

void random_weight_init(double *weights, int num_weights, int range);

void print_perceptron(Perceptron *perceptron);

void free_perceptron(Perceptron *perceptron);


// CALCULATE_ACTIVATION ____

double step(double x);
double step_prime(double x);


double sigmoid(double x);
double sigmoid_prime(double x);


double linear(double x);
double linear_prime(double x);


// TRAINING ____
TrainingConfig new_training_config(int epoch, int max_win,
    double learning_rate, double epsilon, WeightUpdateType w_update);

WeightUpdateFunction define_weight_update_function(WeightUpdateType w_update);

Dataset new_dataset(double* inputs, int row_size, int column_size,  double* expected_outputs);

int trainPerceptron(Perceptron* p, Dataset data, TrainingConfig conf);

void multiTrainPerceptron(Perceptron* p, Dataset data, TrainingConfig conf);

double compute_weighted_sum(Perceptron* p, double inputs[], int i_size);

void check_inputs_outputs(Perceptron* p, double xputs[], int i_size);

void adjust_weights_gradient_descent(Perceptron* p, int w_index, double learning_rate,
    double input[],  double expected_output, double actual_output );

int compare_outputs(double expected_output, double actual_output,
    double epsilon);

double** make_data_inputs(double* data_inputs, int row_size, int column_size);


//PROMPTE ___
double get_output_perceptron(Perceptron* p, double input[], int i_size);

char* input_prompt_str(double input[], int size);

#endif