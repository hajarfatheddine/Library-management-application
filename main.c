#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include<windows.h>  ///contient les declarations utilisees pour definir gotoxy
#include <time.h>

///declarartion des couleurs de maniere claire
#define BLUE 1
#define YELLOW 14
#define BLACK 0
#define WHITE 15
#define RED 4
#define GREEN 2
#define LIGHTCYAN 11
#define LIGHTGRAY 7

///variables globales du programme

char choix, choix1, confirme;
int i,j;
///i pour garder la position d'un element trouve (etudiant, ouvrage ou pret)
///j est utilise dans les boucles pour tracer un cadre pour les menus

int nombre_elements=0,nb_ch=0,num_pret=0;
///nombre_elements: nombre courant d'etudaints
///nb_ch : nombre courant d'ouvrages
///num_pret : nombre courant de prets

typedef struct {///definition d'un type structure pour un etudiant qui a fait un pret (emprunteur)
          int id;
          char nom[15];
          char prenom[15];
          char filiere[15];
          char tele[10];
          char annee[15];
                }etudiant;
etudiant c1[200]; ///tableau de structures de type etudiant


typedef struct {///definition d'un type structure pour un ouvrage emprunte
          int id;
          char titre[15];
          char annee[15];
          char auteur[15];
          char specialite[15];
              }ouvrage;
ouvrage c2[200]; ///tableau de structures de type ouvrage


typedef struct{///definition d'un type structure pour un pret fait
     int Numero_De_Pret;
     char jour1[20];
     char mois1[20];
     char ann1[20];
     char jour2[20];
     char mois2[29];
     char ann2[20];
     int duree;
 }pret;
pret c3[200]; ///tableau de structures de type pret

///La fonction main() appelle la fonction qui presente
///le menu principal et saisit le choix de l'utilisateur
///puis appelle la fonction qui realise le traitement choisi

COORD coord={0,0}; ///le centre des axes est mis au coin gauche haut de l'ecran
void gotoxy(int x,int y);
void SetColorAndBackground(int ForgC, int BackC);
///declarations pour pour pouvoir deplacer le curseur et changer les couleurs dans code blocks
///code source est fourni par le site: www.codeincodeblock.com

void menu_principal(void);
///cette fonction presente le menu principal et saisit le choix de l'utilisateur

void gestion_etudiant(void);

///cette fonction presnete le menu ge gestion des etudiants tel demande et saisit le choix
///de l'utilisateur (touches Fi) et appelle la fonction qui fait le traitement demande

void menu_gestion_etudiant(void);
///cette fonction affiche un cadre avec des caracteres speciaux tel demande
///et affiche les informations concernant un etudiant qui fait un pret

int chercher_etudiant(int x);
///retourne le numero d'etudiant s'il existe dans la table
///en plus determine sa position dans la varaible globale i
///cette variable i sera utilisé dans differentes fonctions
///pour acceder aux differents champs d'un etudiant
///on cherche un etudiant sachant son numero x

void nouveau_etudiant(void);
void consulter_etudiant(void);
void modifier_etudiant(void);
void supprimer_etudiant(void);
///ces fonctions realisent les traitements demandes
///et font les controles necessaires et en affiche les informations
///et quite (si escape) pour revenir au menu principal c.a.d main()

///les fonctions suivantes sont identiques a celles de gestion des etudiants
///mais concernent un ouvrage emprunté

void gestion_ouvrage(void);
void menu_gestion_ouvrage(void);
int chercher_ouvrage(int x);
void Nouveau_ouvrage(void);
void consulter_ouvrage(void);
void modifier_ouvrage(void);
void supprimer_ouvrage(void);

///les fonctions suivantes sont identiques a celles de gestion des etudiants
///mais concernent un pret fait
void gestion_pret(void);
void menu_gestion_pret(void);
int chercher_pret(int x);
void nouveau_pret(void);
void consulter_pret(void);
void modifier_pret(void);
void supprimer_pret(void);



void generation_etat(void);
///cette fonction affiche un menu tel demande, saisit le choix
///et appelle la fonction pret_encours() ou quitte le fonction


void pret_encours(void);
///cette fonction affiche un cadre avec des caracteres speciaux tel demande
///et affiche les informations concernant tous les prets qui sont faits


void menu_etat(void);
///cette fonction est appele par generation_etat() pour afficher le menu


void main(void)
{
         do
            {
              system("cls");
              system("color f0"); // fond blanc
              menu_principal();
              gotoxy(16,21);
			  printf("Donner votre choix (1-5): ");
              choix=getch();
            }while(choix!='1' && choix!='2' && choix!='3' &&choix!='4' &&choix!='5');

         switch(choix)
           {
            case '1':gestion_etudiant();
                    break;
            case '2':gestion_ouvrage();
                    break;
            case '3': gestion_pret();
                    break;
            case '4':generation_etat();
                   break;
            case '5':SetColorAndBackground(BLACK,WHITE);
                     exit(0);
           }

}

void gotoxy(int x,int y)
     {
          coord.X=x;
          coord.Y=y;
          SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
     }

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
void menu_principal(void)
    {
             system("color f0");
             SetColorAndBackground(YELLOW,BLUE);
             gotoxy(15,3); printf("                                                ");
             gotoxy(15,4); printf("     GESTION DE BIBLIOTHEQUE UNIVERSITAIRE      ");
             gotoxy(15,5); printf("                                                ");
             gotoxy(15,8); printf("                                                ");
             gotoxy(15,9); printf("       1- GESTION DES ETUDIANTS                 ");
             gotoxy(15,10);printf("                                                ");
             gotoxy(15,11);printf("       2- GESTION DES OUVRAGES                  ");
             gotoxy(15,12);printf("                                                ");
             gotoxy(15,13);printf("       3- GESTION DES PRETS                     ");
             gotoxy(15,14);printf("                                                ");
             gotoxy(15,15);printf("       4- GENERATION D'ETATS                    ");
             gotoxy(15,16);printf("                                                ");
             gotoxy(15,17);printf("       5- QUITTER                               ");
             gotoxy(15,18);printf("                                                ");
}

void gestion_etudiant(void)
       {
              system("cls");
              system("color f0"); // fond blanc
              menu_gestion_etudiant();
do{
                gotoxy(6,25);
                choix1=getch();
                switch(choix1)
                   {

                       case 59:  nouveau_etudiant(); main();
                              break;
                       case 60:consulter_etudiant();main();
                               break;
                       case 61:modifier_etudiant();main();
                               break;
                       case 62:  supprimer_etudiant();main();
                               break;
                       case 27: main();
                               break;

                   }
}while(choix1!=59 && choix1!=60 && choix1!=61 &&choix1!=62 &&choix1!=27);
return;
}
  void nouveau_etudiant(void)
  {

                 system("cls");
                 system("color f0"); // fond blanc
                 menu_gestion_etudiant();
                 SetColorAndBackground(WHITE,GREEN);
                 gotoxy(23,23);printf(" Enregistrer ");
                 gotoxy(53,23);printf("   Annuler   ")  ;

                 if(nombre_elements<200)
                        {
                            SetColorAndBackground(BLACK,WHITE);
                            gotoxy(33,9);printf("Nouveau etudiant :");
                            gotoxy(30,11);scanf("%d",&c1[nombre_elements].id);
                            gotoxy(30,13);scanf("%s",c1[nombre_elements].nom);
                            gotoxy(30,15);scanf("%s",c1[nombre_elements].prenom);
                            gotoxy(30,17);scanf("%s",c1[nombre_elements].filiere);
                            gotoxy(30,19);scanf("%s",c1[nombre_elements].tele);
                            gotoxy(30,21);scanf("%s",c1[nombre_elements].annee);
                            system("cls");
                            system("color f0"); // fond blanc
                            SetColorAndBackground(GREEN,LIGHTGRAY);
                            gotoxy(27,9); printf("                                 ");
                            gotoxy(27,10);printf(" LE NOUVEAU ETUDIANT EST AJOUTE! ");
                            gotoxy(27,11);printf("                                 ");
                            SetColorAndBackground(BLACK,WHITE);
                            nombre_elements++;
                            Sleep(2000);
                            gestion_etudiant();

                        }
                    else{

                            system("cls");
                            system("color f0"); // fond blanc
                            SetColorAndBackground(RED,LIGHTGRAY);
                            gotoxy(27,9); printf("                      ");
                            gotoxy(27,10);printf(" La table est pleine! ");
                            gotoxy(27,11);printf("                      ");
                            Sleep(2000);
                            gestion_etudiant();
                        }
    return;
    }

void consulter_etudiant(void)
  { int ide;

                             if(nombre_elements==0)
                                {
                                system("cls");
                                system("color f0"); // fond blanc
                                SetColorAndBackground(RED,LIGHTGRAY);
                                gotoxy(27,9); printf("                      ");
                                gotoxy(27,10);printf("  La table est vide!  ");
                                gotoxy(27,11);printf("                      ");
                                Sleep(2000);
                                gestion_etudiant();
                                }
                           system("cls");
                           system("color f0"); // fond blanc
                           SetColorAndBackground(BLUE,LIGHTGRAY);
                           gotoxy(33,9);printf("Consulter etudiant :");
                           SetColorAndBackground(BLACK,WHITE);
                           menu_gestion_etudiant();
                           SetColorAndBackground(WHITE,GREEN);
                             gotoxy(10,23);
                             printf("    >>     ");
                             gotoxy(27,23);
                             printf("     >     ");
                             gotoxy(43,23);
                             printf("     <     ");
                             gotoxy(58,23);
                             printf("    <<    ");
                             SetColorAndBackground(BLACK,WHITE);
                             gotoxy(30,11);scanf("%d",&ide);
                             chercher_etudiant(ide);

                            if(nombre_elements>0&&chercher_etudiant(ide)==ide)
                                   {
                                        gotoxy(30,13);printf("%s",c1[i].nom);
                                        gotoxy(30,15);printf("%s",c1[i].prenom);
                                        gotoxy(30,17);printf("%s",c1[i].filiere);
                                        gotoxy(30,19);printf("%s",c1[i].tele);
                                        gotoxy(30,21);printf("%s",c1[i].annee);
                                        Sleep(2000);
                                        gestion_etudiant();
                                   }

                             else
                                { system("cls");
                                    system("color f0"); // fond blanc
                                    SetColorAndBackground(RED,LIGHTGRAY);
                                    gotoxy(27,9); printf("                                   ");
                                    gotoxy(27,10);printf(" LE NUMERO D'ETUDIANT N'EXISTE PAS ");
                                    gotoxy(27,11);printf("                                   ");
                                    Sleep(2000);
                                    gestion_etudiant();
                                }
return;
  }
    ///retourne le numero d'etudiant s'il existe dans la table
    ///en plus determine sa position dans la varaible globale i
    ///cette variable i sera utilisé dans differentes fonctions
    ///pour acceder aux differents champs d'u etudiant
    ///on cherche un etudiant sachant son numero x
    int chercher_etudiant(int x)

     {int temp1,temp2;


                          for(i=0;i<nombre_elements;i++)
                             {
                                   if(x==c1[i].id)
                                       {
                                           temp1=x;temp2=i;i=nombre_elements+1;//pour sortir une fois trouve
                                       }else
                                       {
                                          temp1=-1;
                                        }
                            }
                            i=temp2; //garde la postion de l'etudiant trouve dans la table
    return temp1;
     }

      void menu_gestion_etudiant(void)
    {
                     for(j=0;j<=75;j++)
                            {
                                gotoxy(3+j,5);printf("\304");
                            }
                       gotoxy(3,5);
                       printf("\332");
                       for(j=0;j<=17;j++)
                            {
                              gotoxy(3,6+j);printf("\263");
                            }
                       gotoxy(3,24);
                       printf("\300");
                       for(j=0;j<=73;j++)
                            {
                                gotoxy(4+j,24);printf("\304");
                            }
                       printf("\331");
                       for(j=0;j<=18;j++)
                            {
                              gotoxy(78,23-j);printf("\263");
                            }
                       gotoxy(78,5);printf("\277");

                    SetColorAndBackground(BLACK,LIGHTGRAY);
                    gotoxy(6,6);printf("                           GESTION DES ETUDIANTS                     ");
                    SetColorAndBackground(BLACK,WHITE);
                    gotoxy(9,11);printf("Numero D'etudiant   :..........................................");
                    gotoxy(9,13);printf("Nom                 :..........................................");
                    gotoxy(9,15);printf("Prenom              :..........................................");
                    gotoxy(9,17);printf("Filiere             :..........................................");
                    gotoxy(9,19);printf("Tel                 :..........................................");
                    gotoxy(9,21);printf("Annee_inscrit       :..........................................");
                    SetColorAndBackground(BLACK,LIGHTGRAY);
                    gotoxy(6,25);printf("F1:Nouveau    F2:Consulter    F3:Modifier    F4:Supprimer    ESC:MENU");



   return;
    }
 void modifier_etudiant()
  {int idm;
             if(nombre_elements==0)
                {
                 system("cls");
                system("color f0"); // fond blanc
                SetColorAndBackground(RED,LIGHTGRAY);
                gotoxy(27,9); printf("                      ");
                gotoxy(27,10);printf("  La table est vide!  ");
                gotoxy(27,11);printf("                      ");
                Sleep(2000);
                 gestion_etudiant();
                }
            system("cls");
            system("color f0"); // fond blanc
             menu_gestion_etudiant();
             gotoxy(30,9);printf("Modifier Etudiant :");
             SetColorAndBackground(WHITE,GREEN);

          gotoxy(10,23);
                             printf("    >>     ");
                             gotoxy(27,23);
                             printf("     >     ");
                             gotoxy(43,23);
                             printf("     <     ");
                             gotoxy(58,23);
                             printf("    <<    ");
                             SetColorAndBackground(BLACK,WHITE);
                             gotoxy(30,11);scanf("%d",&idm);
                chercher_etudiant(idm);
            if(nombre_elements>0&&chercher_etudiant(idm)==idm)
               {
                     gotoxy(30,13);
                     scanf("%s",c1[i].nom);
                     gotoxy(30,15);
                     scanf("%s",c1[i].prenom);
                     gotoxy(30,17);
                     scanf("%s",c1[i].filiere);
                     gotoxy(30,19);
                     scanf("%s",c1[i].tele);
                     gotoxy(30,21);
                     scanf("%s",c1[i].annee);
                     system("cls");
                            system("color f0"); // fond blanc
                            SetColorAndBackground(GREEN,LIGHTGRAY);
                            gotoxy(27,9); printf("                                 ");
                            gotoxy(27,10);printf("      L'ETUDIANT EST MODIFIE     ");
                            gotoxy(27,11);printf("                                 ");
                            SetColorAndBackground(BLACK,WHITE);
                            Sleep(2000);
                            gestion_etudiant();

              }
        else {   system("cls");
                                    system("color f0"); // fond blanc
                                    SetColorAndBackground(RED,LIGHTGRAY);
                                    gotoxy(27,9); printf("                                   ");
                                    gotoxy(27,10);printf(" LE NUMERO D'ETUDIANT N'EXISTE PAS ");
                                    gotoxy(27,11);printf("                                   ");
                                    Sleep(2000);
                                    gestion_etudiant();
                 gestion_etudiant();
            }
return;
  }
     void supprimer_etudiant(void)
    {int ids,temp1;
     char temp2[20];

                                if(nombre_elements==0)
                {
                 system("cls");
                                system("color f0"); // fond blanc
                                SetColorAndBackground(RED,LIGHTGRAY);
                                gotoxy(27,9); printf("                      ");
                                gotoxy(27,10);printf("  La table est vide!  ");
                                gotoxy(27,11);printf("                      ");
                                Sleep(2000);
                                gestion_etudiant();
                }
                                 system("cls");
                                  system("color f0"); // fond blanc
                               menu_gestion_etudiant();
                               gotoxy(30,9);printf("Supprimer Etudiant :");
                              SetColorAndBackground(WHITE,GREEN);
                              gotoxy(10,23);
                             printf("    >>     ");
                             gotoxy(27,23);
                             printf("     >     ");
                             gotoxy(43,23);
                             printf("     <     ");
                             gotoxy(58,23);
                             printf("    <<    ");

                              SetColorAndBackground(BLACK,WHITE);
                            gotoxy(30,11);
                            scanf("%d",&ids);
                            chercher_etudiant(ids);

                        if(nombre_elements>0&&chercher_etudiant(ids)==ids)
                                   {
                                         gotoxy(30,13);printf("%s",c1[i].nom);
                                         gotoxy(30,15);printf("%s",c1[i].prenom);
                                         gotoxy(30,17);printf("%s",c1[i].filiere);
                                         gotoxy(30,19);printf("%s",c1[i].tele);
                                         gotoxy(30,21);printf("%s",c1[i].annee);
                                         Sleep(2000);

                                         system("cls");
                                         system("color f0"); // fond blanc
                                         SetColorAndBackground(RED,LIGHTGRAY);
                                         gotoxy(27,9); printf("                                 ");
                                         gotoxy(27,10);printf("  VOULEZ VOUS SUPPRIMER (o/n)?   ");
                                         gotoxy(27,11);printf("                                 ");
                                          gotoxy(57,10);confirme=getch();
                                         SetColorAndBackground(BLACK,WHITE);


                                         if (confirme=='o') {

                                            for(j=i;j<nombre_elements;j++)
                                            {

                                                  c1[j].id=c1[j+1].id;
                                                strcpy(c1[j].nom,c1[j+1].nom);
                                                strcpy(c1[j].prenom,c1[j+1].prenom);
                                                 strcpy(c1[j].filiere,c1[j+1].filiere);
                                                 strcpy(c1[j].tele,c1[j+1].tele);
                                                 strcpy(c1[j].annee,c1[j+1].annee);

                                          }
                                                  nombre_elements--;


                                                system("cls");
                            system("color f0"); // fond blanc
                            SetColorAndBackground(GREEN,LIGHTGRAY);
                            gotoxy(27,9); printf("                                 ");
                            gotoxy(27,10);printf("      L'ETUDIANT EST SUPPRIME    ");
                            gotoxy(27,11);printf("                                 ");
                            SetColorAndBackground(BLACK,WHITE);
                            Sleep(2000);
                            gestion_etudiant();
                             }
                             else gestion_etudiant();


                            }



                 else        {
                                         system("cls");
                                    system("color f0"); // fond blanc
                                    SetColorAndBackground(RED,LIGHTGRAY);
                                    gotoxy(27,9); printf("                                   ");
                                    gotoxy(27,10);printf(" LE NUMERO D'ETUDIANT N'EXISTE PAS ");
                                    gotoxy(27,11);printf("                                   ");
                                    Sleep(2000);
                                    gestion_etudiant();

                             }


  return;

}

void gestion_ouvrage(void)
      {
            system("cls");
              system("color f0"); // fond blanc
              menu_gestion_ouvrage();

do{
        gotoxy(6,25);
        choix1=getch();
        switch(choix1)
        {

           case 59:  Nouveau_ouvrage();main();
                  break;
           case 60:consulter_ouvrage();main();
                  break;
           case 61:modifier_ouvrage();main();
                   break;
           case 62:supprimer_ouvrage();main();
                  break;
           case 27: main();
                  break;
                    }

}while(choix1!=59 && choix1!=60 && choix1!=61 &&choix1!=62 &&choix1!=27);
return;
}
void Nouveau_ouvrage(void)
     {

                 system("cls");
                 system("color f0"); // fond blanc
                 menu_gestion_ouvrage();
                 SetColorAndBackground(WHITE,GREEN);
                 gotoxy(23,23);printf(" Enregistrer ");
                 gotoxy(53,23);printf("   Annuler   ")  ;

                    if(nb_ch<200 &&nb_ch>=0)
                            {
                                SetColorAndBackground(BLACK,WHITE);
                                gotoxy(30,11);scanf("%d",&c2[nb_ch].id);
                                gotoxy(30,13);scanf("%s",c2[nb_ch].titre);
                                gotoxy(30,15);scanf("%s",c2[nb_ch].annee);
                                gotoxy(30,17);scanf("%s",c2[nb_ch].auteur);
                                gotoxy(30,19);scanf("%s",c2[nb_ch].specialite);

                                system("cls");
                            system("color f0"); // fond blanc
                            SetColorAndBackground(GREEN,LIGHTGRAY);
                            gotoxy(27,9); printf("                                 ");
                            gotoxy(27,10);printf("      L'OUVRAGE EST AJOUTE!      ");
                            gotoxy(27,11);printf("                                 ");
                            SetColorAndBackground(BLACK,WHITE);
                            nb_ch++;
                            Sleep(2000);
                            gestion_ouvrage();



                              }


                      else{      system("cls");
                            system("color f0"); // fond blanc
                            SetColorAndBackground(RED,LIGHTGRAY);
                            gotoxy(27,9); printf("                      ");
                            gotoxy(27,10);printf(" La table est pleine! ");
                            gotoxy(27,11);printf("                      ");
                            Sleep(2000);
                            gestion_ouvrage();

                          }
return;
   }
   void consulter_ouvrage(void)
  { int ide;

                     if(nb_ch ==0)
                         {

                                system("cls");
                                system("color f0"); // fond blanc
                                SetColorAndBackground(RED,LIGHTGRAY);
                                gotoxy(27,9); printf("                      ");
                                gotoxy(27,10);printf("  La table est vide!  ");
                                gotoxy(27,11);printf("                      ");
                                Sleep(2000);
                                gestion_ouvrage();
                      }
                    system("cls");

                           system("color f0"); // fond blanc
                    menu_gestion_ouvrage();
                    SetColorAndBackground(BLUE,LIGHTGRAY);
                    gotoxy(30,12);printf("Consulter Ouvrage :");
                   SetColorAndBackground(WHITE,GREEN);
                   gotoxy(10,23);
                             printf("    >>     ");
                             gotoxy(27,23);
                             printf("     >     ");
                             gotoxy(43,23);
                             printf("     <     ");
                             gotoxy(58,23);
                             printf("    <<    ");

                  SetColorAndBackground(BLACK,WHITE);
                  gotoxy(70,14);scanf("%d",&ide);
                  chercher_ouvrage(ide);
              if(nb_ch>0&&chercher_ouvrage(ide)==ide)
                    {

                                             gotoxy(30,13);printf("%s",c2[i].titre);
                                             gotoxy(30,15);printf("%s",c2[i].annee);
                                             gotoxy(30,17);printf("%s",c2[i].auteur);
                                             gotoxy(30,19);printf("%s",c2[i].specialite);
                                             Sleep(2000);
                                             gestion_ouvrage();


                       }
                 else
                       {
                            system("cls");
                                    system("color f0"); // fond blanc
                                    SetColorAndBackground(RED,LIGHTGRAY);
                                    gotoxy(27,9); printf("                                   ");
                                    gotoxy(27,10);printf("  LE NUMERO D'OUVRAGE N'EXISTE PAS ");
                                    gotoxy(27,11);printf("                                   ");
                                    Sleep(2000);
                                    gestion_ouvrage();
                        }
return;
  }
  int chercher_ouvrage(int x)
     {int temp1,temp2;

                    for(i=0;i<nb_ch;i++)
                          {
                               if(x==c2[i].id)
                                   {
                                     temp1=x;
                                     temp2=i;
                                     i=nb_ch+1;
                                   }

                               else {temp1=-1;}
                           }
                           i=temp2;
     return temp1;
     }
 void menu_gestion_ouvrage(void)
    {        for(j=0;j<=75;j++)
                            {
                                gotoxy(3+j,5);printf("\304");
                            }
                       gotoxy(3,5);
                       printf("\332");
                       for(j=0;j<=17;j++)
                            {
                              gotoxy(3,6+j);printf("\263");
                            }
                       gotoxy(3,24);
                       printf("\300");
                       for(j=0;j<=73;j++)
                            {
                                gotoxy(4+j,24);printf("\304");
                            }
                       printf("\331");
                       for(j=0;j<=18;j++)
                            {
                              gotoxy(78,23-j);printf("\263");
                            }
                       gotoxy(78,5);printf("\277");

                    SetColorAndBackground(BLACK,LIGHTGRAY);
                    gotoxy(6,6); printf("                        GESTION DES OUVRAGESS                       ");
                    SetColorAndBackground(BLACK,WHITE);
                    gotoxy(9,11);printf("Numero              :..........................................");
                    gotoxy(9,13);printf("Titre               :..........................................");
                    gotoxy(9,15);printf("Annee d'edition     :..........................................");
                    gotoxy(9,17);printf("Auteur              :..........................................");
                    gotoxy(9,19);printf("Specialite          :..........................................");
                    SetColorAndBackground(BLACK,LIGHTGRAY);
                    gotoxy(6,25);printf("F1:Nouveau    F2:Consulter    F3:Modifier    F4:Supprimer    ESC:MENU");

   return;
    }
    void modifier_ouvrage(void)
    { int idm;
                            if(nb_ch==0)
                                 {
                                   system("cls");
                                system("color f0"); // fond blanc
                                SetColorAndBackground(RED,LIGHTGRAY);
                                gotoxy(27,9); printf("                      ");
                                gotoxy(27,10);printf("  La table est vide!  ");
                                gotoxy(27,11);printf("                      ");
                                Sleep(2000);
                                gestion_ouvrage();
                                  }

                            system("cls");
                             menu_gestion_ouvrage();
                             gotoxy(30,10);printf("Modifier ouvrage:");
                             SetColorAndBackground(WHITE,GREEN);
                             gotoxy(10,23);
                             printf("    >>     ");
                             gotoxy(27,23);
                             printf("     >     ");
                             gotoxy(43,23);
                             printf("     <     ");
                             gotoxy(58,23);
                             printf("    <<    ");
                             SetColorAndBackground(BLACK,WHITE);
                             gotoxy(70,14);scanf("%d",&idm);
                             chercher_ouvrage(idm);
                              if(nb_ch>0&&chercher_ouvrage(idm)==idm)
                                {
                                              gotoxy(30,13);scanf("%s",c2[i].titre);
                                              gotoxy(30,15);scanf("%s",c2[i].annee);
                                              gotoxy(30,17);scanf("%s",c2[i].auteur);
                                              gotoxy(30,19);scanf("%s",c2[i].specialite);

                                            system("cls");
                            system("color f0"); // fond blanc
                            SetColorAndBackground(GREEN,LIGHTGRAY);
                            gotoxy(27,9); printf("                                 ");
                            gotoxy(27,10);printf("      L'ETUDIANT EST MODIFIE     ");
                            gotoxy(27,11);printf("                                 ");
                            SetColorAndBackground(BLACK,WHITE);
                            Sleep(2000);
                            gestion_ouvrage();
                                }
                            else
                               {
                                               system("cls");
                                    system("color f0"); // fond blanc
                                    SetColorAndBackground(RED,LIGHTGRAY);
                                    gotoxy(27,9); printf("                                   ");
                                    gotoxy(27,10);printf("  LE NUMERO D'OUVRAGE N'EXISTE PAS ");
                                    gotoxy(27,11);printf("                                   ");
                                    Sleep(2000);
                                    gestion_ouvrage();

                                }

return;
    }
    void supprimer_ouvrage(void)
    {int ids,temp1;
     char temp2[15];
                       if(nb_ch==0)
                                 {
                                   system("cls");
                                system("color f0"); // fond blanc
                                SetColorAndBackground(RED,LIGHTGRAY);
                                gotoxy(27,9); printf("                      ");
                                gotoxy(27,10);printf("  La table est vide!  ");
                                gotoxy(27,11);printf("                      ");
                                Sleep(2000);
                                    gestion_ouvrage();
                                  }


                       system("cls");
                       system("color f0"); // fond blanc
                       menu_gestion_ouvrage();
                       SetColorAndBackground(WHITE,GREEN);
                       gotoxy(10,23);
                             printf("    >>     ");
                             gotoxy(27,23);
                             printf("     >     ");
                             gotoxy(43,23);
                             printf("     <     ");
                             gotoxy(58,23);
                             printf("    <<    ");
                       SetColorAndBackground(BLACK,WHITE);
                       gotoxy(70,14);scanf("%d",&ids);
                       chercher_ouvrage(ids);
                    if(nb_ch>0&&chercher_ouvrage(ids)==ids)

                    {

                        gotoxy(30,13);printf("%s",c2[i].titre);
                        gotoxy(30,15);printf("%d",c2[i].annee);
                        gotoxy(30,17);printf("%d",c2[i].auteur);
                        gotoxy(30,19);printf("%d",c2[i].specialite);
                        Sleep(2000);
                       system("cls");
                                         system("color f0"); // fond blanc
                                         SetColorAndBackground(RED,LIGHTGRAY);
                                         gotoxy(27,9); printf("                                 ");
                                         gotoxy(27,10);printf("  VOULEZ VOUS SUPPRIMER (o/n)?   ");
                                         gotoxy(27,11);printf("                                 ");
                                          gotoxy(57,10);confirme=getch();
                                         SetColorAndBackground(BLACK,WHITE);


                                         if (confirme=='o') {

                        for(j=i;j<=nb_ch;j++)
                         {
                              c2[j].id=c2[j+1].id;
                             strcpy(c2[j].titre,c2[j+1].titre);
                             strcpy(c2[j].annee,c2[j+1].annee);
                             strcpy(c2[j].auteur,c2[j+1].auteur);
                             strcpy(c2[j].titre,c2[j+1].specialite);


                          }
                          nb_ch--;
                        system("cls");
                            system("color f0"); // fond blanc
                            SetColorAndBackground(GREEN,LIGHTGRAY);
                            gotoxy(27,9); printf("                                 ");
                            gotoxy(27,10);printf("      L'OUVRAGE EST SUPPRIME     ");
                            gotoxy(27,11);printf("                                 ");
                            SetColorAndBackground(BLACK,WHITE);
                            Sleep(2000);
                            gestion_ouvrage();
                            } else gestion_ouvrage();
                    }
                else
                    {
                                              system("cls");
                                    system("color f0"); // fond blanc
                                    SetColorAndBackground(RED,LIGHTGRAY);
                                    gotoxy(27,9); printf("                                   ");
                                    gotoxy(27,10);printf("  LE NUMERO D'OUVRAGE N'EXISTE PAS ");
                                    gotoxy(27,11);printf("                                   ");
                                    Sleep(2000);
                                    gestion_ouvrage();
                    }



return;
    }

void gestion_pret( void)
      {
            system("cls");
              system("color f0"); // fond blanc
              menu_gestion_pret();
do{
           gotoxy(6,25);
           choix1=getch();

           switch (choix1)
               {
                  case 59: nouveau_pret();main();
                         break;
                  case 60:  consulter_pret();main();
                         break;
                  case 61: modifier_pret();main();
                         break;
                  case 62:supprimer_pret();main();
                           break;
                  case 27: main();
                         break;
                  }
}while(choix1!=59 && choix1!=60 && choix1!=61 &&choix1!=62 &&choix1!=27);
return;
}
void nouveau_pret( void)
{
                 system("cls");
                 system("color f0"); // fond blanc
                 menu_gestion_pret();
                 SetColorAndBackground(WHITE,GREEN);
                 gotoxy(23,23);printf(" Enregistrer ");
                 gotoxy(53,23);printf("   Annuler   ");

               if(num_pret<100)
                   {
                     SetColorAndBackground(BLACK,WHITE);
                      gotoxy(28,12);printf("Nouveau Pret :");
                      menu_gestion_pret();

                      gotoxy(35,14);scanf("%d",&c3[num_pret].Numero_De_Pret);
                     gotoxy(35,16);scanf("%s",c3[num_pret].jour1);
                     gotoxy(41,16);scanf("%s",c3[num_pret].mois1);
                     gotoxy(47,16);scanf("%s",c3[num_pret].ann1);
                     gotoxy(35,18);scanf("%s",c3[num_pret].jour2);
                     gotoxy(41,18);scanf("%s",c3[num_pret].mois2);
                     gotoxy(47,18);scanf("%s",c3[num_pret].ann2);
                     gotoxy(52,20);scanf("%d",&c3[num_pret].duree);

                            system("cls");
                            system("color f0"); // fond blanc
                            SetColorAndBackground(GREEN,LIGHTGRAY);
                            gotoxy(27,9); printf("                                 ");
                            gotoxy(27,10);printf("       LE PRET EST AJOUTE!       ");
                            gotoxy(27,11);printf("                                 ");
                            SetColorAndBackground(BLACK,WHITE);
                            num_pret++;
                            Sleep(2000);
                            gestion_pret();

        }else{

                            system("color f0"); // fond blanc
                            SetColorAndBackground(RED,LIGHTGRAY);
                            gotoxy(27,9); printf("                      ");
                            gotoxy(27,10);printf(" La table est pleine! ");
                            gotoxy(27,11);printf("                      ");
                            Sleep(2000);
                            gestion_pret();
             }
return;
}


void consulter_pret (void)
   {int idr;
                 if(num_pret==0)
                   { system("cls");
                                system("color f0"); // fond blanc
                                SetColorAndBackground(RED,LIGHTGRAY);
                                gotoxy(27,9); printf("                      ");
                                gotoxy(27,10);printf("  La table est vide!  ");
                                gotoxy(27,11);printf("                      ");
                                Sleep(2000);
                                gestion_pret();
                    }
                    system("cls");

                           system("color f0"); // fond blanc
                    SetColorAndBackground(BLUE,LIGHTCYAN);
                    gotoxy(28,12);printf("Consulter Pret :");
                    menu_gestion_pret();
                    gotoxy(35,14);scanf("%d",&idr);
                    chercher_pret(idr);
                    if(num_pret>0&&chercher_pret(idr)==idr)
                    {
                     gotoxy(35,16);printf("%s",c3[num_pret].jour1);
                     gotoxy(41,16);printf("%s",c3[num_pret].mois1);
                     gotoxy(47,16);printf("%s",c3[num_pret].ann1);
                     gotoxy(35,18);printf("%s",c3[num_pret].jour2);
                     gotoxy(41,18);printf("%s",c3[num_pret].mois2);
                     gotoxy(47,18);printf("%s",c3[num_pret].ann2);
                     gotoxy(52,20);printf("%d",c3[num_pret].duree);
                     Sleep(2000);
                     gestion_pret();
             }
         else{
                     system("cls");
                                    system("color f0"); // fond blanc
                                    SetColorAndBackground(RED,LIGHTGRAY);
                                    gotoxy(27,9); printf("                                        ");
                                    gotoxy(27,10);printf("    LE NUMERO DE PRET N'EXISTE PAS      ");
                                    gotoxy(27,11);printf("                                        ");
                                    Sleep(2000);
                                    gestion_pret();
              }
return;
  }

 void modifier_pret (void)
  {int idm;
             if(num_pret==0)
                   { system("cls");
                                system("color f0"); // fond blanc
                                SetColorAndBackground(RED,LIGHTGRAY);
                                gotoxy(27,9); printf("                      ");
                                gotoxy(27,10);printf("  La table est vide!  ");
                                gotoxy(27,11);printf("                      ");
                                Sleep(2000);
                      gestion_pret();
                    }

                system("cls");
                system("color f0"); // fond blanc
                SetColorAndBackground(BLUE,LIGHTGRAY);
                gotoxy(28,12);printf("Modifier Pret :");
                menu_gestion_pret();
                gotoxy(35,14);scanf("%d",&idm);
                chercher_pret(idm);
            if(num_pret>0&&chercher_pret(idm)==idm)
               {
                     gotoxy(35,16);scanf("%s",c3[i].jour1);
                     gotoxy(41,16);scanf("%s",c3[i].mois1);
                     gotoxy(47,16);scanf("%s",c3[i].ann1);
                     gotoxy(35,18);scanf("%s",c3[i].jour2);
                     gotoxy(41,18);scanf("%s",c3[i].mois2);
                     gotoxy(47,18);scanf("%s",c3[i].ann2);
                     gotoxy(52,20);scanf("%d",&c3[i].duree);
                     Sleep(2000);
                     gestion_pret();
              }
        else {
                 system("cls");
                                    system("color f0"); // fond blanc
                                    SetColorAndBackground(RED,LIGHTGRAY);
                                    gotoxy(27,9); printf("                                   ");
                                    gotoxy(27,10);printf("  LE NUMERO DE PRET N'EXISTE PAS   ");
                                    gotoxy(27,11);printf("                                   ");
                                    Sleep(2000);
                                    gestion_pret();
            }
return;
  }



 void supprimer_pret (void)
  {int k,A,ids;
   char B[15];
                if(num_pret==0)
                   { system("cls");

                                system("color f0"); // fond blanc
                                SetColorAndBackground(RED,LIGHTGRAY);
                                gotoxy(27,9); printf("                      ");
                                gotoxy(27,10);printf("  La table est vide!  ");
                                gotoxy(27,11);printf("                      ");
                                Sleep(2000);
                    gestion_pret();
                    }

                 system("cls");
                 system("color f0"); // fond blanc
                 SetColorAndBackground(BLUE,LIGHTCYAN);
                 gotoxy(28,12);printf("Supprimer Pret :");
                 menu_gestion_pret();
                 gotoxy(35,14);scanf("%d",&ids);
                 chercher_pret(ids);

              if(num_pret>0&&chercher_pret(ids)==ids)
               { gotoxy(35,16);printf("%s",c3[i].jour1);
                     gotoxy(41,16);printf("%s",c3[i].mois1);
                     gotoxy(47,16);printf("%s",c3[i].ann1);
                     gotoxy(35,18);printf("%s",c3[i].jour2);
                     gotoxy(41,18);printf("%s",c3[i].mois2);
                     gotoxy(47,18);printf("%s",c3[i].ann2);
                     gotoxy(52,20);printf("%d",c3[i].duree);
                    system("cls");
                                         system("color f0"); // fond blanc
                                         SetColorAndBackground(RED,LIGHTGRAY);
                                         gotoxy(27,9); printf("                                 ");
                                         gotoxy(27,10);printf("  VOULEZ VOUS SUPPRIMER (o/n)?   ");
                                         gotoxy(27,11);printf("                                 ");
                                         Sleep(2000);
                                          gotoxy(57,10);confirme=getch();
                                         SetColorAndBackground(BLACK,WHITE);


                                         if (confirme=='o') {


                for(k=i;k<num_pret;k++)
                 {

                   c3[k].Numero_De_Pret=c3[k+1].Numero_De_Pret;



                   strcpy(c3[k].jour1,c3[k+1].jour1);



                   strcpy(c3[k].mois1,c3[k+1].mois1);



                   strcpy(c3[k].ann1,c3[k+1].ann1);



                   strcpy(c3[k].jour2,c3[k+1].jour2);


                   strcpy(c3[k].mois2,c3[k+1].mois2);



                   strcpy(c3[k].ann2,c3[k+1].ann2);



                   c3[k].duree=c3[k+1].duree;


                 }
                num_pret--;
                system("cls");
                            system("color f0"); // fond blanc
                            SetColorAndBackground(GREEN,LIGHTGRAY);
                            gotoxy(27,9); printf("                                 ");
                            gotoxy(27,10);printf("     LE PRET EST SUPPRIME        ");
                            gotoxy(27,11);printf("                                 ");
                            SetColorAndBackground(BLACK,WHITE);
                            Sleep(2000);

                    gestion_pret();
                      }
                 else gestion_pret();


        }
    else{

                 system("cls");
                                    system("color f0"); // fond blanc
                                    SetColorAndBackground(RED,LIGHTGRAY);
                                    gotoxy(27,9); printf("                                   ");
                                    gotoxy(27,10);printf("  LE NUMERO DE PRET N'EXISTE PAS   ");
                                    gotoxy(27,11);printf("                                   ");
                                    Sleep(2000);
                                    gestion_pret();
                 }

return;
}

  void menu_gestion_pret( void)
    {
                        for(j=0;j<=75;j++)
                            {
                                gotoxy(3+j,5);printf("\304");
                            }
                       gotoxy(3,5);
                       printf("\332");
                       for(j=0;j<=17;j++)
                            {
                              gotoxy(3,6+j);printf("\263");
                            }
                       gotoxy(3,24);
                       printf("\300");
                       for(j=0;j<=73;j++)
                            {
                                gotoxy(4+j,24);printf("\304");
                            }
                       printf("\331");
                       for(j=0;j<=18;j++)
                            {
                              gotoxy(78,23-j);printf("\263");
                            }
                       gotoxy(78,5);printf("\277");

                    SetColorAndBackground(BLACK,LIGHTGRAY);
                    gotoxy(6,6); printf("                           GESTION DES PRETS                        ");
                    SetColorAndBackground(BLACK,WHITE);
                    gotoxy(9,14); printf("Numero De pret           :....................................");
                    gotoxy(9,16); printf("Date de debut de pret    :...../...../.....");
                    gotoxy(9,18); printf("Debut de retour          :...../...../.....");
                    gotoxy(35,20);printf("Duree de pret   :.................");
                    SetColorAndBackground(BLACK,LIGHTGRAY);
                    gotoxy(6,25);printf("F1:Nouveau    F2:Consulter    F3:Modifier    F4:Supprimer    ESC:MENU");
   return;
    }

 int chercher_pret(int x)
     {int a,b;
                     for(i=0;i<num_pret;i++)
                      {
                         if(x==c3[i].Numero_De_Pret)
                          {
                             a=x;
                             b=i;
                             i=num_pret+1;
                         }else{
                                 a=-1;
                              }
                      }
                         i=b;
return a;
     }



void menu_etat(void)
    {        system("cls");
             system("color f0");
             SetColorAndBackground(YELLOW,BLUE);
             gotoxy(18,7);printf("                                            ");
             gotoxy(18,8);printf("             GENERATION D'ETATS             ");
             gotoxy(18,9);printf("                                            ");

            gotoxy(18,12);printf("                                            ");
            gotoxy(18,13);printf("             1- PRET EN COURS               ");
            gotoxy(18,14);printf("                                            ");


            gotoxy(18,17);printf("                                            ");
            gotoxy(18,18);printf("             2- QUITTER                     ");
            gotoxy(18,19);printf("                                            ");
return;
    }


void generation_etat(void)
    {

 do{
              system("cls");
              system("color f0"); // fond blanc
              menu_etat();
             gotoxy(19,21);printf("Donner votre choix (1-2): ");
             choix=getch();
              switch(choix)
            {
            case '1': pret_encours();main();
                     break;

            case '2':main();
                     break;
            }
             }while(choix!='1' && choix!='2');

return;
    }

void pret_encours(void)
        { int k,i;
            system("cls");system("color f0"); // fond blanc

          for(j=0;j<=76;j++)
                            {
                                gotoxy(3+j,7);printf("\304");
                            }
                 for(i=0;i<num_pret;i++)
                            {

                     for(j=0;j<=76;j++)
                            {
                                gotoxy(3+j,12+2*i);printf("\304");
                            }
                            }
         for(j=0;j<=76;j++)
                            {
                                gotoxy(3+j,10);printf("\304");
                            }
                    gotoxy(3,7);
                       printf("\332");
                       gotoxy(3,17);
                       printf("\332");
         for(j=0;j<=8+num_pret;j++)
                            {
                              gotoxy(3,8+j);printf("\263");
                            }
                       gotoxy(3,8+j);
                       printf("\300");
                k=j;
                     for(j=0;j<=76;j++)
                            {
                                gotoxy(3+j,8+k);printf("\304");
                            }
printf("\331");
                        for(j=0;j<=8+num_pret;j++)
                            {
                              gotoxy(80,16+num_pret-j);printf("\263");
                              gotoxy(17,16+num_pret-j);printf("\263");
                              gotoxy(33,16+num_pret-j);printf("\263");
                              gotoxy(47,16+num_pret-j);printf("\263");
                              gotoxy(59,16+num_pret-j);printf("\263");
                              gotoxy(68,16+num_pret-j);printf("\263");

                            }
                       gotoxy(80,16+num_pret-j);printf("\277");
                          gotoxy(17,16+num_pret-j);printf("\332");
                              gotoxy(33,16+num_pret-j);printf("\332");
                              gotoxy(47,16+num_pret-j);printf("\332");
                              gotoxy(59,16+num_pret-j);printf("\332");
                              gotoxy(68,16+num_pret-j);printf("\332");
                               gotoxy(33,8+j);printf("\300");
                                gotoxy(17,8+j);printf("\300");
                                 gotoxy(47,8+j);printf("\300");
                                  gotoxy(59,8+j);printf("\300");
                                   gotoxy(68,8+j);printf("\300");
                                    gotoxy(3,8+j);printf("\300");







              SetColorAndBackground(BLUE,LIGHTGRAY);
              gotoxy(8,3);printf("                                                                     ");
              gotoxy(8,4);printf("                    GENERATION D'ETATS:LES PRETS                     ");
              gotoxy(8,5);printf("                                                                     ");
            gotoxy(5,8);printf("Pret numero");
            gotoxy(20,8);printf("Nom etudiant");
            gotoxy(35,8);printf("Date debut "); gotoxy(37,9);printf("pret");
            gotoxy(50,8);printf("Date de"); gotoxy(50,9);printf("retour");
           gotoxy(60,8);printf("Ouvrage ");
            gotoxy(70,8);printf("Specialite");


          for(i=0;i<num_pret;i++)
              {
                gotoxy(6,11+2*i);
                printf("%d",c3[i].Numero_De_Pret);
                gotoxy(21,11+2*i);
                printf("%s",c1[i].nom);
                gotoxy(36,11+2*i);
                printf("%s/%s/%s",c3[i].jour1,c3[i].mois1,c3[i].ann1);
                 gotoxy(51,11+2*i);
                printf("%s/%s/%s",c3[i].jour2,c3[i].mois2,c3[i].ann2);
                gotoxy(61,11+2*i);printf("%s",c2[i].titre);
                gotoxy(71,11+2*i);printf("%s",c2[i].specialite);
                }

                getch();


return;
        }



