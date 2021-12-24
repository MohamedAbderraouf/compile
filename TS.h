#ifndef _TS_H
#define _TS_H

/****************************************************************/
/*        TABLE DE SYMBOLE DES VARIABLE ET CONSTANTE            */
/****************************************************************/


// pour la var type :
// (1= integer) (2= float) (3= char) (4= string) (0 = non Initialiser)
typedef struct list_node {
	int type;
  char idf[8],val[50];
	struct list_node *next;
} list_node;

typedef struct list_node  *list;

/***************/
/* linked list */
list listCreate(int type , char idf[8] , char val[50]);
list listInsertEnd(list l ,int type , char idf[8] , char val[50]);
void listRemove(list *l, list node);
list listFindNode(list l, list node);
list listFindByIdf(list l, char idf[8]);
list listDestroy(list * l);
int MAJList (list *l ,char idf[8] , char newVal[50] , int type);
int verifCompatibilite(int type,char newVal[50]);
int searchIdf(list l ,char idf[8]);



/***************/
/* hach table  */
int hachFunction(char str[8]);
void initHachTable(list HT[89]);
void hachTableDestroy(list hachTableTs[89]);
int lookup(list hachTableTs[89],char idf[8]);
int modifyIdfData(list hachTableTs[89]);
void insertIdf(list hachTableTs[89],char idf[8] , char newVal[50] , int type);
int MAJ (list hachTableTs[89],char idf[8] , char newVal[50] , int type);


/****************************************************************/
/*        TABLE DE SYMBOLE DES SEPARATEUR ,MOT CLES ET NUM      */
/****************************************************************/
//remarque : on 2 table une pour chaque

typedef struct DeuxiemList {
    char val[20];
	struct DeuxiemList *next;
} DeuxiemList;

typedef struct DeuxiemList  *list2;

list2 initList2();
void insertList2(list2 *t,char val[20]);
int lookupList2(list2 t,char val[20]);
void destroyList2(list2 * t);



#endif

