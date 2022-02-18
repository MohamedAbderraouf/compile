#ifndef _POST_H
#define _POST_H


char* format_formula(char* formula);
char* get_postfix_formula(char *formula);
int calculate(char *formula);
char* remove_element_by_index(char* formula, int index);
int is_number(char c);
int is_operator(char c);


#endif
