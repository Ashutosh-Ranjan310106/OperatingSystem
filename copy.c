#include <stdio.h>


int main(int argc, char *argv[]){
    for (int i = 0; i < argc; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");
    if (argc != 3){
        printf("Usage: <source_file> <destination_file>\n");
        return 1;
    }
    FILE *sptr, *dptr;
    sptr = fopen(argv[1],"r");
    dptr = fopen(argv[2], "r");
    char ch;
    int paste = 1;


    ch = fgetc(dptr);
    if (ch != EOF){
        paste = 0;
        printf("destination file already have data do you want to replace old data (Y/N):- ");
        char i;
        scanf("%c",&i);
        if (i == 'Y' || i == 'y'){
            paste = 1;
        }
    }

    if (paste == 1){
        fclose(dptr);
        dptr = fopen(argv[2], "w");
    }

    while (paste){
        ch = fgetc(sptr);
        if (ch == EOF){
            break;
        }
        fputc(ch, dptr);
    }

    
    printf(" ");
    fclose(sptr);
    fclose(dptr);
    return 0;
}
