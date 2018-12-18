
//..................................................................................
//...Ecrire un applicatif de gestion des élèves d'une école primaire en langage C...
//..................................................................................

/*Réalisé en décembre 2018 par Pauline CANNILLO
                               Sonia CHARGE
                               Loïc FERRANDEZ
                               Arnaud TARDIF*/


#include <stdio.h>
#include <string.h> // Cette directive permet d'utiliser les opérations sur les chaînes de caractères
#include <ctype.h> // L'utilisation des fonctions tolower et toupper nécessite l'import de cette bibliothèque

#define ELEVE_MAX  25 // On définit une constante pour le nombre maximum d'élèves dans une classe
#define CLASSE_MAX 10 // On définit une constante pour le nombre maximum de classes dans l'école

int AnneeActuel;    // Variable global ( VISIBLE et UTILISABLE PARTOUT !!)
                    // ATTENTION : la variable et modifiable donc pas de bétise :D

// Définition des différentes structures de données
typedef struct Date
{
	int 	jour;
	int 	mois;
	int 	an;
}Date_t;

typedef struct Eleve
{
	char 	nom[50];
	char 	prenom[25];
	double 	moyenne;
	struct 	Date DateNaissance;
}Eleve_t;

typedef struct Classe
{
	char 	        nom[5];
	int             numeroClasse;
	int 	        nbrEleve;
	char 	        nomInstit[50];
	struct Eleve    TabEleve[ELEVE_MAX];

}Classe_t;

typedef struct ClassePool
{
 	char 	        nom[5];
	int             numeroClasse;
	int 	        nbrEleve;
	char 	        nomInstit[50];
	struct Eleve    TabEleve[256];

}Classe_tPool;

typedef struct Ecole
{
	char 	        nom[50];
	int 	        nbrClasse;
	struct Classe   TabClasse[CLASSE_MAX];
}Ecole_t;


// Définition des fonctions
// ------------------------------Fonctions Date------------------------------


// ...Fait par le groupe
// Fonction pour afficher une date sous le format JJ/MM/AAAA

void AfficherDate(Date_t D,char Affich[50])
{
   printf("%s %d/%d/%d\n",Affich,D.jour,D.mois,D.an);// D est une structure donc . (point) pour accèder au champ
}

//...Fait par Loïc
// Fonction pour empêcher l'utilisateur d'entrer des dates aberrantes

int verifieDate(int*jour,int*mois,int*annee)
{
    int jourMax=0;
    int bissextile;
    int boucle=0;

    do
    {
        if (boucle>0)
            return 0;
        bissextile=((*annee%400==0 || *annee%100!=0) && *annee%4==0);
        if(*mois>0 || *mois<13)
        {
            if(*mois==2 && bissextile==1)
                jourMax=29;
            else if (*mois==2 && bissextile==0)
                jourMax=28;
            else if (*mois==1 || *mois==3 || *mois==5 || *mois==7 || *mois==8 || *mois==10 ||
                     *mois==12)
                jourMax=31;
            else
                jourMax=30;
        }
        boucle ++;
    }while ((*jour>jourMax || *jour<1) || (*mois>12 || *mois<1) || (*annee>AnneeActuel-5 || *annee<AnneeActuel-11));
    return 1;
}

// ...Fait par Arnaud et Loïc
// Fonction pour saisir une date mais avec un affichage variable passé en paramètre
// Exemple : SaisirDate(Date_t *var, char Affich)

void SaisirDate(Date_t *var, char Affich[50])
{
    int dateOK;

    do
    {
        printf("Veuillez saisir la date %s au format jj/mm/aaaa : ",Affich);
        scanf("%d/%d/%d",&var->jour ,&var->mois, &var->an);
        dateOK=verifieDate(&var->jour,&var->mois,&var->an);
    }while (dateOK==0);
}


// ------------------------------Fonctions Eleve------------------------------


// ...Fait par Pauline
// Fonction pour afficher les informations concernant un élève au hasard

void AfficherEleve(Eleve_t E)
{
	printf("Eleve : %s %s Moyenne : %.2lf ",E.nom,E.prenom,E.moyenne);
    AfficherDate(E.DateNaissance,"Date de naissance :");
}

// ...Fait par Sonia
// Fonction pour saisir les informations concernant un élève au hasard

void SaisirEleve(Eleve_t *Eleve)
{
	printf("\nVeuillez saisir le nom et le prénom de l'eleve : ");
	scanf("%s %s",Eleve->nom,Eleve->prenom);
	getchar();
	SaisirDate(&Eleve->DateNaissance,"de naissance");
	Eleve->moyenne=0.0;
}

// ...Fait par Sonia
// Fonction pour afficher les informations d'un ensemble d'élèves

void AfficherTabEleve(const Eleve_t *tab, int taille)
{
	int i;//compteur de boucle
	
    for(i=0 ; i<taille ; i++)
        AfficherEleve(tab[i]);
}

// ...Fait par Pauline
// Fonction pour saisir les informations de plusieurs élèves

void SaisirTabEleve(Eleve_t *tab, int *nbrEleve, int tailleMax)
{
	int i;

	for(i=0;i<(*nbrEleve);i++)
        SaisirEleve(&tab[i]);
}


// ------------------------------Fonctions Classe------------------------------


// ...Fait par Loïc
// Fonction pour afficher les informations concernant une classe au hasard

void AfficherClasse(Classe_t C)
{
    printf("\nNom de la classe: %s_%d\nNom de l'institut.eur.rice : %s\nNombre d'eleve dans la classe : %d\n\n",C.nom,C.numeroClasse,C.nomInstit,C.nbrEleve);
    AfficherTabEleve(C.TabEleve, C.nbrEleve);
}

// ...Fait par Arnaud et Loïc
// Fonction pour saisir les informations d'une classe au hasard

void SaisirClasse(Classe_t *classe, Ecole_t *ecole)
{
		int test=0,drapeau=0,i=0;
		char majuscule[5];

		do {
    		printf("\nEntrez le nom de la classe et son quantième : ");
    		scanf("%s %d",classe->nom,&classe->numeroClasse);
    		getchar();

            for(i=0;i<strlen(classe->nom)+1;i++)
                    majuscule[i]=toupper(classe->nom[i]);//conversion du nom de la classe en majuscules
            strcpy(classe->nom,majuscule);//on force le nom à être en majuscules
            test=strcmp(majuscule,"CP");
            if (test==0)
                drapeau=1;
            test=strcmp(majuscule,"CE1");
            if (test==0)
                drapeau=1;
            test=strcmp(majuscule,"CE2");
            if (test==0)
                drapeau=1;
            test=strcmp(majuscule,"CM1");
            if (test==0)
                drapeau=1;
            test=strcmp(majuscule,"CM2");
            if (test==0)
                drapeau=1;
            if (drapeau==0)
                printf("Ce nom de classe n'est pas valide");
	     } while(drapeau==0);
    printf("\nEntrez le nom de l'Institut.eur.rice : ");
    scanf("%s",classe->nomInstit);
    classe->nbrEleve=0;
}

// ...Fait par Loïc
// Fonction pour afficher les informations d'un ensemble de classes

void AfficherTabClasse(const Classe_t *tab,int taille)
{
    int i;

    for(i=0 ; i<taille ; i++)
        AfficherClasse(tab[i]);
}

// ...Fait par le groupe
// Fonction pour saisir les informations pour plusieurs classes

void SaisirTabClasse(Classe_t *tab,int *nbrClasse,int tailleMax, Ecole_t *ecole)
{
    int i,j=0;

    do
    {
        if (j==0)
        {
            printf("\nCombien de classes voulez-vous dans votre ecole ? : ");
            scanf("%d",nbrClasse);
            j=1;
        }
        else
        {
            printf("\nDésolé, il faut minimum 1 classe et maximum %d classes\n",tailleMax);
            printf("Combien de classes voulez-vous dans votre ecole ? : ");
            scanf("%d",nbrClasse);
            j=1;
        }
    }while ( ! (*nbrClasse>0 && *nbrClasse<tailleMax) );

    for(i=0 ; i<(*nbrClasse) ; i++)
        SaisirClasse(&tab[i], ecole);
}


// ------------------------------Fonctions Ecole------------------------------


//  ...Fait par Pauline
// Fonction pour afficher les informations d'une école

void AfficherEcole(const Ecole_t *Eco)
{
    printf("\nNom de l'Ecole :%s\nNombre de classes :%d\n",Eco->nom,Eco->nbrClasse);
    AfficherTabClasse(Eco->TabClasse,Eco->nbrClasse);
}

//  ...Fait par Sonia
// Fonction pour saisir les informations pour une école

void SaisirEcole(Ecole_t *ecole)
{
    printf("\nEntrez le nom de l'ecole et l'annee en cours : ");
    scanf("%s %d",ecole->nom,&AnneeActuel);
    getchar();
    SaisirTabClasse(ecole->TabClasse,&ecole->nbrClasse, CLASSE_MAX, ecole);
}


//------------------------------Fonctions Opérationnelles------------------------------


// ...Fait par Loïc
// Fonction pour rechercher un élève en particulier et savoir de quelle classe il appartient

int RechercherEleve(const Ecole_t *Eco, const char *nom, const char *prenom, int *retourNumeroEleve)
{
    int  NumClasse,NumEleve;                // Compteur
    char prenomEleve[25];   // Variable de substitution
    char nomEleve[50];      // Variable de substitution

    for(NumClasse=0 ; NumClasse<(Eco->nbrClasse) ;  NumClasse++)
    {
        for(NumEleve=0 ; NumEleve<(Eco->TabClasse[NumClasse].nbrEleve) ; NumEleve++)
        {
// A chaque tour de boucle, copie le nom de l'eleve "j" de chaque classe dans "nomEleve"
            strcpy(nomEleve, Eco->TabClasse[NumClasse].TabEleve[NumEleve].nom);
// A chaque tour de boucle, copie le prenom de l'eleve "j" de chaque classe dans "prenomEleve"
            strcpy(prenomEleve, Eco->TabClasse[NumClasse].TabEleve[NumEleve].prenom);
            if(strcmp(nomEleve, nom)==0 && strcmp(prenomEleve, prenom)==0)
            {
                *retourNumeroEleve=NumEleve;
                return NumClasse; // Retourne le numero de classe
            }
        }
    }
    *retourNumeroEleve=-1;
    return -1;
}

// Fait par Loïc
// Fonction pour chercher si la classe "x" est dans l'école

int RechercherClasse(Ecole_t *ecole,const char *nomClasse, int Quantieme)
{
    int i;
    char MajClasse[5];

    for(i=0 ;i<strlen(nomClasse)+1 ; i++)
// le "+1" me permet de copier jusqu'au caractere : '\0' => fin de chaine
        MajClasse[i]=toupper(nomClasse[i]);
// Met la classe saisie en majuscules
// Toutes les classes de l'école ont un nom en majuscules
    for(i=0 ; i<ecole->nbrClasse ; i++)
// boucle jusqu'au nombre de classes réel
    {
// On compare la classe saisie avec celles existantes sans oublier le numero de la classe dans le cas
// où il y a plusieurs fois la même classe (2 CP ou 3 CM1 ....)
        if(strcmp(MajClasse, ecole->TabClasse[i].nom)==0 && Quantieme==ecole->TabClasse[i].numeroClasse)
        {
            return i;   // Retourne i (la position de la classe) si la classe est dans l'école
        }
    }
    return -1;   // Retourne -1 si la classe demandée n'est pas dans l'école
}

//...Fait par Sonia
//Fonction pour modifier les informations de la classe

void ModifierCetClasse(Ecole_t *ecole)
{
    char   nouvNom[50],nouvnomInstit[50],nom[50], minuscule[5], classe[5];
    int    reponse,numeroClasse,NumClasse=0,nouvQ, i, Quantieme=0;

    printf("Entrez le nom et le quantieme de la classe que vous cherchez : ");
    scanf("%s %d", classe, &Quantieme);
    NumClasse=RechercherClasse(ecole, classe, Quantieme);
    if(NumClasse != -1)
    {
        do
        {
            printf("Que voulez vous modifier ?\n \
                   1)-> Nom et quantième\n \
                   2)-> Nom de l'institut.eur.rice\n \
                   3)-> Toutes les informations\n \
                   0)-> Menu Précédent...");
            printf("\nEntrez votre choix : ");
            scanf("%d", &reponse);
            switch (reponse)
            {
                case 1 : printf("Etes vous sur d'avoir mesuré les consequences ? o/n : ");
                    scanf("%s", nouvNom);
                    getchar();
                    for(i=0;i<strlen(nouvNom)+1;i++)
                        minuscule[i]=tolower(nouvNom[i]);
                    if(strcmp(minuscule, "o")==0)
                    {
                        printf("Entrez le nouveau nom et quantieme de la classe : ");
                        scanf("%s %d",nouvNom,&nouvQ);
                        strcpy(ecole->TabClasse[NumClasse].nom, nouvNom);
                        ecole->TabClasse[NumClasse].numeroClasse = nouvQ;
                    }
                    break;
                case 2 : printf("Entrez le nouveau nom de l'institut.eur.rice :\n");
                    scanf("%s", nouvnomInstit);
                    strcpy(ecole->TabClasse[NumClasse].nomInstit, nouvnomInstit);
                    break;
                case 3 : printf("Etes vous sur d'avoir mesuré les consequences ? o/n : ");
                    scanf("%s", nouvNom);
                    getchar();
                    for(i=0;i<strlen(nouvNom)+1;i++)
                        minuscule[i]=tolower(nouvNom[i]);
                    if(strcmp(minuscule, "o")==0)
                    {
                        printf("Entrez le nouveau nom et quantieme de la classe : ");
                        scanf("%s %d",nouvNom,&nouvQ);
                        strcpy(ecole->TabClasse[NumClasse].nom, nouvNom);
                        ecole->TabClasse[NumClasse].numeroClasse = nouvQ;
                        printf("Entrez le nouveau nom de l'institut.eur.rice :\n");
                        scanf("%s", nouvnomInstit);
                        strcpy(ecole->TabClasse[NumClasse].nomInstit, nouvnomInstit);
                    }
                    break;
                case 0 :
                    break;
            }
        }while(reponse != 0);
    }
    else
        printf("Cette classe ne fait pas partie de l'établissement. Je vous invite à la creer	...");
}

// ...Fait par Groupe
// Fonction pour rechercher un élève en particulier et savoir de quelle classe il appartient

void RechercherEleveViaClasse(Ecole_t *Eco, const char *nom, const char *prenom, int *retourNumeroEleve)
{
    int  NumClasse,NumEleve;                // Compteur
    char prenomEleve[25];   // Variable de substitution
    char nomEleve[50];      // Variable de substitution
	int  result, resultat2, poubelle, Quantieme=0;
	char classe[5];

	printf("Entrez le nom et le quantieme de la classe que vous cherchez : ");
    scanf("%s %d", classe, &Quantieme);
	result=RechercherClasse(Eco, classe, Quantieme);    // Si on cherche CE1 1, result renvoie la position de CE1 1 dans l'ecole
	if(result == -1)
// Si la classe n'existe pas on fait les instruction ci dessous
	{
        printf("La classe existe pas");
        return;
    }
    resultat2=RechercherEleve(Eco, nom, prenom, &poubelle);
    if(poubelle == -1)
// Si l'élève n'existe pas on fait les instruction ci dessous
	{
        printf("L'eleve existe pas");
        return;
    }
    if(result == resultat2)
    {
        printf("l'eleve est bien dans la classe %s_%d", Eco->TabClasse[resultat2].nom,Eco->TabClasse[resultat2].numeroClasse);
        return;
    }
    else
        printf("L'eleve n'est pas en %s_%d, il est en %s_%d",Eco->TabClasse[result].nom, Eco->TabClasse[result].numeroClasse, Eco->TabClasse[resultat2].nom,Eco->TabClasse[resultat2].numeroClasse );
}


// Fait par Loïc
// Fonction qui permet de rajouter un classe dans l'école

void AjouterClasse (Ecole_t *ecole)
{
    int i=ecole->nbrClasse;

    if(ecole->nbrClasse<CLASSE_MAX)
    {
        SaisirClasse(&ecole->TabClasse[i], ecole);     // On saisie un classe a l'emplacement vide
        ecole->nbrClasse++;                                      // On oublie pas d'augmenter de 1 le nombre de classe réel
        return;                                                  // Fin de fonction
    }
    else
       printf("L'ecole a atteint le nombre maximum de classe possible\n");
}

// Fait par Loïc 13/12/18
// Transfere l'eleve dans l'ecole

void TransfereEleveEcole(Ecole_t *ecole, Eleve_t *Tabeleve, int nbrEleve, char NomClasse[5])
{
    int i, j=0, k=0;

    do
    {
        for(i=0 ; i<ecole->nbrClasse ; i++) // Parcours les classes de l'ecole
        {
            // Si le nom de la classe correspond a celui ou l'eleve doit aller et si "j" est inferieur au nombre d'eleve a transferer, je transfere
            if(strcmp(ecole->TabClasse[i].nom, NomClasse)==0 && j<nbrEleve)
            {
                strcpy(ecole->TabClasse[i].TabEleve[k].nom, Tabeleve[j].nom);
                strcpy(ecole->TabClasse[i].TabEleve[k].prenom , Tabeleve[j].prenom);
                ecole->TabClasse[i].TabEleve[k].moyenne = Tabeleve[j].moyenne;
                ecole->TabClasse[i].TabEleve[k].DateNaissance.jour = Tabeleve[j].DateNaissance.jour;
                ecole->TabClasse[i].TabEleve[k].DateNaissance.mois = Tabeleve[j].DateNaissance.mois;
                ecole->TabClasse[i].TabEleve[k].DateNaissance.an = Tabeleve[j].DateNaissance.an;
                ecole->TabClasse[i].nbrEleve++;
                j++;
            }
        }
        k++;
    }while(j<nbrEleve);
// Je sors de la boucle uniquement si "j" est egal au nombre d'eleve a transferer
}

// Fait par Loic 15/12/2018
// Transfere l'eleve entre le tableau "TabElevePool" et le tableau de classe (ec TabCP, TabCE1..)

void TransfereEleve(Eleve_t *eleveDest, Eleve_t *eleveOrig)
{
        strcpy(eleveDest->nom , eleveOrig->nom);
        strcpy(eleveDest->prenom , eleveOrig->prenom);
        eleveDest->moyenne = eleveOrig->moyenne;
        eleveDest->DateNaissance.jour = eleveOrig->DateNaissance.jour;
        eleveDest->DateNaissance.mois = eleveOrig->DateNaissance.mois;
        eleveDest->DateNaissance.an = eleveOrig->DateNaissance.an;
//  On remet l'origine à "zéro"...
        strcpy(eleveOrig->nom , "zz");
        strcpy(eleveOrig->prenom , "xx");
        eleveOrig->moyenne = 0;
        eleveOrig->DateNaissance.jour = 0;
        eleveOrig->DateNaissance.mois = 0;
        eleveOrig->DateNaissance.an = 0;
}

//...Fait par Loïc 16/12/18
// Fonction pour affecter un élève dans la classe correspondant à sa date de naissance

void AffecterClasse(Ecole_t *ecole, Eleve_t *TabClasse, int nbrEleve, char NomClasse[5])
{
//    const int annee=AnneeActuel;
    char reponse[2];
    int i=0,j=0, compteurClasse=0;//compteur de boucle
    int result, poubelle, nbrEleveReel=0;
    double NbrClasseBesoin=0.0;

    do
    {
        compteurClasse=0;
        for(i=0 ; i<ecole->nbrClasse ; i++) // Parcours les classe de l'ecole
            if(strcmp(ecole->TabClasse[i].nom, NomClasse) ==0)
// On regarde que la classe "i" a bien le nom de la classe voulu
                compteurClasse++; // On stock le nombre de classe du meme nom
            NbrClasseBesoin = nbrEleve / 25.0;
// On regarde combien de classe il nous faut pour acceuillir les eleves de la classe voulu
        if(NbrClasseBesoin>compteurClasse)
// Si le nombre de classe dont on a besoin et superieur au nombre de classe reel, on passe
        {
            if(compteurClasse == 0)
// si le nombre de classe reel et egale à 0 (classe existe pas), on passe
            {
                do
                {
                    printf("Il y a aucune classe %s dans l'ecole, Voulez-vous la créer ? o/n : ", NomClasse);
                    scanf("%s", reponse);
                }while( (strcmp(reponse ,"o")!=0 && strcmp(reponse,"O")!=0 ) &&  (strcmp(reponse ,"n")!=0 || strcmp(reponse,"N")!=0) );
                if(strcmp(reponse ,"o")==0 || strcmp(reponse,"O")==0)
// Si l'utilisateur repond oui, on crée un classe
                {
                    poubelle=getchar();
                    AjouterClasse(ecole);
                }
            }
            else
// si la classe existe mais qu'il y en a pas assez, on passe
            {
                do
                {
                    printf("\nIl y a trop d'eleves pour le nombre de classe. Voulez vous crée une classe %s ? o/n : ", NomClasse);
                    scanf("%s", reponse);
                }while( (strcmp(reponse ,"o")!=0 && strcmp(reponse,"O")!=0 ) &&  (strcmp(reponse ,"n")!=0 || strcmp(reponse,"N")!=0) );

                if(strcmp(reponse ,"o")==0 || strcmp(reponse,"O")==0)
// Si l'utilisateur repond oui, on crée un classe
                {
                    poubelle=getchar();
                    AjouterClasse(ecole);
                }
                if(strcmp(reponse ,"n")==0 || strcmp(reponse,"N")==0)
// Si il repond non, on lui demande de confirmer son choix
                {
                    do
                    {
                        printf("\nVous etes en train de refuser des eleves, etes vous sur ? o/n : ");
                        scanf("%s", reponse);
                    }while( (strcmp(reponse ,"o")!=0 && strcmp(reponse,"O")!=0 ) &&  (strcmp(reponse ,"n")!=0 || strcmp(reponse,"N")!=0) );
                    if(strcmp(reponse ,"o")==0 || strcmp(reponse,"O")==0)
                        break;
                    else
                    {
                        poubelle=getchar();
                        AjouterClasse(ecole);
                    }
                }
            }
        }
    }while(NbrClasseBesoin>compteurClasse);
// Tant que le besoin en classe n'est pas résolu on boucle
    TransfereEleveEcole(ecole, TabClasse, nbrEleve, NomClasse);
}


// Fait par Loïc 16/12/18
// Fonction pour répartir les élèves par classe (tri des élèves entre classes)
void CreaTabClasse (Eleve_t *TabPool, int nbrEleve, Ecole_t *ecole)
{
    int i, j=0, TabNbrEl[5]={0};     // TabNbrEl[0] =CP ; TabNbrEl[1]=CE1....
    Eleve_t TabCP[100], TabCE1[100], TabCE2[100] , TabCM1[100], TabCM2[100];


    for (i=0 ; i<nbrEleve ;i++)
    {
        printf("eleve : %s %s, annee naissance : %d\n", TabPool[i].nom, TabPool[i].prenom, TabPool[i].DateNaissance.an);
// Je transfere les eleves en age d'etre au CP dans le tableau CP
        if (TabPool[i].DateNaissance.an == AnneeActuel-6)
        {
            TransfereEleve(&TabCP[TabNbrEl[0]],&TabPool[i]);
// Je me sers du nombre d'eleve dans la classe pour copier l'eleve dans la case (nombre d'eleve)
            TabNbrEl[0]++;
// Nombre d'eleve dans la classe CP qui s'incrémente dès que je transfere un eleve
        }
// Je transfere les eleves en age d'etre au CE1 dans le tableau CE1
        else if (TabPool[i].DateNaissance.an == AnneeActuel-7)
        {
            TransfereEleve(&TabCE1[TabNbrEl[1]],&TabPool[i]);
            TabNbrEl[1]++;  // Nombre d'eleve dans la classe CE1
        }
// Je transfere les eleves en age d'etre au CE2 dans le tableau CE2
        else if (TabPool[i].DateNaissance.an == AnneeActuel-8)
        {
            TransfereEleve(&TabCE2[TabNbrEl[2]],&TabPool[i]);
            TabNbrEl[2]++;
// Nombre d'eleve dans la classe CE2
        }
// Je transfere les eleves en age d'etre au CM1 dans le tableau CM1
        else if(TabPool[i].DateNaissance.an == AnneeActuel-9)
        {
            TransfereEleve(&TabCM1[TabNbrEl[3]],&TabPool[i]);
            TabNbrEl[3]++;
// Nombre d'eleve dans la classe CM1
        }
// Je transfere les eleves en age d'etre au CM2 dans le tableau CM2
        else if(TabPool[i].DateNaissance.an == AnneeActuel-10)
        {
            TransfereEleve(&TabCM2[TabNbrEl[4]],&TabPool[i]);
            TabNbrEl[4]++;
// Nombre d'eleve dans la classe CM2
        }
    }
    if(TabNbrEl[0]>0)
        AffecterClasse(ecole, TabCP, TabNbrEl[0], "CP");
    if(TabNbrEl[1]>0)
        AffecterClasse(ecole, TabCE1, TabNbrEl[1], "CE1");
    if(TabNbrEl[2]>0)
        AffecterClasse(ecole, TabCE2, TabNbrEl[2], "CE2");
    if(TabNbrEl[3]>0)
        AffecterClasse(ecole, TabCM1 ,TabNbrEl[3], "CM1");
    if(TabNbrEl[4]>0)
        AffecterClasse(ecole, TabCM2, TabNbrEl[4], "CM2");
}


// ...Fait par Loïc et Arnaud
// Recréer un Pool avec les eleves de l'ecole dont la classe et la meme que celui de l'eleve a inscrire

void RemplirPool(Classe_tPool *PoolDest, Ecole_t *ecoleOrig, char classe[5])
{
    int i, j, k=0;
    PoolDest->nbrEleve=0;

    for(i=0 ; i<ecoleOrig->nbrClasse ; i++)
    {
        if(strcmp(ecoleOrig->TabClasse[i].nom, classe)==0)
        {
            for(j=0 ; j<ecoleOrig->TabClasse[i].nbrEleve ; j++)
            {
                TransfereEleve(&PoolDest->TabEleve[k], &ecoleOrig->TabClasse[i].TabEleve[j]);
                k++;
            }
            ecoleOrig->TabClasse[i].nbrEleve=0;
        }
    }
    PoolDest->nbrEleve=k;
}


//...Fait par Sonia et Loïc
// Inscrit l'eleve dans la bonne classe

void InscrireEleve(Ecole_t *Eco, Classe_tPool *PoolEleve)
{
    Eleve_t ElSolo[1];

    SaisirEleve(ElSolo);
// Dans quel classe va ElsOlo
    if(ElSolo->DateNaissance.an == AnneeActuel-6)
// On recupere tout les eleve de la meme classe d'age et on les met dans le pool
        RemplirPool(PoolEleve, Eco,"CP");
    else if(ElSolo->DateNaissance.an == AnneeActuel-7)
        RemplirPool(PoolEleve, Eco,"CE1");
    else if(ElSolo->DateNaissance.an == AnneeActuel-8)
        RemplirPool(PoolEleve, Eco,"CE2");
    else if(ElSolo->DateNaissance.an == AnneeActuel-9)
        RemplirPool(PoolEleve, Eco,"CM1");
    else if(ElSolo->DateNaissance.an == AnneeActuel-10)
        RemplirPool(PoolEleve, Eco,"CM2");
// On ajoute au bout du pool ElSolo
    TransfereEleve(&PoolEleve->TabEleve[PoolEleve->nbrEleve] , ElSolo);
    PoolEleve->nbrEleve++; // on augmente le nombre eleve du pool de 1
// On fait CreaTabClass avec le pool complet
    CreaTabClasse(PoolEleve->TabEleve, PoolEleve->nbrEleve, Eco);
}

// Fait par Loic 13/12/18
// Fonction pour saisir les informations de l'ensemble des élèves inscrits et les affecter à leur classe

void RentreeDesClasses(Ecole_t *ecole, Classe_tPool *PoolEleve)
{
    printf("Combien d'eleves font leur rentree : ");
    scanf("%d", &PoolEleve->nbrEleve);
    SaisirTabEleve(PoolEleve->TabEleve, &PoolEleve->nbrEleve, 256);
    CreaTabClasse(PoolEleve->TabEleve, PoolEleve->nbrEleve, ecole);
}


// ...Fait par Loïc
// Fonction pour modifier les informations d'un élève

void ModifierCetEleve(Ecole_t *ecole)
{
    double nouvMoy;
    char   nouvNom[50],nouvPrenom[50],nom[50],prenom[50];
    int    reponse,NumEleve=0,NumClasse=0;

    printf("Saisissez le nom et prenom de l'eleve a modifier :\n");
    scanf("%s %s",nom,prenom);
    NumClasse=RechercherEleve(ecole,nom,prenom,&NumEleve);
    if(NumClasse != -1)
    {
        do
        {
            printf("Que voulez vous modifier ?\n \
                   1)-> Nom et Prenom\n \
                   2)-> La moyenne generale\n \
                   3)-> La date de naissance\n \
                   4)-> Toutes les informations\n \
                   0)-> Menu Précédent...");
            printf("\nEntrez votre choix : ");
            scanf("%d", &reponse);
            switch (reponse)
            {
                case 1 : printf("Entrez le nouveau nom et prenom de l'eleve :\n");
                    scanf("%s %s",nouvNom, nouvPrenom);
                    strcpy(ecole->TabClasse[NumClasse].TabEleve[NumEleve].nom, nouvNom);
                    strcpy(ecole->TabClasse[NumClasse].TabEleve[NumEleve].prenom, nouvPrenom);
                    break;
                case 2 : printf("Entrez la nouvelle moyenne generale de l'eleve :\n");
                    scanf("%lf", &nouvMoy);
                    ecole->TabClasse[NumClasse].TabEleve[NumEleve].moyenne = nouvMoy;
                    break;
                case 3 : SaisirDate(&ecole->TabClasse[NumClasse].TabEleve[NumEleve].DateNaissance, "de naissance");
                    break;
                case 4 : SaisirEleve(&ecole->TabClasse[NumClasse].TabEleve[NumEleve]);
                    printf("Entrez la nouvelle moyenne generale de l'eleve :\n");
                    scanf("%lf", &nouvMoy);
                    ecole->TabClasse[NumClasse].TabEleve[NumEleve].moyenne = nouvMoy;
                    break;
                case 0 :
                    break;
            }
        }while(reponse != 0);
    }
    else
        printf("L'eleve ne fait pas partie de l'ecole. Je vous invite à l'inscrire...");
}

//...Fait par Arnaud
// Fonction pour afficher un élève en particulier

void AffichCetEleve(Ecole_t *Eco)
{
    char nom[50]; // Nom de l'élève à rechercher
    char prenom[25]; // Prénom de l'élève à rechercher
    int  i,j;
    int  NumClasse,NumEleve; // Compteurs

    printf("Entrez le nom et le prenom de l'eleve recherché : \n");
    scanf("%s %s", nom, prenom);
//  Reprise de la fonction de recherche de Loïc mais SANS affichage intégré...
    NumClasse=RechercherEleve(Eco,nom,prenom,&NumEleve);
    if (NumClasse!=-1)
    {
        printf("L'eleve %s %s est bien inscrit dans l'ecole.\n", nom, prenom);
        printf("Il est en %s_%d et ",Eco->TabClasse[NumClasse].nom,Eco->TabClasse[NumClasse].numeroClasse);
        printf("sa moyenne generale est : %.2lf ",Eco->TabClasse[NumClasse].TabEleve[NumEleve].moyenne);
//  On va afficher sa date de naissance
        AfficherDate(Eco->TabClasse[NumClasse].TabEleve[NumEleve].DateNaissance,"Date de naissance :");
    }
    else
        printf("\nL'eleve n'est pas présent dans l'école...\n");
}

//  ...Fait par Arnaud en reprenant du code à Loïc et du code d'exercices antérieurs
//  Fonction pour exclure un élève

void ExclureEleve(Ecole_t *Eco)
{
    char nom[50];
    char prenom[25];
    char vide[2]=" ";
    int  numClasse,numEleve, i, j;

    printf("Entrez le nom et le prenom de l'eleve recherché : \n");
    scanf("%s %s", nom, prenom);
    numClasse=RechercherEleve(Eco,nom,prenom,&numEleve);
    if (numClasse!=-1)
    {
        printf("L'eleve %s %s est bien inscrit dans l'ecole.\nIl est en %s_%d", nom, prenom, Eco->TabClasse[numClasse].nom, Eco->TabClasse[numClasse].numeroClasse);
        printf("\nOn va le détruire ! ;-)\n");
        for (i=numEleve; i<(Eco->TabClasse[numClasse].nbrEleve-1); i++)
        {
            strcpy(Eco->TabClasse[numClasse].TabEleve[i].nom, Eco->TabClasse[numClasse].TabEleve[i+1].nom);
            strcpy(Eco->TabClasse[numClasse].TabEleve[i].prenom, Eco->TabClasse[numClasse].TabEleve[i+1].prenom);
            Eco->TabClasse[numClasse].TabEleve[i].moyenne=Eco->TabClasse[numClasse].TabEleve[i+1].moyenne;
            Eco->TabClasse[numClasse].TabEleve[i].DateNaissance.jour=Eco->TabClasse[numClasse].TabEleve[i+1].DateNaissance.jour;
            Eco->TabClasse[numClasse].TabEleve[i].DateNaissance.mois=Eco->TabClasse[numClasse].TabEleve[i+1].DateNaissance.mois;
            Eco->TabClasse[numClasse].TabEleve[i].DateNaissance.an=Eco->TabClasse[numClasse].TabEleve[i+1].DateNaissance.an;
        }
        Eco->TabClasse[numClasse].nbrEleve--;
    }
    else
        printf("\nL'eleve n'est pas présent dans l'école...");
}


//Fait par Pauline
//Fonction pour afficher une classe en particulier

void AfficherUneClasse(Ecole_t *ecole)
{
	int retour, Quantieme=0;
	char classe[5];

    printf("Entrez le nom et le quantieme de la classe que vous cherchez : ");
    scanf("%s %d", classe, &Quantieme);
	retour = RechercherClasse(ecole, classe, Quantieme);

	if (retour !=-1)
		AfficherClasse(ecole->TabClasse[retour]);
    else
    	printf("Cette classe n'est pas dans l'ecole\n");
 }


// ...Fait par Arnaud
// Fonction pour afficher la classe recherchée

void AfficherEleveDeClasse(Ecole_t *ecole)
{
    int resultat, Quantieme=0;
    char classe[5];

    printf("Entrez le nom et le quantieme de la classe que vous cherchez : ");
    scanf("%s %d", classe, &Quantieme);
    resultat=RechercherClasse(ecole, classe, Quantieme);
    AfficherClasse(ecole->TabClasse[resultat]);
// permet d'afficher une seul et unique classe (celle demandée)
}


//...Fait par le groupe
//Fonction pour saisir la moyenne d'un élève

void SaisirMoyEleve(Ecole_t *ecole)
{
	int result,empeleve=0;
	char nom[50],prenom[25];
	double moy;

	printf("Entrez le nom et le prenom de l'eleve : ");
	scanf("%s %s",nom,prenom);

	result=RechercherEleve(ecole, nom, prenom, &empeleve);

	if(result!=-1)
		{
		printf("Entrez la moyenne de l'eleve : ");
		scanf("%lf",&moy);
		ecole->TabClasse[result].TabEleve[empeleve].moyenne=moy;
		}
}


// ...Fait par Pauline, Sonia et Arnaud
// Fonction pour saisir la moyenne des élèves de la classe

void SaisirMoyClasse(Ecole_t *ecole)
{
	int empclasse,i, Quantieme=0;
	double moy;
	char classe[5];

	printf("Entrez le nom et le quantieme de la classe que vous cherchez : ");
    scanf("%s %d", classe, &Quantieme);
	empclasse=RechercherClasse(ecole, classe, Quantieme);
	if(empclasse!=-1)
		{
		for(i=0;i<ecole->TabClasse[empclasse].nbrEleve;i++)
			{
			printf("Saisissez la moyenne de l'eleve : %s %s ",ecole->TabClasse[empclasse].TabEleve[i].nom,ecole->TabClasse[empclasse].TabEleve[i].prenom);
			printf("\nEntrez la moyenne de l'eleve : ");
			scanf("%lf",&moy);
			ecole->TabClasse[empclasse].TabEleve[i].moyenne=moy;
			}
		AfficherTabEleve(ecole->TabClasse[empclasse].TabEleve, ecole->TabClasse[empclasse].nbrEleve);
		}
}


// ------------------------------Fonctions Menu------------------------------


// ...Fait par Loïc, Sonia & Pauline
// Fonction pour proposer un menu de différents choix pour gérer l'école

void SousMenu1(Ecole_t *Ecole,int *flag, Classe_tPool *PoolEleve)
{
    int reponse=-1;

    do
    {
        printf("\n--Menu Gerer l'ecole--\n");
        printf("\nVos choix sont : \n");
        printf("\n\t1)-> Saisir les informations de l'ecole");
        printf("\n\t2)-> Afficher les informations de l'ecole");
        if (*flag!=2)
            {
                printf("\n\t3)-> Rentree des classes");
                printf("\n\t\tCe choix ne sera possible qu'une seule fois !");
            }
        printf("\n\t0)-> Menu Précédent...");
        printf("\nEntrez votre choix : ");
        scanf("%d", &reponse);
        switch (reponse)
        {
            case 1 : SaisirEcole(Ecole);
                *flag=1;
                break;
            case 2 : AfficherEcole(Ecole);
                break;
            case 3 : RentreeDesClasses(Ecole, PoolEleve);
                *flag=2;
                break;
            case 0 : printf("Menu Précédent...\n");
                break;
        }
    }while (reponse != 0);
}

// ...Fait par le groupe
// Fonction pour proposer un menu comprenant plusieurs choix pour gérer une classe

void SousMenu2(Ecole_t *ecole)
{
    int choix=-1, result;
    Classe_t Classe;

    do
    {
        printf("\n--Menu Gerer la classe--\n");
        printf("Vos choix sont : \n \
               1)-> Afficher une classe\n \
               2)-> Modifier une classe\n \
               3)-> Ajouter une classe\n \
               4)-> Donner la liste des eleves d'une classe\n \
               0)-> Menu Précédent...");
        printf("\nEntrez votre choix : ");
        scanf("%d",&choix);

        switch (choix)
        {
            case 1 : AfficherUneClasse(ecole);
                break;
            case 2 : ModifierCetClasse(ecole);
                break;
            case 3 : AjouterClasse(ecole);
                break;
            case 4 : AfficherEleveDeClasse(ecole);
                break;
            case 0 : printf("Menu Précédent...\n");
                break;
        }
    }while(choix != 0);
}


// ...Fait par Sonia & Pauline
// Fonction pour proposer un menu de choix pour gérer un élève

void SousMenu3(Ecole_t *ecoleTest, Classe_tPool *PoolEleve)
{
    int  choix=-1,NumEleve=0,result=0;
    char Nom[50],Prenom[50];

    do
    {
        printf("\n--Menu Gerer un eleve--\n");
        printf("Vos choix sont : \n \
               1)-> Rechercher un eleve via classe\n \
               2)-> Inscrire un eleve\n \
               3)-> Modifier les informations d'un eleve\n \
               4)-> Afficher un eleve\n \
               5)-> Exclure un eleve\n \
               0)-> Menu Précédent...");
        printf("\nEntrez votre choix : ");
        scanf("%d",&choix);
        switch (choix)
        {
            case 1 :
                printf("Saisissez le Nom et le Prenom de l'eleve recherché :");
                scanf("%s %s",Nom, Prenom);
                RechercherEleveViaClasse(ecoleTest,Nom,Prenom,&NumEleve);
                break;
            case 2 : InscrireEleve(ecoleTest, PoolEleve);
                break;
            case 3 : ModifierCetEleve(ecoleTest);
                break;
            case 4 : AffichCetEleve(ecoleTest);
                break;
            case 5 : ExclureEleve(ecoleTest);
                break;
            case 0 : printf("Menu Précédent...\n");
                break;
        }
    }while(choix!=0);
}


// ...Fait par Sonia & Pauline
// Fonction pour proposer un menu pour gérer la fin de l'année et le passage des élèves dans une classe supérieure

void SousMenu4(Ecole_t *ecole_Test)
{
    int choix=-1;

    do
    {
        printf("\n--Menu Gerer les moyennes--\n");
        printf("Vos choix sont : \n \
               1)-> Saisir la moyenne finale d'un eleve\n \
               2)-> Saisir la moyenne finale pour une classe d'eleves\n \
               0)-> Menu Précédent...");
        printf("\nEntrez votre choix : ");
        scanf("%d",&choix);

        switch (choix)
        {
            case 1 : SaisirMoyEleve(ecole_Test);
                break;
            case 2 : SaisirMoyClasse(ecole_Test);
                break;
            case 0 : printf("Menu Précédent...\n");
                break;
        }
    }while(choix != 0);
}


// ------------------------------Programme principal------------------------------


int main()
{
//Variables
    int  choix=-1;
    int  flag;
    Ecole_t  ecoleTest;
    Classe_tPool ElevePool;

// ...Fait par Arnaud
	printf("\n*---------------------------*");
	printf("\n| ...Bienvenue à l'Ecole... |");
	printf("\n*---------------------------*");
	flag=0;
	do
	{
		printf("\n*------------------------------------------------------*");
		printf("\n| Vos choix sont les suivants :                        |");
		printf("\n| 1) -> Choix gerer l'ecole                            |");
		if (flag==0)
			printf("\n| D'autres choix seront après création de l'école      |");
		if (flag!=0)
		{
				printf("\n| 2) -> Choix gerer une classe                         |");
				printf("\n| 3) -> Choix gerer un eleve                           |");
				printf("\n| 4) -> Choix gerer les moyennes                       |");
		}
		printf("\n| 0) -> Sortir !                                       |");
		printf("\n*------------------------------------------------------*");
		printf("\nVotre choix ?\t");
		scanf("%d",&choix);
		switch (choix)
			{
//            Gérer école
                case 1: SousMenu1(&ecoleTest,&flag, &ElevePool);
						break;
//            Gérer les classes
				case 2:
						if (flag!=0)
								SousMenu2(&ecoleTest);
						break;
//             Gérer les élèves
				case 3:
						if (flag!=0)
								SousMenu3(&ecoleTest, &ElevePool);
						break;
//              Gérer les Moyennes
				case 4:
						if (flag!=0)
								SousMenu4(&ecoleTest);
						break;
//              Gérer fin programme
				case 0:
						break;
				}
    }
    while (choix!=0);
}
