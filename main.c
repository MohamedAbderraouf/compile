#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include"TS.h"
/*
HAMOUCHE Mohamed Abderraouf mat:191931061662 
IHADDADEN Soheib mat:191931069669
*/

struct DisplayList{

    int hachtage , dollar , etCom , pourcentage ;
};


int main()
{
char str[80]="hello # s %  dd & dd  $ ";
char display[10][8];

strcpy(display[0],"char1");
strcpy(display[1],"char2");
strcpy(display[2],"char3");
strcpy(display[3],"char4");
int i;
for ( i = 0; i < 4; i++)
{
printf("%s\n",display[i]);
    
}


    return 0;
}
    //  tab table[1024];
    //  int tailleTab;
    //  char s[1024];
    //  greeting();
    //  while (1)
    //  {
    //      printf("Veiller donner une expression::");
    //      gets(s);

    //     while (verifPar(s)==false)
    //     {
    //       printf("veiller donner une expression correct::");
    //       gets(s);
    //     }
    //  rmSpace(s);
    //  verifMul(s);
    //  printf("%s",s);
    //  tailleTab =putInTable(s,table);
    //  char x[50];
    //  pileT p=intpileT(p);
    //  p=transformation(table,tailleTab);    
    //  float o;
    //  o=resultatfinal(p);
    //  printf("=%f\n",o);
    //  }

