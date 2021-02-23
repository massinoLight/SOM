#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "main.h"



void alloc_array_struct(int n);
void average_vec(int n);
void min_vec(double k);
void max_vec(double k);
void norm_array_vec(int i,int size);
void denorm_array_vec(int n);
double* init_rand_w();
void init_shuffle(int n);
void init_poids_synaptiques();
void array_shuffle(int n);
double euc_distance(double *a1, double *a2, int n);
void calc_alpha(int it_n, int tot_it);
#define SQR(x) ((x)*(x)) //c'est stylé
double* init_rand_nodes();
double* get_rand_data(int pos);
void update_parametres(int t);
int* get_voisinage(int X1,int Y1);



