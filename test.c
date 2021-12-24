#include<stdio.h>
#include<stdlib.h>
#include "TS.h"


void printList(list2 l){
for ( l ; l!=NULL; l=l->next)
    printf( " ==> %s \n",l->val);

}

// void printHachTable(list HT[88]){
// int i;
// for ( i = 0; i <=88; i++)
// {
//     if (HT[i]!=NULL)
//     {
//     printf("i==%d::: \n",i);    
//     printList(HT[i]);
//     }
    
// }


//}

int main()
{ 

list2 table = initList2();
insertList2(&table , "val1");
 insertList2(&table , "val2");
 insertList2(&table , "val3");
 insertList2(&table , "val4");
  insertList2(&table , "val5");

printList(table);
destroyList2(&table);
printList(table);



    return 0;
}
// list hachTable[89];
// initHachTable(hachTable);

// insertIdf(hachTable,"A","val A",3);
// insertIdf(hachTable,"Fer","val Fer",4);
// insertIdf(hachTable,"B","val B",5);
// insertIdf(hachTable,"Zzzzzzzz","val B",5);

// printf(" lookup %d \n",lookup(hachTable,"Fer"));    

// printHachTable(hachTable);

// printf("\n MAJ %d \n",MAJ(hachTable,"A","hello",4));    

// printHachTable(hachTable);


// hachTableDestroy(hachTable);



