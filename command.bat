flex .\%1.l
bison -d .\%1.y
gcc .\lex.yy.c .\%1.tab.c .\TS.c .\POST.c -lfl -ly
.\a.exe