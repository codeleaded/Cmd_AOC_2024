#include <stdio.h>
#include "C:\Wichtig\System\Static\Library\Int_Parser.h"
#include "C:\Wichtig\System\Static\Library\Files.h"
#include "C:\Wichtig\System\Static\Library\Math.h"

#define Number  unsigned long long

void* Create(char* cstr){
    Number a = Number_Parse(cstr);
    void* Data = malloc(sizeof(Number));
    memcpy(Data,&a,sizeof(Number));
    return Data;
}
int Cmp(void* e1,void* e2){
    Number a = *(Number*)e1;
    Number b = *(Number*)e2;
    return a<b?1:(a>b?-1:0);
}

int main(){
    
    char* Data = Files_Read("C:/Wichtig/Hecke/C/Cmd_AOC_2024/01_12_2024/Part2/Data");
    Vector Parts = Parser_StreamtoParts(Data);
    Vector Numbers = Parser_buildTo(&Parts,sizeof(Number),Create,free);

    Vector_BubbleSortStep(&Numbers,0,Numbers.size-1,2,Cmp);
    Vector_BubbleSortStep(&Numbers,1,Numbers.size,2,Cmp);

    Number TotalDiff = 0;
    for(int i = 0;i<Numbers.size/2;i++){
        Number n1 = *(Number*)Vector_Get(&Numbers,i*2);
        Number n2 = *(Number*)Vector_Get(&Numbers,i*2+1);

        Number nmin = I64_min(n1,n2);
        Number nmax = I64_max(n1,n2);

        Number Diff = nmax - nmin;
        TotalDiff += Diff;

        printf("%d -> N1: %llu, N2: %llu, Diff: %llu, TotalDiff: %llu |\n",i,n1,n2,Diff,TotalDiff);
    }

    printf("TotalDiff: %llu |\n",TotalDiff);

    Vector_Free(&Numbers);
    Parser_freeParts(&Parts);
    //Vector_Free(&Parts);
    free(Data);
    
    return 0;
}