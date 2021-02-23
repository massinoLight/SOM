#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
La structure pour garder les coordonnées du bmu et les ajouter a une liste 
*/
typedef struct position position;
struct position {
        
	
	int x;
	int y;
	position *suivant;
};


typedef struct ListeBMU ListeBMU;
struct ListeBMU
{
    int nombre;
    position *suivant;
};


//init liste des BMU
ListeBMU *initialisation(int x,int y)
{
    ListeBMU *liste = malloc(sizeof(*liste));
    position *p = malloc(sizeof(*p));

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
    position *nouveau = malloc(sizeof(*nouveau));
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

int main()
{
       //on prend un BMU aléatoire de la liste des BMU 
    int r = rand()%10;
    int q =rand()%10;
    ListeBMU *l = malloc(sizeof(*l));
    l=initialisation(r,q);
    
    int t = rand()%10;
    int u =rand()%10;
    addBmu(l,t,u);
    
    
    t = rand()%10;
    u =rand()%10;
    addBmu(l,t,u);
    
    
    t = rand()%10;
    u =rand()%10;
    addBmu(l,t,u);
    
     position *actuel = l->suivant;

    while (actuel != NULL)
    {
        printf("%d %d-> ", actuel->x,actuel->y);
        actuel = actuel->suivant;
    }
    printf(" \n");
    int ra = rand()%l->nombre;
    position *al = l->suivant;
    for (int i=0;i<ra;i++)
    {
    al = al->suivant;
    }
    printf("%d -> \n", al->x);
    printf("%d -> ", al->y);
    
         
	return 0;
}






