#ifndef PERCEPTRON_H
#define PERCEPTRON_H

typedef struct {
    int weights_size;
    double *weights;//pointeur vers les poids
    double bias;
}Perceptron;

Perceptron makePerceptron(int w_size, double b, int range);
void randomWeightInit(double *weights, int w_size, int range); //test de retiré du main pour voir ce que ça fait
void printPerceptron(Perceptron *perceptron);
void freePerceptron(Perceptron *perceptron);

#endif