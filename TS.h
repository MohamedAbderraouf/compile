#ifndef _TS_H
#define _TS_H

/****************************************************************/
/*        TABLE DE SYMBOLE DES VARIABLE ET CONSTANTE            */
/****************************************************************/


// pour la var type :
// (1= integer) (2= float) (3= char) (4= string) ( 5 == tableau) (6 == exp) (0 = non Initialiser)
typedef struct list_node {
	int type;
	int isConst; 
  char idf[8],val[50];
	struct list_node *next;
} list_node;

typedef struct list_node  *list;

/***************/
/* linked list */
list listCreate(int type , char idf[8] , char val[50],int isConst);
list listInsertEnd(list l ,int type , char idf[8] , char val[50],int isConst);
void listRemove(list *l, list node);
list listFindNode(list l, list node);
list listFindByIdf(list l, char idf[8]);
list listDestroy(list * l);
int MAJList (list *l ,char idf[8] , char newVal[50] , int type );
int isDeclaredInList(list l, char idf[8]);
void InitInfoList(list *l ,char idf[8] , char val[50] , int type ,int isConst);
int searchIdf(list l ,char idf[8]);
int getTypeList(list l , char idf[8]);
long getIntegerValueFromList(list l,char idf[8]);


/***************************/
/*      fonction util      */

void countSpaces(char s[15]);
void RVDR(char * str);
char* switchType(int type);
void ftoa(float x, char str[10]);
void intToStr(int x , char str[7]);
void reverse(char* str, int len);
void clearString(char * str);
int findType(char * str);
void extractSigneDeFormatage(char * str , char * display);
int returnTypeFromSigne(char r);


/***************/
/* hach table  */
int hachFunction(char str[8]);
void initHachTable(list HT[89]);
void hachTableDestroy(list hachTableTs[89]);
int lookup(list hachTableTs[89],char idf[8]);
void insertIdf(list hachTableTs[89],char idf[8] , char newVal[50] , int type,int isConst);
int MAJ (list hachTableTs[89],char idf[8] , char newVal[50] , int type);
void InitInfo(list *l ,char idf[8] , char val[50] , int type ,int isConst);
int MajError(int t,char * str);
void printHachTable(list hachTableTs[89]);
int isDeclared(list hachTable[89],char idf[8]);
int getType(list hachTable[89],char idf[8]);
long getIntegerValue(list hachTable[89],char idf[8]);

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
void printList2(list2 t,char * Type);


#endif

