#include <stdlib.h>
#include <string.h>
#include "TS.h"



/* Creates a list (node) and returns it
 * Arguments: The data the list will contain or NULL to create an empty
 * list/node
 */
list listCreate(int type , char idf[8] , char val[50])
{
	list l = malloc(sizeof(list_node));
	if (l != NULL) {
		l->next = NULL;
		strcpy(l->idf,idf);
		strcpy(l->val,val);
        l->type=type;
	}

	return l;
}


list listInsertEnd(list l, int type , char idf[8] , char val[50] )
{
	list newNode = listCreate(type,idf,val),it;
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
		if (l->idf == idf) break;
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

int MAJList (list * l,char idf[8] , char newVal[50] , int type){

// return values:
// ( 1 = succes ) ( 2 = idf introuvable) ( 3 = type incompatible)

while (*l != NULL)
{
    if (strcmp((*l)->idf,idf)==0){

	  if ((*l)->type != type)
	  {
		return 3;  
	  }
	   	
      strcpy((*l)->val,newVal);
      return 1;}
	  *l=(*l)->next;   
}
return 2;
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

void insertIdf(list hachTableTs[89],char idf[8] , char val[50] , int type){
int index =hachFunction(idf);

hachTableTs[index]=(hachTableTs[index]==NULL)?listCreate(type,idf,val):listInsertEnd(hachTableTs[index],type,idf,val);
}

//return values
// ( 1 = succes ) ( 2 = idf introuvable) ( 3 = type incompatible)
int MAJ (list hachTableTs[89],char idf[8] , char newVal[50] , int type){
int index =hachFunction(idf);
return MAJList(&hachTableTs[index],idf,newVal,type);
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




