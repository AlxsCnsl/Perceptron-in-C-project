#ifndef PERCEPTRON_H
#define PERCEPTRON_H

typedef struct {
    int weights_size;
    double *weights;//pointeur vers les poids
    double bias;
}Perceptron;

Perceptron make_perceptron(int w_size, double b, int range);
void random_weight_init(double *weights, int w_size, int range);
void print_perceptron(Perceptron *perceptron);
void free_perceptron(Perceptron *perceptron);

//inferences
double compute_weighted_sum(Perceptron* p, double inputs[], int i_size);
void check_inputs(Perceptron* p, double inputs[], int i_size);
#endif