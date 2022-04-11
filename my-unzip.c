#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char* argv[]){
    FILE* fp;
    int luku;
    char kirjain;

    if (argc< 2){
        perror("too few arguments!\n");
        exit(1);
    }
    else{
        if((fp = fopen(argv[1],"rb"))==NULL){
            perror("error opening file!\n");
            exit(1);
        }

        fseek(fp,0,SEEK_END);
        int size = (ftell(fp)/5);
        rewind(fp);

        for(int i = 0; i<size;i++){
            fread(&luku,sizeof(int),1,fp);
            fread(&kirjain,sizeof(char),1,fp);
            for(int j = 0; j<luku;j++){
                fprintf(stdout,"%c",kirjain);
            }
        }

 
        }
        fclose(fp);
        exit(0);
}