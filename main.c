#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "structures.h"
#include "init.c"
#include "main.h"


t_bmu *Bmu = NULL;
int Bmu_size=1;
int position=0;
//pour garder la position du bmu sur la map
int X1=0;
int Y1=0;
int t=0;
int tot_it=0;

/*
Step 0: Randomly position the grid’s neurons in the data space.v

Step 1: Select one data point, either randomly or systematically cycling through the dataset in order

Step 2: Find the neuron that is closest to the chosen data point. This neuron is called the Best Matching Unit (BMU).

Step 3: Move the BMU closer to that data point. The distance moved by the BMU is determined by a learning rate, which decreases after each iteration.

Step 4: Move the BMU’s neighbors closer to that data point as well, with farther away neighbors moving less. Neighbors are identified using a radius around the BMU, and the value for this radius decreases after each iteration.

Step 5: Update the learning rate and BMU radius, before repeating Steps 1 to 4. Iterate these steps until positions of neurons have been stabilized.


*/









/*
Trouver le node le plus proche (BMU) d'un vecteur de données 
prit aléatoirement a l'aide du shuffle table 
*/
int* find_BMU()
{
    int i,j;
    
    double *data=malloc(N_conf.n_in*sizeof(double));
    
    //la position du bmu sur la map
    int *positionXY=malloc(2*sizeof(int));
    double *bmu=malloc(N_conf.n_in*sizeof(double));
    data=get_rand_data(position);
    Bmu=malloc(sizeof(t_bmu));
   
   

    
   
    
    //la 1ere distance 
    double dis=euc_distance(Net.map[0][0].w,data,N_conf.n_in);
    int x1,x2;
     //une liste dans le cas ou il y a plusieurs BMU et en prendre un aléatoirement 
    ListeBMU *l = malloc(sizeof(*l));
    l=initialisation(0,0);
    
    for(i=0;i<N_conf.n_l_out;i++)
    {
        for(j=0;j<N_conf.n_c_out;j++)
            {
                Net.map[i][j].dis=euc_distance(Net.map[i][j].w,data,N_conf.n_in);
                
                if(dis<=Net.map[i][j].dis)
                {
                dis=Net.map[i][j].dis;
                bmu=Net.map[i][j].w;
                x1=i;
                x2=j;
                //on ajoute le bmu a la liste des BMU si la  distance est similaire 
                addBmu(l,x1,x2);
                }
            }
       
    }
    
    //on prend un BMU aléatoire de la liste des BMU si il en a plusieurs 
    int r = rand() % l->nombre-1;
    positionBMU *al = l->suivant;
    for (int i=0;i<r;i++)
    {
    al = al->suivant;
    }
    strcpy(Net.map[al->x][al->y].etiq, array_vec[index_array[position]].name);
    //printf("%s ",Net.map[al->x][al->y].etiq);
    positionXY[0]=al->x;
    positionXY[1]=al->y;
    
    X1=positionXY[0];
    Y1=positionXY[1];
    
    
    
    return positionXY;
}



/*
On fait bouger le BMU pour le rapprocher le plus du vecteur donnée auquel il correspond
 en appliquant la formule suivante 

Wj(n+1) = Wj(n) + delta.Wj

Avec delta.Wj = ita.Yj.X - g(Yj).Wj
  
*/
void move_bmu(int a ,int b)
{
    double *data=malloc(N_conf.n_in*sizeof(double));
    double *delta=malloc(N_conf.n_in*sizeof(double));
    
    
    
    //on recupére le alpha et le rayon de voisinage qui seront mis a jours apres l'itertion
    double alpha=Net.alpha;
    double rayon=Net.nhd_r;
    //on calcule le taux de voisinage 
    double h=h_voisinage();
    //on recupére le vecteur données qui est en cours de traitement 
    data=get_rand_data(position);
  
   int j; 
    
    for(j=0;j<N_conf.n_in;j++)
            {
     Net.map[a][b].w[j]=Net.map[a][b].w[j]+alpha*h*(data[j]-Net.map[a][b].w[j]);
            }
            
    position=position+1;
    if (position>=149){
    position=0;
    }
            
            
   
}


/*
Calculer le taux de voisinage. 
*/
double h_voisinage()
{

/*
On va trouver le voisinage correspondant
*/ 
   
   //si on est dans l'une des extrémités le voisinage est 3
   if((X1==0 || Y1==0)&&(X1==N_conf.n_l_out || Y1==N_conf.n_c_out)){
   Net.nhd_r=2;
   
   }else{
   //si on est dans l'une des bordures mais pas l'extrémité
     if((X1==0 || Y1==0)){
        Net.nhd_r=3;
   
       }
       //sinon on est au centre de la map le voisinage reste 4
   
   }
   
    return exp(-(Net.map[X1][Y1].dis)/2*(SQR(Net.nhd_r)));
}







/*
On fait bouger le BMU et son voisinage en appliquant la formule suivante 

Wj(n+1) = Wj(n) + delta.Wj

Avec delta.Wj = ita.Yj.X - g(Yj).Wj
  
*/

void move_map()
{
  int *b=malloc(N_conf.n_in*sizeof(int));
    
    for(int i=0;i<N_conf.nb_it;i++){
    
    b=find_BMU();
    move_bmu(b[0],b[1]);
    
    }
}







int main()
{
    printf("Début de %s\n", __FILE__);
    

    init_n_conf();

     allouer_struct(150);

	  read_data();
    printf("    la matrice des données brutes\n" );
    print_Data();
    normalise_vec(150);
    printf("    la matrice des données normalisées\n " );
    print_Data();
    shuffle_table(150);
    //les vecteur min et max centré autour de la moyenne 
    average_vec(150);
    min_vec(0.005);
    max_vec(0.005);
    Net.alpha=N_conf.minAlpha;
    Net.nhd_r=floor((N_conf.n_l_out*N_conf.n_c_out)/2);
    
   
    
    
    
    create_map();
    printf(" \n" );
	printf("         The initial lattice \n" );
    print_map();
     for(int i=0;i<N_conf.nb_it;i++){
    
    move_map();
    
    }
    
    move_map();
    printf(" \n" );
    print_map();
    
    
	return 0;
}


/*
 Print la matrice
 */
void print_Data()
{
    int i,j;
    for(i=0;i<=149;i++)
    {
        
        for(j=0;j<4;j++)
            {
                printf(" %f ",array_vec[i].arr[j] );
                
            }
        
        printf(" \n" );
    }
}


/**
création de notre carte
**/
void create_map()
{
    int i,j;
    Net.map=malloc(N_conf.n_l_out*sizeof(t_node *));
	for(i=0;i<N_conf.n_l_out;i++)
	{
		Net.map[i]=malloc(N_conf.n_c_out*sizeof(t_node));
	}
	for(i=0;i<N_conf.n_l_out;i++)
	{
		for (j=0;j<N_conf.n_c_out;j++)
		{

            Net.map[i][j].w=(double*)malloc(sizeof(double)*N_conf.n_in);
			Net.map[i][j].w=init_rand_nodes();
			Net.map[i][j].etiq=malloc(20*sizeof(char));
			strcpy(Net.map[i][j].etiq, ".");
		}
	}
}

/*
Fonction pour afficher la map avant et apres le traitement
*/
void print_map()
{
    int i,j;
    for(i=0;i<N_conf.n_l_out;i++)
    {
        for(j=0;j<N_conf.n_c_out;j++)
            {
                printf("%s ",Net.map[i][j].etiq);
            }
        printf("\n");
    }
}
