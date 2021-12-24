#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include<ctype.h>
#include "fonction.h"
#include <time.h>



  float depilerf(pilef *p )
  {  pilef temp;         
      float x = (*p)->nf;
      temp=*p;
     (*p)=(*p)->svt;
      free(temp);
      return x;
  }

  pilef empilerf(pilef pf,float f){
   pilef nouv;
   int i=0;
       nouv=malloc(sizeof(cellef));
       if (nouv==NULL)
       {
           printf("pas d'espace");
           exit(EXIT_FAILURE);
       }
       nouv->nf=f;
       nouv->svt=pf;
       return nouv;
  }
  pilef intpilef(pilef p){p=NULL;
  return p;
  }

  bool pilevidef(pilef p)
  {
      return p==NULL?true:false;
  }

pileT empilerT(pileT p,char *x){
   pileT nouv;
   int i=0;
       nouv=malloc(sizeof(Celle));
       if (nouv==NULL)
       {
           printf("pas d'espace");
           exit(EXIT_FAILURE);
       }
        while (x[i]!='\0')
        {
         nouv->inf[i]=x[i];
         i++;
        }
        nouv->inf[i]='\0';
       nouv->svt=p;
       return nouv;
  }

  
  pileT intpileT(pileT p){p=NULL;
  return p;
  }

  bool pilevideT(pileT p)
  {
      return p==NULL?true:false;
  }

  char* sommetpileT(pileT p ) {return p->inf;}



  void depilerT(pileT *p , char *x )
  {  pileT temp;
     int i=0;
     while ((*p)->inf[i]!='\0')
     {
         x[i]=(*p)->inf[i];
         i++;
     }     
     x[i]='\0';
     temp=*p;
     (*p)=(*p)->svt;
     free(temp);
  }
  
pile empiler(pile p,char x){
   pile nouv;
       nouv=malloc(sizeof(pille));
       if (nouv==NULL)
       {
           printf("pas d'espace");
           exit(EXIT_FAILURE);
       }
        nouv->info=x;
       nouv->svt=p;
       return nouv;
  }


  char depiler(pile *p )
  {  pile temp;
     char x;
      x=(*p)->info;
      temp=*p;
      (*p)=(*p)->svt;
      free(temp);
     return x;
  }


  bool pilevide(pile p)
  {
      return p==NULL?true:false;      
  }


  pile intpile(pile p){p=NULL;
  return p;
  }

  char sommetpile(pile p ) {return p->info;}

//rmspace to remoove spaces in case
void rmSpace(char *s)
{
	int  i,k=0;

	 for(i=0;s[i];i++)
    {
            s[i]=s[i+k];


            if(s[i]==' ')
            {
                k++;
                i--;
            }

        }
}

int putInTable( char *s,pointTab table)
{

    bool cond;
    int i=0,j,t=0;
    while (s[i]!='\0')
    {  
        cond=false;
        if (s[i]=='(' || s[i]==')' ||  s[i]=='/' || s[i]=='*' || s[i]=='%' )
        {
            table[t].info[0]=s[i];
            table[t].info[1]='\0';
            t++;
            cond=true;
        }
        if(s[i]=='+' || s[i]=='-')
        {
             if (s[i-1]!='+' && s[i-1]!='-' && s[i-1]!= '*' && s[i-1]!='/' &&  s[i-1]!= '(' && s[i]!='%')
            {
                 table[t].info[0]=s[i];
                 table[t].info[1]='\0';   
            }
            else 
            {
                table[t].info[0]=s[i];
                i++;
                j=i;
                 while ( isdigit(s[i])!=0 || s[i]=='.' )
                {
                    i++;
                }
              
                 int m=1;
                for ( j; j < i; j++)
                {
                     table[t].info[m]=s[j];
                     m++;
                }
                     table[t].info[m]='\0';
                     i--;
                  }
                    cond=true;
                    t++;    
        }

        if (isdigit(s[i])!=0 && cond==false )
        {
                j=i;
            while (  s[i]=='.' || isdigit(s[i])!=0 )
            {
                i++;
            }
            int m=0;
            for ( j; j < i; j++)
            {
                 table[t].info[m]=s[j];
                 m++;
            }
            table[t].info[m]='\0';
                cond=true;
                t++;
                i--;
            }
        i++;
    }

  return t;
}


bool verifPar(char *t)
{

   char x;
   int i=0;
   pile p=intpile(p);
   bool v=true;
   while(t[i]!='\0' && v==true)
   {
     if (t[i]=='(')
       p=empiler(p,t[i]);
     else if (t[i]==')')
     {
      if (pilevide(p)==true)  return false;
      else x= depiler(&p);

     }

     i++;
   }
   if ( !pilevide(p) )return false ;

     return v;

}


bool operateur(char *c)
{
    if(c[0]=='+'||c[0]=='/'||c[0]=='*'||c[0]=='%')
      return true;
   
    if (c[0]=='-' && isdigit(c[1])==0 )
      return true;   
   
    return false;
}


bool operand(char *x)
{
 bool v;
 v =isdigit(x[0])!=0?true:false;
 if(v==false)
   return isdigit(x[1])!=0?true:false;
 return v;
}

int priorite(char *x){
if(operateur(x)==true)
   if(x[0]=='+'|| x[0]=='-')
      return 1;
    else return 2;
}



float operation(float a,float b,char *c){
 if(operateur(c)==true){
    if(c[0]=='+') return a+b;
    if(c[0]=='-') return a-b;
    if(c[0]=='/') return a/b;
    if(c[0]=='%') return fmod(a,b);
    if(c[0]=='*') return a*b;
   }

}



pileT transformation(tab t[1024],int taille)
{
    pileT p=intpileT(p),r=intpileT(r);
    int i=0;
    char x[50];
    for(i=0;i<taille;i++)
    {
        if(operand(t[i].info)==true)r=empilerT(r,t[i].info);
        if(t[i].info[0]=='(')p=empilerT(p,"(");
        if(operateur(t[i].info)==true)
        {
            while(pilevideT(p)==false&&operateur(sommetpileT(p))==true&&priorite(t[i].info)<=priorite(sommetpileT(p)))
            {
                depilerT(&p,x);
                r=empilerT(r,x);
            }
            p=empilerT(p,t[i].info);
        }
        if(t[i].info[0]==')')
        {
            while(pilevideT(p)==false && p->inf[0]!='(')
            {
                depilerT(&p,x);
                r=empilerT(r,x);
            }
            depilerT(&p,x);
        }
    }
    while(pilevideT(r)==false)
    {
       depilerT(&r,x);
        p=empilerT(p,x);
    }
    return p;
}

void verifMul(char *s)
{
int i=0,j;

while (s[i]!='\0')
{
    if (s[i]=='(')
    {
        if(s[i-1]==')' || isdigit(s[i-1]))
        {
        j=i;
        while (s[j]!='\0')
        {
          j++;
        }
        s[j+1]='\0';
        while (j>i)
        {
            s[j]=s[j-1];
            j--;
        }
       s[i]='*';
      }
    }
    i++;
}
}

float resultatfinal(pileT p)
{
  pilef r=intpilef(r); 
 float a,b;
 char inter[50];

 while (!pilevideT(p))
 {
  depilerT(&p,inter);
  if (operand(inter))
  {
    r=empilerf(r,atof(inter));
  }
  if (operateur(inter))
  {
    a= depilerf(&r);
    b= depilerf(&r);
    r=empilerf(r,operation(b,a,inter));
  }
   
 }

 return depilerf(&r);
}


void delay(int nombre) 
{ 
    int milli_seconds = 1000 * nombre; 
  
    clock_t start_time = clock(); 
  

    while (clock() < start_time + milli_seconds) {}  
} 

void greeting()
{
printf("|     |  -----  |        | by:                  \n");delay(1);
printf("|     | |       |        | mohamed ------     \n");delay(1);
printf(" -----   -----  |        | soheib |      |    \n");delay(1);
printf( "|     | |c c    |        | yacin  |      |    \n");delay(1);
printf(  "|     | | ~     |        | aymen  |      |    \n");delay(1);
printf(" :) ;)   -----   -----    ------   ------     \n");delay(1);
}

float countExp(char * exp){

 tab table[1024];
     int tailleTab;
     char s[1024];
     strcpy(s,exp);

     rmSpace(s);
     verifMul(s);
     tailleTab =putInTable(s,table);
     char x[50];
     pileT p=intpileT(p);
     p=transformation(table,tailleTab);    
     float o;
     o=resultatfinal(p);
     return o;
     
}


