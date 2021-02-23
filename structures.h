
/*
 Structure de données pour notre configuration de base
 */
 struct N_config
 {
   int n_in; //variable pour la taille du vecteur
   int n_l_out; // nombre de neuron map sur ligne
   int n_c_out; // npmbre de neuron sur colone
   int n_out; //total neuron (n_l_out * n_c_out) taille de notre map
   int nb_it; // Nombre d'iterations qu'on calcule avec la methode donnée
   double minAlpha;//starting value le     0.6 < alpha < 0.9
   int train; //nombre d'opération lors de l'entrainement 
   int ftrain; //numero de l'operation dans la 1ere couche
 }N_conf;



/*
 Structure d'un node (neurone)
 */
struct node
{
  double dis; // dist euc.
  char *etiq; // A B OU C selon le type de fleur 
  double *w;//les poids synaptiques
  double *position;//vecteur  position du neurone qui va étre ajustable 
};

typedef struct node t_node;


/*
 le fameux Best-Matching Unit
 */
typedef struct bmu t_bmu;
struct bmu {
        
	double act; // euclidian distance
	int x;
	int y;
	t_bmu *suivant;
};


/*
La structure pour garder les coordonnées du bmu et les ajouter a une liste 
*/
typedef struct positionBMU positionBMU;
struct positionBMU {
        
	
	int x;
	int y;
	positionBMU *suivant;
};


typedef struct ListeBMU ListeBMU;
struct ListeBMU
{
    int nombre;
    positionBMU *suivant;
};

/*
 Structure de notre réseau de neurons
 */
struct net
{
  int nhd_r;  // nombre de voisinage (rayon) (neighbourhood)
  t_node **map;
  double *captors; // le vecteur courant
  double alpha; // le fameux coeif
  char *etiq;   // l'etiquette ici une lettre A,B ou C qui sera attribué au node au fur et a mesure 
} Net;

struct vec
	{
        double *arr;
        char *name;
        double norm;
        double *poidSynaptiques;
	};

struct vec * array_vec;
