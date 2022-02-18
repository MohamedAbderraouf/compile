#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h>
#include "TS.h"



/* Creates a list (node) and returns it
 * Arguments: The data the list will contain or NULL to create an empty
 * list/node
 */
list listCreate(int type , char idf[8] , char val[50],int isConst)
{
	list l = malloc(sizeof(list_node));
	if (l != NULL) {
		l->next = NULL;
		strcpy(l->idf,idf);
		strcpy(l->val,val);
        l->type=type;
		l->isConst=isConst;
	}

	return l;
}


list listInsertEnd(list l, int type , char idf[8] , char val[50],int isConst)
{
	list newNode = listCreate(type,idf,val,isConst),it;
	if (newNode != NULL) {

		for(it = l; it != NULL; it = it->next) {
			if (it->next == NULL) {
				it->next = newNode;
				break;
			}
		}
	}
	return l;//newNode old val to ret
}

/* Removes a node from the list
 * Arguments: The list and the node that will be removed
 */
void listRemove(list *l, list node)
{
	list tmp = NULL;
	if (l == NULL || *l == NULL || node == NULL) return;

	if (*l == node) {
		*l = (*l)->next;
		free(node);
		node = NULL;
	} else {
		tmp = *l;
		while (tmp->next && tmp->next != node) tmp = tmp->next;
		if (tmp->next) {
			tmp->next = node->next;
			free(node);
			node = NULL;
		}
	}
}



/* Find an element in a list by the pointer to the element
 * Arguments: A pointer to a list and a pointer to the node/element
 */
list listFindNode(list l, list node)
{
	while (l) {
		if (l == node) break;
		l = l->next;
	}
	return l;
}

/* Finds an elemt in a list by the data pointer
 * Arguments: A pointer to a list and a pointer to the data
 */

list listFindByIdf(list l, char idf[8])
{
	while (l) {
		if (strcmp(idf,l->idf)==0) break;
		l = l->next;
	}
	return l;
}

list listDestroy(list *l ){
list x;

while (*l!=NULL)
{
    x=*l;
    *l=(*l)->next;
    free(x);
}
return NULL;
}

int MAJList (list * l,char idf[8] , char newVal[50] , int type ){

// return values:
// ( 1 = succes ) ( 2 = idf introuvable) ( 3 = CONST) (4 = type incompatible) ( 5 not declared )
list t= *l;
while (t != NULL)
{
    if (strcmp(t->idf,idf)==0){

	  if (t->type==0)
	     return 5;
	  if (t->isConst == 1 && strcmp(t->val,"")!=0)
		return 3;
	  if (t->type != type)
		return 4;  
	  
	   	
      strcpy(t->val,newVal);
      return 1;}
	  t=t->next;   
}
return 2;
}

void InitInfoList(list *l ,char idf[8] , char val[50] , int type ,int isConst){

list t=*l;

while (t != NULL)
{
    if (strcmp(t->idf,idf)==0){
		  strcpy(t->val,val);
          t->type=type;
		  t->isConst=isConst; 
		  break;
		  }
	  t=t->next;   
}
}

long getIntegerValueFromList(list l,char idf[8]){
list t= listFindByIdf(l,idf);
if (strcmp(t->val,"exp math")==0)return 32769;
if (strcmp(t->val,"")==0)return 32770;
else return atoi(t->val);

}
// return values:
// ( 1 = succes ) ( 0 = idf introuvable)

int searchIdf(list l ,char idf[8]){

while (l != NULL)
{
    if (strcmp(l->idf,idf)==0){
      return 1;} 
	  l=l->next;  
}
return 0;

}

// return values (1== declared) (2 == not dec) (0 == not found)

int isDeclaredInList(list l, char idf[8]){

while (l != NULL)
{
    if (strcmp(l->idf,idf)==0){
		return  l->type!=0?1:2;} 
	  l=l->next;  
}
return 0;
}

int getTypeList(list l , char idf[8]){
while (l != NULL)
{
    if (strcmp(l->idf,idf)==0){
		return  l->type;} 
	  l=l->next;  
}
return 0;
}


/* hach table function*/


/*
    65 <= AsciiCount <= 944
	on soustract 60 et on divise sur 10
	pour avoire un tableau de 89 element  

	chaque element du tableau est un pointeur sur 
	une liste chaine
*/

int hachFunction(char str[8]){

int i=0,AsciiCount=0;

for ( i = 0; i <strlen(str); i++)
	AsciiCount+=str[i];

return (AsciiCount-60)/10;

}

void initHachTable(list HT[89]){
int i;
for ( i = 0; i <=88; i++)
   HT[i]=NULL;
}

void hachTableDestroy(list hachTableTs[89]){
int i;
for ( i = 0; i < 89; i++)
  hachTableTs[i]=hachTableTs[i]!=NULL?listDestroy(&hachTableTs[i]):NULL;

}

/*
return values
(1 == succes ) ( 0 == idfNotExist)
*/
int lookup(list hachTableTs[89],char idf[8]){

int index =hachFunction(idf);
if (hachTableTs[index]==NULL)
 return 0;
return searchIdf(hachTableTs[index],idf);

}

void insertIdf(list hachTableTs[89],char idf[8] , char val[50] , int type,int isConst){
int index =hachFunction(idf);

hachTableTs[index]=(hachTableTs[index]==NULL)?listCreate(type,idf,val,isConst):listInsertEnd(hachTableTs[index],type,idf,val,isConst);
}

//return values
// ( 1 = succes ) ( 2 = idf introuvable) ( 3 = type incompatible)
int MAJ (list hachTableTs[89],char idf[8] , char newVal[50] , int type){
int index =hachFunction(idf);
return MAJList(&hachTableTs[index],idf,newVal,type);
}

void InitInfo(list hachTableTs[89] ,char idf[8] , char val[50] , int type ,int isConst){
int index =hachFunction(idf);
InitInfoList(&hachTableTs[index],idf,val,type,isConst);
}

int isDeclared(list hachTable[89],char idf[8]){
int index =hachFunction(idf);
return isDeclaredInList(hachTable[index],idf);

}

long getIntegerValue(list hachTable[89],char idf[8]){
int index =hachFunction(idf);
return getIntegerValueFromList(hachTable[index],idf);

}

int getType(list hachTable[89],char idf[8]){

	int index =hachFunction(idf);
	return getTypeList(hachTable[index],idf);
}

int MajError(int t,char * e){
         switch (t)
         {
         case 1:return 1;
             break;
         case 2:
             printf("%s idf introuvable dans la table TS\n",e);
             break;
         case 3:
             printf("%s valeur constante ne peut etre changer \n",e);
             break;
         case 4:
             printf("%s Type incompatible \n",e);
             break;
         case 5:
             printf("%s idf non declares \n",e);
             break;

         default:
             break;

         }
         return 0;
}



void printList(list l){
	char str[15];
for ( l ; l!=NULL; l=l->next)
    {  strcpy(str,l->idf);countSpaces(str);
		printf("  %s   |",str,l->isConst,l->type,l->val);
		printf("  %s   |",l->isConst==1?"CONST   ":"VARIABLE");
		printf("  %s   |",switchType(l->type));
		printf("  %s \n",l->val);
		
printf("________________________________________________________________________ \n");
    }
}


void printHachTable(list HT[89]){
int i;
printf("\n________________________________________________________________________\n ");

printf("----------------------------TABLE DES IDF------------------------------ \n");
printf("________________________________________________________________________\n ");


printf("   IDF      |  CodeEntite |    Type     |  VALEUR     \n");
printf("________________________________________________________________________ \n");
printf("________________________________________________________________________\n");


for ( i = 0; i <=88; i++)
{
    if (HT[i]!=NULL)
    { 
    printList(HT[i]);
    }
    }
}



list2 initList2(){
return NULL;
}

void insertList2(list2 * t,char val[20]){
list2 newLink=malloc(sizeof(DeuxiemList));
if(newLink==NULL) return;
newLink->next=*t;
strcpy(newLink->val,val);
*t=newLink;
}

int lookupList2(list2 t,char val[20]){
list2 it;
	for ( it =t; it!=NULL; it=it->next)
	{
		if (strcmp(it->val,val)==0)
		{
			return 1;
		}
	}
	return 0;
}

void destroyList2(list2 * t){
list2 tempo;

	while (*t!=NULL)
	{   tempo=*t;
	    free(tempo);
		*t=(*t)->next;
	}
	
}

void printList2(list2 t,char * Type){
printf("\n________________________________________\n");
printf("     TABLE DE SYMBOLE DES %s  \n",Type);
while (t!= NULL)
{
printf("_________________________________________\n");
printf(" %s ====> %s \n",t->val,Type);

    t=t->next;
}
}


void countSpaces(char s[8])
{
	int i;
for ( i = strlen(s); i < 8; i++) s[i]=' ';

s[8]='\0';

}


void RVDR(char * str){
int i ;
for ( i = 0; i <strlen(str); i++)
   {
       if (str[i]==',') {str[i]='.' ; break;}}

}


char* switchType(int type){

	switch (type)
	{
	case 1:
         return "INTEGER ";
		break;
	
		case 2:
         return "FLOAT   ";

		break;
		case 3:
         return "CHAR    ";

		break;
		case 4:
         return "STRING  ";

		break;
		case 5:
         return "TABLEAU ";

		break;
	default:
		break;
	}
	return "NON INIT";
}

int getTypeFromString(char * str){
int i =0;
	if (str[i]=='"') return 4;
	if (str[i]=='\'') return 3 ;
for ( i = 1; i < strlen(str); i++) if (str[i]==',') return 2;	

return 1;
}

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void intToStr(int x , char str[7])
{
  sprintf(str, "%d",x);
} 

void ftoa(float x , char str[10])
{
  sprintf(str, "%f",x);
} 

void clearString(char * str){
	int i;
for ( i = 0; i <strlen(str); i++)
	str[i]=0;


}

int findType(char * str){
int i;
for ( i = 0; i < strlen(str); i++)
{
    if (str[i]=='.') return 2;
}
    return 1;
}

void extractSigneDeFormatage(char * str , char * display){
strcpy(display,"");
int i;
    for ( i = 0; i < strlen(str) ; i++)
     { if (str[i]=='#') strcat(display,"#");
      if (str[i]=='$') strcat(display,"$");
      if (str[i]=='&') strcat(display,"&");
      if (str[i]=='%') strcat(display,"%");}
    
}

int returnTypeFromSigne(char r){

switch (r)
{
case '$' :
	return 1;
	break;

case '%' :
	return 2;
	break;

case '&' :
	return 3;
	break;

case '#' :
	return 4;
	break;

default:
	break;
}
return 0;


}

