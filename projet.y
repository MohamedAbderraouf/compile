%{
#include <math.h>
#include <stdio.h>
#include"TS.h"

int yylex(void);
int yyerror(char *msg);
FILE *yyin;
int nb_ligne=1,i=0,Cl=0,f;
int *verifZero;
int typeInt,numOfDisplays=0,display2Length;
char forFloat[50];
char expression[80];
char display2[80] ;
char display[10][8];

//table de hachage pour les idf
list hachTable[89];
list2 ListMotCles,ListNum ,ListSeparateur ;

%}
%union {
int integer;
char* str;
float real;
}
%token mc_identification mc_division mc_programId mc_data mc_workingStorage mc_section mc_procedure mc_stopRun
<str>mc_integer <str>mc_real <str>mc_char <str>mc_string mc_const bar parOuvre parFerme point egal plus moin divi mul mc_and mc_or mc_not 
mc_gl mc_ge mc_g mc_l mc_le mc_eq mc_di pourcentage hachtage andCom dollar arob deuxPoints mc_if mc_else mc_end mc_accept
mc_display mc_move mc_to <str>idf <real>REAL <str>CHAR <str>STRING <integer>INTEGER err size line virgule
%start S
%%
S:HEADER  {
    printf("syntax correct");}
;

/*---------------------HEADER------------------------*/
HEADER:mc_identification mc_division point mc_programId point idf  point DECLARATIONS
;

/*  block declaration */
DECLARATIONS:mc_data mc_division point mc_workingStorage mc_section point DEC
;

/*  declaration */
DEC:VAR DEC
|TAB DEC      
|CONST DEC
|PROCEDURES
;
   
/* variable simple */
VAR: idf bar VAR    { if (isDeclared(hachTable,$1)!=1) {InitInfo(hachTable,$1,"",typeInt,0);} 
                          else{printf("%s deja declare plus de 2 foix\n",$1); YYERROR; } }
    |idf TYPE point { if (isDeclared(hachTable,$1)!=1) {InitInfo(hachTable,$1,"",typeInt,0);} 
                          else{printf("%s deja declare plus de 2 foix\n",$1); YYERROR;} }
;

/*  tableau   */
TAB:idf  line INTEGER  virgule size   INTEGER  TYPE  point { 
if (isDeclared(hachTable,$1)!=1)
                     { if($3 > 0 && $6 > 0 ){InitInfo(hachTable,$1,"",5,0); }
                          else{ printf("size ou line incorrect doit etre ( > 0 ) \n"); YYERROR;} } 
else{printf("%s deja declare plus de 2 foix\n",$1); YYERROR; }
}
;

CONST:mc_const idf TYPE point { if(isDeclared(hachTable,$2)!=1) {InitInfo(hachTable,$2,"",typeInt,1);} 
                                else{printf("%s deja declare plus de 2 foix\n",$2); YYERROR; } }
    
    |mc_const idf egal INTEGER point{ if(isDeclared(hachTable,$2)!=1) {intToStr($4,forFloat); InitInfo(hachTable,$2,forFloat,1,1);clearString(forFloat);} 
                                else{printf("%s deja declare plus de 2 foix\n",$2); YYERROR; } }
    
    |mc_const idf egal REAL point{ if(isDeclared(hachTable,$2)!=1) {ftoa($4,forFloat); InitInfo(hachTable,$2,forFloat,2,1);clearString(forFloat);} 
                                else{printf("%s deja declare plus de 2 foix\n",$2); YYERROR; } }
    
    |mc_const idf egal CHAR point{ if(isDeclared(hachTable,$2)!=1) {InitInfo(hachTable,$2,$4,3,1);} 
                                else{printf("%s deja declare plus de 2 foix\n",$2); YYERROR; } }
    
    |mc_const idf egal STRING point{ if(isDeclared(hachTable,$2)!=1) {InitInfo(hachTable,$2,$4,4,1);} 
                                else{printf("%s deja declare plus de 2 foix\n",$2); YYERROR; } }
                                
;


/* TYPE de  variable */
TYPE:mc_integer {typeInt=1;}
    |mc_char {typeInt=3;}
    |mc_real {typeInt=2;}
    |mc_string {typeInt=4;}
;

PROCEDURES: mc_procedure mc_division point PROCEDURES1 END
;

PROCEDURES1: AFFECTATIONS PROCEDURES1
             |ACCEPT PROCEDURES1
             |DISPLAY PROCEDURES1
             |IF PROCEDURES1
             |MOVE PROCEDURES1
             |
;

AFFECTATIONS:idf egal EXP point {
    
    if(expression[strlen(expression)-1]=='_'){
                    expression[strlen(expression)-1]='\0';
                        clearString(forFloat);

                    if(findType(expression)==1){
                        
                    if (MajError(MAJ(hachTable,$1,expression,1),$1)==0)YYERROR;
                    }
                    else
                    {
                    if (MajError(MAJ(hachTable,$1,expression,2),$1)==0)YYERROR;
                    }
                    clearString(forFloat);
                    }
    else{
      
     if (calculate(expression)==1)
     {
         printf("division sur 0");
         YYERROR;
     }
     else{
        if (MajError(MAJ(hachTable,$1,"exp math",findType(expression)),$1)==0)YYERROR; 
      }
       

    }
  clearString(expression);
}
             |idf egal CHAR point{
                if (MajError(MAJ(hachTable,$1,$3,3),$1)==0)YYERROR;
             }
             |idf egal STRING point{
                if (MajError(MAJ(hachTable,$1,$3,4),$1)==0)YYERROR;

             }  
;

/*******EXP ARETH*******/
EXP:EXP plus EXP1 {
strcat(expression,"+");
}
|EXP moin EXP1{
strcat(expression,"-");
}
|EXP1
;
EXP1:EXP1 mul EXP2{
strcat(expression,"*");
} 
| EXP1 divi EXP2{
strcat(expression,"/");
} 
| EXP2
;
EXP2:idf{

  if(isDeclared(hachTable,$1)!=1) {printf("%s : IDF non declare et utilise !\n",$1); YYERROR; }
  if( ! ( getType(hachTable,$1)==1 || getType(hachTable,$1)==2) ) {printf("%s : idf doit etre soit float ou integer\n",$1); YYERROR;}
} 
|REAL{
    clearString(forFloat);
    ftoa($1,forFloat);
strcat(expression,forFloat);
strcat(expression,"_");
}
 |INTEGER{
    clearString(forFloat);
    intToStr($1,forFloat);
strcat(expression,forFloat);
strcat(expression,"_");
}
  |parOuvre EXP parFerme
;


ODC:mc_g| mc_ge |mc_l |mc_le |mc_di |mc_eq
;

ODL:mc_and |mc_or
;

COMPARAISON:EXP point ODC  point  EXP
;        

CASENOT:mc_not |
;

LOGIC:parOuvre CASENOT COMPARAISON parFerme point ODL point LOGIC
      |parOuvre CASENOT COMPARAISON parFerme
;

/*******ACCEPT*******/
ACCEPT:mc_accept parOuvre STRING deuxPoints arob idf parFerme point{

if (strlen($3)!=3)
{
   printf("accept doit contenire un seule signe de formatage");
   YYERROR;
}
switch ($3[1])
{
case '$':
     //entier
  if(isDeclared(hachTable,$6)!=1) {printf("%s : IDF non declare et utilise !\n",$6);YYERROR;  }
  if( getType(hachTable,$6)!=1 ) {printf("%s : idf doit etre de type integer\n",$6);YYERROR;}

    break;

case '%':
    //float
  if(isDeclared(hachTable,$6)!=1) {printf("%s : IDF non declare et utilise !\n",$6);  YYERROR;}
  if( !getType(hachTable,$6)!=2 ) {printf("%s : idf doit etre de type float \n",$6);YYERROR;}
    break;
case '#':
      //string

  if(isDeclared(hachTable,$6)!=1) {printf("%s : IDF non declare et utilise !\n",$6);  YYERROR;}
  if( ! getType(hachTable,$6)!=4 ) {printf("%s : idf doit etre de type string\n",$6);YYERROR;}
    break;
case '&':
    //char
  if(isDeclared(hachTable,$6)!=1) {printf("%s : IDF non declare et utilise !\n",$6); YYERROR; }
  if( !getType(hachTable,$6)!=3 ) {printf("%s : idf doit etre de type char\n",$6);YYERROR;}
    break;
default:
    break;
}


}
;

/*******DISPLAY*******/
DISPLAY:mc_display parOuvre DISPLAY2 parFerme point
;
DISPLAY2: STRING 
| STRING deuxPoints LISTDISPLAY {
     
extractSigneDeFormatage($1 , display2);

if(numOfDisplays!=strlen(display2)) {printf("pour chaque signe de formatage associer un idf \n"); YYERROR;}

display2Length=strlen(display2)-1;

for ( i = 0; i < numOfDisplays; i++)
{
  if(getType(hachTable,display[i])!=  returnTypeFromSigne(display2[display2Length]) ) {printf("signe de formatage incorect %s != %c",display[i],display2[display2Length]);YYERROR;}
  display2Length--;
}
   numOfDisplays=0;
   strcpy(display2,"");
} 
;
LISTDISPLAY: idf bar LISTDISPLAY {
 if(isDeclared(hachTable,$1)!=1) {printf("%s : IDF non declare et utilise !\n",$1);  YYERROR;}

       strcpy(display[numOfDisplays],$1);
      numOfDisplays++;

}
| idf {
 if(isDeclared(hachTable,$1)!=1) {printf("%s : IDF non declare et utilise !\n",$1);  YYERROR;}

     strcpy(display[numOfDisplays],$1);
     numOfDisplays++;
}
;

IF:mc_if parOuvre LOGIC parFerme deuxPoints PROCEDURES1 CASeELSE
;
CASeELSE:mc_else deuxPoints PROCEDURES1 mc_end point | mc_end point
;

MOVE:mc_move idf mc_to idf PROCEDURES1 mc_end point{

  if(isDeclared(hachTable,$2)!=1) {printf("%s : IDF non declare et utilise !\n",$2);YYERROR;  }
  if( getType(hachTable,$2)!=1 ) {printf("%s : idf doit etre de type integer\n",$2);YYERROR;}
  if(isDeclared(hachTable,$4)!=1) {printf("%s : IDF non declare et utilise !\n",$4);YYERROR;  }
  if( getType(hachTable,$4)!=1 ) {printf("%s : idf doit etre de type integer\n",$4);YYERROR;}


  if(getIntegerValue(hachTable,$2)!=32770){ printf("%s : non inisialiser");YYERROR;  }
  if(getIntegerValue(hachTable,$4)!=32770){ printf("%s : non inisialiser");YYERROR;  }

}
|mc_move idf mc_to INTEGER PROCEDURES1 mc_end point{

  if(isDeclared(hachTable,$2)!=1) {printf("%s : IDF non declare et utilise !\n",$2);YYERROR;  }
  if( getType(hachTable,$2)!=1 ) {printf("%s : idf doit etre de type integer\n",$2);YYERROR;}
  if(getIntegerValue(hachTable,$2)!=32770){ printf("%s : non inisialiser");YYERROR;  }

}
;


END:mc_stopRun point
;


%%

int yyerror(char *msg)
{ printf("\n%s error syntaxique",msg);
return 1; }
int main ()
{
verifZero= malloc(sizeof(int)); 
strcpy(display2,"");
initHachTable(hachTable);    
ListMotCles=initList2();
ListNum=initList2();
ListSeparateur=initList2();
   yyin = fopen( "prog.txt", "r" );
   if (yyin==NULL) printf("ERROR in yyin file \n");
   else yyparse();


printHachTable(hachTable);

// printList2(ListSeparateur,"SEPARATEUR");
// printList2(ListMotCles,"MOT CLES");
// printList2(ListNum,"NUM");

hachTableDestroy(hachTable);
destroyList2(&ListMotCles);
destroyList2(&ListNum);
destroyList2(&ListSeparateur);



return 0;
}
int yywrap()
{}
