#include "fonctions_vec.h"

/*
Fonction pour allouer
*/

void allouer_struct(int n)
{
    array_vec=malloc(n*sizeof(struct vec));
    int i;
    for(i=0;i<n;i++)
    {
        array_vec[i].arr=malloc(N_conf.n_in*sizeof(double));
        array_vec[i].name=malloc(20*sizeof(char));
        array_vec[i].poidSynaptiques=malloc(N_conf.n_in*sizeof(double));
        
    }
}




//vecteur moyen
void average_vec(int n)
{
    aver=malloc(N_conf.n_out*sizeof(double));
    //on init a l espace mémoire alloué a aver a 0 
    memset(aver,0,N_conf.n_out*sizeof(double));

    int i,j;

    for(i=0;i<N_conf.n_out;i++)
    {
        for(j=0;j<n;j++)
            aver[i]+=array_vec[j].arr[i];
        aver[i]/=n;
    }
}
//vecteur min
void min_vec(double k)
{
    min=malloc(N_conf.n_out*sizeof(double));
    int i;
    for(i=0;i<N_conf.n_out;i++)
        min[i]=aver[i]-k;
}

//vecteur max
void max_vec(double k)
{
    max=malloc(N_conf.n_out*sizeof(double));
    int i;
    for(i=0;i<N_conf.n_out;i++)
        max[i]=aver[i]+k;
}


/*
 Fonction pour garder la norme de chaque vecteur
 */
void la_norm_vec(int i,int size)
{
    double sum=0.;
    int j;
    for(j=0;j<size;j++)
        sum+=SQR(array_vec[i].arr[j]);
    array_vec[i].norm=sqrt(sum);
}


/*
Fonction pour normaliser un vecteur
*/
void normalise_vec(int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<N_conf.n_in;j++)
            array_vec[i].arr[j]/=array_vec[i].norm;
    }
}


/*
le shuffle table pour accé par faux pointeur
*/
void shuffle_table(int n)
{
    index_array=malloc(sizeof(int)*n);
    int i;
    for(i=0;i<n;i++)
        index_array[i]=i;
    
    int r_and,k;
    srand(time(NULL));
    for(i=0;i<n;i++)
        {
            r_and=rand()%n;
            k=index_array[i];
            index_array[i]=index_array[r_and];
            index_array[r_and]=k;
        }
}


/**
On ininitialise les valeurs des nodes de la map 
**/

double* init_rand_nodes()
{
    int i;
    double k=(double)rand()/RAND_MAX;
    double *tmp_w=malloc(N_conf.n_in*sizeof(double));

    for(i=0;i<N_conf.n_in;i++)
        {
            tmp_w[i]=k*(max[i]-min[i])+min[i];
        }

    double norm=0.;

    for(i=0;i<N_conf.n_in;i++)
    {
        norm+=SQR(tmp_w[i]);
    }

    for(i=0;i<N_conf.n_in;i++)
    {
            tmp_w[i]/=norm;
    }
    return tmp_w;
}


/*
prendre un vecteur des donnéees de façon aléatoire a l'aide du le shuffle table   
*/
double* get_rand_data(int pos)
{
  double *random_data=malloc(N_conf.n_in*sizeof(double));
  int j;
   for(j=0;j<4;j++)
    {
        random_data[j]=array_vec[index_array[pos]].arr[j];
    }
   return random_data;
}








/*
On init les poids synaptique de facon aléatoire 
et on normalise cest poids afin de ne pas obtenir des valeurs >=1
*/
void init_poids_synaptiques()
{
    int i,j;
    double k=(double)rand()/RAND_MAX;
    poids=malloc(N_conf.n_out*sizeof(double));
    
    for(j=0;j<150;j++)
 {
    
    
    
    for(i=0;i< N_conf.n_out;i++)
        {
            poids[i]=k*(max[i]-min[i])+min[i];
            
        }
    double norm=0.;

    for(i=0;i<N_conf.n_out;i++)
    {
        norm+=SQR(poids[i]);
       
    }

    for(i=0;i<N_conf.n_out;i++)
    {
        poids[i]/=norm;
        array_vec[j].arr[i]=poids[i];
        
    }
    
}
}


/**
Fonction pour calculer la distance euclidienne
*/
double euc_distance(double *a1, double *a2, int n)
{
	double sum=0.0;
	int i;
	for(i=0;i<n;i++)
	{
		sum+=(SQR(a1[i] - a2[i]));
	}
	return sqrt(sum);
}










/**
Fonction pour calculer le α a chaque fois
(pas sur que ca soit exactement ca a revoir)
**/

void calc_alpha(int it_n, int tot_it)
{
	Net.alpha = N_conf.minAlpha * (1 - ((double)it_n/(double)tot_it));
}

/*
Mettre à jour les paramètres d’apprentissage
*/

void update_parametres(int t)
{
  Net.alpha = Net.alpha*(t/500*N_conf.n_l_out*N_conf.n_c_out);
  Net.nhd_r=Net.nhd_r-floor((t/50*N_conf.n_l_out*N_conf.n_c_out));
  
}


//init liste des BMU
ListeBMU *initialisation(int x,int y)
{
    ListeBMU *liste = malloc(sizeof(*liste));
    positionBMU *p = malloc(sizeof(*p));

    if (liste == NULL || p == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    
    p->x = x;
    p->y = y;
    p->suivant = NULL;
    liste->nombre = 1;
    liste->suivant = p;

    return liste;
}


//add BMU to liste
void addBmu(ListeBMU *liste,int x,int y)
{
    /* Création du nouvel élément */
    positionBMU *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    
    
    nouveau->x = x;
    nouveau->y = y;
    /* Insertion du BMU au début de la liste */
    nouveau->suivant = liste->suivant;
    liste->nombre = liste->nombre +1;
    liste->suivant = nouveau;
}





