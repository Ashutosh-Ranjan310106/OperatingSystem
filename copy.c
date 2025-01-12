#include <stdio.h>


int main(){
    FILE *sptr, *dptr;
    sptr = fopen("a.txt","r");
    dptr = fopen("b.txt", "r");
    char ch;
    int paste = 1;


    ch = fgetc(dptr);
    if (ch != EOF){
        paste = 0;
        printf("destination file already have data do you want to replace old data (Y/N):- ");
        char i;
        scanf("%c",&i);
        if (i == 'Y'){
            paste = 1;
        }
    }

    if (paste == 1){
        fclose(dptr);
        dptr = fopen("b.txt", "w");
    }

    while (paste){
        ch = fgetc(sptr);
        if (ch == EOF){
            break;
        }
        fputc(ch, dptr);
    }

    
    printf("");
    fclose(sptr);
    fclose(dptr);
    return 0;
}