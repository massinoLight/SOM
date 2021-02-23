#include "init.h"

/*on initialise les valeurs
 comme suite (elles peuvent étre initialisé autrement
 j'ai mis α a 0.7
 et le nombre d'iterations a 3000
*/
void init_n_conf()
{
    N_conf.n_l_out=10;
    N_conf.n_c_out=10;
    N_conf.n_out=N_conf.n_l_out*N_conf.n_c_out;
    N_conf.n_in=4;
    N_conf.nb_it=1000;
    N_conf.minAlpha=0.7;
}



/*
Fonction pour lire le fichier iris.data
 avec utilisation de strtok
*/
void read_data()
{
    FILE * fichier;

    char *str=malloc(sizeof(char)*500);
    fichier=fopen("iris.data","r");

    int i,j;
 for(i=0;i<150;i++)
 {
        fscanf(fichier,"%s",str);
        char *tok=strtok(str,",");

        for(j=0;j<N_conf.n_in;j++)
            {
            //atof pour passer d'une chaine de caractére a un double
                array_vec[i].arr[j]=atof(tok);
                tok=strtok(NULL,",");
            }

        if (strcmp(tok, "Iris-setosa") == 0)
     strcpy(array_vec[i].name,"A");
        else if(strcmp(tok,"Iris-versicolor")==0)
            strcpy(array_vec[i].name,"B");
        else
            strcpy(array_vec[i].name,"C");

         la_norm_vec(i,4);
 }

 fclose(fichier);
    free(str);
}





