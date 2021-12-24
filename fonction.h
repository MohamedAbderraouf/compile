#ifndef FONCTION_H_ 
#define FONCTION_H_

//tout les type utiliser

typedef struct tab *pointTab;
typedef struct tab
{
   char  info[50];
}tab;

typedef struct cellule *pile;
  typedef struct cellule
  {
     char info;
     pile svt;
  }pille;

typedef struct cel *pileT;
  typedef struct cel
  {
     char inf[50];
     pileT svt;
  }Celle; 
  
 typedef struct pileff *pilef;
  typedef struct pileff
  {
     float nf;
     pilef svt;
  }cellef; 


//fonction pour les pile de float

pilef empilerf(pilef pf,float f);
float depilerf(pilef *p );
pilef intpilef(pilef p);
bool pilevidef(pilef p);

//fonction pour les pile de tableau

pileT empilerT(pileT p,char *x);
pileT intpileT(pileT p);
bool pilevideT(pileT p);
char* sommetpileT(pileT p );
void depilerT(pileT *p , char *x );

//fonction pour les pile de char

pile empiler(pile p,char x);
char depiler(pile *p );
bool pilevide(pile p);
pile intpile(pile p);
char sommetpile(pile p );

//fonction pour enleve les espace

void rmSpace(char *s);

//fonction pour maittre la pile dans un tableau

int putInTable( char *s,pointTab table);

//fonction pour verifier les parenthese

bool verifPar(char *t);

// les fonctions qui verifie le operation operateur et priorite

bool operateur(char *c);
bool operand(char *x);
int priorite(char *x);

//fonction pour calculer deux flaot et les retourner 

float operation(float a,float b,char *c);

//fonction pour transformer le table a une pile de tab sous forme postfixe

pileT transformation(tab t[1024],int taille);

//fonction aui calcule la pile en forme postfixe

float resultatfinal(pileT p);

// verif en cas l utisateur entre ex (a)(b) devein (a)*(b)

void verifMul(char *s);

//animation du debut du programme

void delay(int nombre) ;

void greeting();

float countExp(char * exp);

#endif 

