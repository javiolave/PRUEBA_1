#include <stdio.h>

int main() {
    double k[] = {1, 2, 1, 1, 2, 0}; // k1, k2, k3, k4, k5 , extra para q funcione el arreglo
    double W[] = {2, 1, 2}; // W1, W2, W3
    double x[3] = {0, 0, 0}; // x1, x2, x3

    double A[3][3] = { //defino la matriz
        {k[0]+k[1]+k[2]+k[4], -k[2], -k[4]},
        {-k[2], k[2]+k[3], -k[3]},
        {-k[4], -k[3], k[3]+k[4]}
    };

    // Gauss-Jordan 
    for (int i = 0; i < 3; i++) { //iteracion
        for (int j = 0; j < 3; j++) {
            if (j != i) {
                double r = A[j][i]/A[i][i]; //divide el elemento de la fila actual en la columna actual por el elemento de la diagonal de la fila correspondiente
                for (int k = 0; k < 3; k++) {
                    A[j][k] -= r * A[i][k]; //se resta esta cantidad multiplicada por la fila correspondiente a la fila actual
                }
                W[j] -= r * W[i]; //W para mantener la igualdad del sistema
            }
        }
    }

    // solucion
    for (int i = 0; i < 3; i++) { // iterando sobre cada fila de la matriz y dividiendo el elemento en la columna correspondiente de W por el elemento de la diagonal de la misma fila en la matriz A.
        x[i] = W[i] / A[i][i]; // dividir cada término independiente de W por su correspondiente elemento diagonal
    }

    // Printeo
    printf("x1 = %lf\n", x[0]);
    printf("x2 = %lf\n", x[1]);
    printf("x3 = %lf\n", x[2]);

    //comprobuebo

    double k1 = 1, k2 = 2, k3 = 1, k4 = 1, k5 = 2;
    double W1 = 2, W2 = 1, W3 = 2;
    double x1 = x[0], x2 = x[1], x3 = x[2];

    double resultado1 = (k1 + k3 + k4 + k5) * x1 - k3 * x2 - k5 * x3;
    double resultado2 = k3 * x1 + (k3 + k4) * x2 - k4 * x3;
    double resultado3 = -k5 * x1 - k4 * x2 + (k4 + k5) * x3;

    if (resultado1 == W1 && resultado2 == W2 && resultado3 == W3) {
        printf("Los valores de x1, x2 y x3 son soluciones del sistema de ecuaciones, ta weno.\n");
    } else {
        printf("Los valores de x1, x2 y x3 no son soluciones del sistema de ecuaciones, ta malo.\n");
    }

    

    return 0;
}









