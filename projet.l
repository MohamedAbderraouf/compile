%{  
#include<stdio.h>	
#include<string.h> 
#include"projet.tab.h"
#include"TS.h"
void printError(int numLine,int col);  
extern nb_ligne ,i ,Cl ,f;
extern YYSTYPE yylval;

extern hachTable[89];
extern ListMotCles;
extern ListNum ;
extern ListSeparateur;
%}

IDF [A-Z][a-z0-9]+
commentaire "#"(.|\n)+"!"
INTEGER \([-+][1-9][0-9]*\)|[1-9][0-9]*|0
REAL \([+-][1-9][0-9]*\,[0-9]*[1-9]\)|[1-9][0-9]*\,[0-9]*[1-9]|\([+-]0\,[0-9]*[1-9]\)|0\,[0-9]*[1-9]
CHAR \'.?\'|\'"\n"\'|\'"\0"\'
STRING \"[^"]*\"


%%

IDENTIFICATION {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_identification;}
DIVISION {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_division; }
PROGRAM-ID {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_programId; }
DATA {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext);  return mc_data;}
WORKING-STORAGE {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext);return mc_workingStorage;}
SECTION {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_section;}
PROCEDURE {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_procedure;}
STOP" "RUN {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_stopRun;}

SIZE {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext);  return size;}
LINE {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return line;}

INTEGER {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); yylval.str=strdup(yytext); return mc_integer; }
FLOAT {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); yylval.str=strdup(yytext); return mc_real;}
CHAR {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); yylval.str=strdup(yytext); return mc_char;}
STRING {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); yylval.str=strdup(yytext); return mc_string;}
CONST {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext);  return mc_const;}

{commentaire} {
   for (f = 0; f < yyleng; f++)
    if(yytext[f]=='\n') nb_ligne++; 
}

\| {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext); return bar;}
\( {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext); return parOuvre ;}
\) {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext); return parFerme;}
\. {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext); return point;}
\, {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext); return virgule;}
[ \t] Cl+=yyleng;
= {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext);  return egal;}
\+ {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext); return plus;}
- {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext);  return moin;}
\/ {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext); return divi; }
\* {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext); return mul; }
\n {Cl=0; nb_ligne++;}
AND {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_and; }
OR {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_or; }
NOT {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_not; }
LE {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_le;}
GE {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_ge;}
G {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_g;}
L {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_l;}
EQ {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext);return mc_eq; }
DI {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_di;}
\@ {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext); return arob; }
\: {if(lookupList2((list2)ListSeparateur,yytext)==0){insertList2((list2 *)&ListSeparateur,yytext);} Cl+=strlen(yytext); return deuxPoints; }


IF {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext);  return mc_if;}
ELSE  { if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext);  return mc_else;}
END {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_end ; }

ACCEPT {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_accept; }
DISPLAY {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext); return mc_display;}
MOVE {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext);  return mc_move;}
to {if(lookupList2((list2)ListMotCles,yytext)==0){insertList2((list2 *)&ListMotCles,yytext);} Cl+=strlen(yytext);   return mc_to;}

{IDF} {if(strlen(yytext)>8){ printf("\nerreur lexicale : l'IDF > 8 caractères"); printError(nb_ligne,Cl); return err;}
 
 if(lookup((list*)hachTable,yytext)==0)insertIdf((list*)hachTable,yytext,"", 0,1);

 Cl+=strlen(yytext); yylval.str=strdup(yytext); return idf; }

{REAL} {if(lookupList2((list2)ListNum,yytext)==0){insertList2((list2 *)&ListNum,yytext);} Cl+=strlen(yytext); RVDR(yytext); yylval.real=atof(yytext);  return REAL;}
{CHAR} {Cl+=strlen(yytext); yylval.str=strdup(yytext); return CHAR;}
{STRING} {Cl+=strlen(yytext); yylval.str=strdup(yytext); return STRING;}
{INTEGER}   {
	if(yytext[0]!='(')
	    {if(atoi(yytext)<0||atoi(yytext)>32767)
	     { printf("\nerreur lexical entier depasse la limite\n");
          printError(nb_ligne,Cl);
	      return err;	}
		}

	else
	    {
			 while(yytext[i]!=')')
				{
		        yytext[i]=yytext[i+1];
                i++;
				}
        yytext[i]='\0';yytext[i-1]='\0';
				
        if(atoi(yytext)<-32767||atoi(yytext)>32767)
		            {printf ("\nerreur lexical entier depasse la limite\n");
					printError(nb_ligne,Cl);
					return err;}			
		}

		i=0;
        yylval.integer=atoi(yytext);
        if(lookupList2((list2)ListNum,yytext)==0){insertList2((list2 *)&ListNum,yytext);}
		return INTEGER;

	}    


. {printError(nb_ligne,Cl);return err;
     }
%%

void printError(int numLine,int col ){
FILE * file = fopen("prog.txt","r");
size_t len = 0;
char str[200];
int i,verif=0;

for (i = 0; i < numLine; i++)
    fgets(str,200,file);

int colEnd=col;
while (str[colEnd]!='\n' && colEnd!=strlen(str))
     {
         if(str[colEnd]==' ' || str[colEnd]=='(' 
         || str[colEnd]==')' || str[colEnd]=='.')
          break;
         colEnd++;}


if (colEnd==strlen(str))
 {str[colEnd]='\n';
str[colEnd+1]='\0';}
else if (str[strlen(str)-1]!='\n') verif=1;


         

char err[col+colEnd+8];
if (verif==1)
{
    err[0]='\n';
    for ( i = 1; i < (col+6) ; i++)
     err[i]=' ';
for ( i = col+6 ; i < colEnd+6 ; i++)
     err[i]='^';
err[colEnd+6]='\0';
}
else
{
for ( i = 0; i < (col+4) ; i++)
     err[i]=' ';
for ( i = col+4 ; i < colEnd+4 ; i++)
     err[i]='^';
err[colEnd+4]='\0';}

printf("\nerreur lexical a la ligne %d sur la colonne %d \n",numLine,col);
printf(":::> %s ",str);
printf("%s",err);

fclose(file);

}




