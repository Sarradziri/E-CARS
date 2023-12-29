#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct voiture {
    char matricule[20];
    char modele[50];
    char couleur[20];
    char status [50];  //  disponible ou louee
    char etat[50]; // en bonne etat ou en panne
};
struct location {
    struct voiture *vo;
    char nomlocataire[50];
    char numlocataire[9];// numero du locataire
    char datedebut[11];// date de la location
    int dateretour;// date de retour d'une voiture
};



/*****les fonctions*****/
int recherch_indice(struct voiture tabvoitures[],int *nbvoitures,const char *mat){
    for( int i=0;i<*nbvoitures;i++){
        if (strcmp(tabvoitures[i].matricule,mat)==1){
            return(i);
        }else{
        return(-1);
        }
    }
}

void louer(struct voiture tabvoitures[],struct location tablocations[],int *nbvoitures,int *nblocations) {
    bool test=false;
    printf("donner la matricule de la voiture à louer : ");
    char *mat;
    int ind;
    scanf("%s",mat);
    ind=recherch_indice(tabvoitures,nbvoitures,mat);
    if (ind >= 0 && ind < *nbvoitures){
         if ( strcmp(tabvoitures[ind].status,"disponible")==1 && strcmp(tabvoitures[ind].etat,"en bonne etat")==1){
            test=true;
        }else{
        printf("cette voiture ne peux pas etre louee\n");
        }

    }
    if (test==true){
        struct location nouvelle_location;

        nouvelle_location.vo = &tabvoitures[ind];

        printf("Donnez le nom du locataire : ");
        scanf("%s",nouvelle_location.nomlocataire);

        printf("Donnez le numero du locataire : ");
        scanf("%s",nouvelle_location.numlocataire);

        printf("donnez la date  de retour sous la forme jj/mm/aaaa: ");
        scanf("%d", &nouvelle_location.dateretour);

        strcpy(tabvoitures[ind].status,"louèe");
        printf("Donnez le date de la location sous la forme jj/mm/aaaa: ");
        scanf("%s",nouvelle_location.datedebut);
        tablocations[*nblocations]=nouvelle_location;

        (*nblocations)++;
        printf("la location de voiture est enregistree\n");
    }
};
void description(const char *mat,struct voiture tabvoitures[],int *nbvoitures){
    int ind;
    ind=recherch_indice(tabvoitures,nbvoitures,mat);

    if( ind>=0){
            printf("la matricule:%s\n",tabvoitures[ind].matricule);
            printf("la couleur:%s\n",tabvoitures[ind].couleur);
            printf("le modèle:%s\n",tabvoitures[ind].modele);
            printf("l'état:%s\n",tabvoitures[ind].etat);
            printf("la disponibilité:%s\n",tabvoitures[ind].status);
    }else{
        printf("la voiture n'existe pas");
    }
}

void supp(const char *mat,struct voiture tabvoitures[],int *nbvoitures){
    int ind=recherch_indice(tabvoitures,nbvoitures,mat);
    struct voiture aux;
    if (ind>-1 && ind<*nbvoitures){
        for(int i=ind;i<*nbvoitures-1;i++){
            tabvoitures[i]=tabvoitures[i+1];
        }
    }else{
            printf("voiture n'existe pas\n");
    }
}
void modification(struct voiture *voiture){
    printf("saisir le nombre correspondant au changement=1:matricule,2:couleur,3:modele,4:etat(en panne ou non),5:diponibilite");
    int d;
    scanf("%d",&d);
    switch(d){
    case 1:
        {
            printf("donnez la nouvelle matricule");
            scanf("%s",voiture->matricule);
        }
    case 2:
        {
            printf("donnez le nouveau couleur");
            scanf("%s",voiture->couleur);

        }
    case 3:
        {
            printf("donnez le modele");
            scanf("%s",voiture->modele);
        }

    case 4:
        {
            printf("saisez (en panne) ou(en bonne etat)");
            scanf("%s",voiture->etat);
        }
    case 5:
        {
            printf("saisez louee ou disponible ");
            scanf("%s",voiture->status);
        }

    }
}
void afficher_historique(struct location tablocations[],int *nblocations){
    for( int i=0;i<*nblocations;i++){
        printf("la location de voiture de matricule %s de %s a  %s\n",tablocations[i].vo->matricule,
               tablocations[i].datedebut,tablocations[i].dateretour);
        printf("le locataire: %s, son numero:%s\n",tablocations[i].nomlocataire,tablocations[i].numlocataire);
    }
}
void retourvoiture(struct location tablocations[],char *mat,int *nblocations,char *datedebut){
    for(int i=0;i<*nblocations;i++){
        if( strcmp(tablocations[i].datedebut,datedebut)==1 && strcmp(tablocations[i].vo->matricule,mat)==1){
           tablocations[i].dateretour=
           strcpy(tablocations[i].vo->status,"disponible");
           int r;
           do{
                printf("si la voiture a tomber en panne,saisez 1,sinon 0");
                ;
                scanf("%d",r);
                if(r==1){
                    strcpy(tablocations[i].vo->etat,"en panne");
                }
           }while(r!=0 && r!=1);

           break;
        }
    }
}
void ajoutvoiture(struct voiture tabvoitures[],int *nbvoitures){
    struct voiture nv;
    printf("donner la matricule");
    scanf("%s",nv.matricule);

    printf("donner le couleur");
    scanf("%s",nv.couleur);

    printf("donner le modele");
    scanf("%s",nv.modele);

    strcpy(nv.etat,"en bonne etat");
    strcpy(nv.status,"disponible");
    tabvoitures[*nbvoitures]=nv;
    (*nbvoitures)++;
}

int main(){

    struct voiture tablevoitures[100];
    struct location tablelocations[200];
    int nbvo= 0;
    int nbloc = 0;

    int a;
    do
    {
        printf("1: louer une voiture\n");
        printf("2: Afficher la description d'une voiture\n");
        printf("3: retourner une voiture et declarer une reclamation\n");
        printf("4: Supprimer une voiture en panne\n");
        printf("5: Modifier la description d'une voiture\n");
        printf("6: Afficher l'historique des locations\n");
        printf("7: Ajouter une voiture\n");
        printf("saisissez le numero correspondant:");
        scanf("%d", &a);
    }while(a<1 && a>7);
    switch (a){
        case 1:
            {
                if (nbvo>0){
                    louer(tablevoitures,tablelocations,nbvo,nbloc);
                    break;
                }
            }
        case 2:
            {
                char matr[20];
                printf("donner la matricule de voiture");
                scanf("%s",matr);
                description(matr,tablevoitures,nbvo);
                break;
            }
        case 3:
            {
               char matr[20];
               char date[11];
               printf("donner la date de la location sous la forme jj/mm/aaaa");
               scanf("%s",date);
               printf("donner la matricule de voiture");
               scanf("%s",matr);
               retourvoiture(tablelocations,matr,nbloc,date);
               break;
            }
        case 4:
            {
                if( nbvo>0){
                    char matr[20];
                    printf("donner la matricule de voiture");
                    scanf("%s",matr);
                    supp(matr,tablevoitures,nbvo);
                    break;
                }
            }
        case 5:
            {
               if( nbvo>0){
                    char matr[20];
                    printf("donner la matricule de voiture");
                    scanf("%s",matr);
                     description(matr,tablevoitures,nbvo) ;
                     break;
                }
            }
        case 6:
            {
                if (nbloc>0){
                    afficher_historique(tablelocations,nbloc);
                    break;
                }
            }
        case 7:
            {
                ajoutvoiture(tablevoitures,nbvo);
                break;
            }
    }





    return 0;
}
