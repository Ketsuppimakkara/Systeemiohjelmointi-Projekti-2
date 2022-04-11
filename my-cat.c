#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main (int argc, char* argv[]){

    char* fileName;
    char* line = NULL;
    size_t n = 0;
    FILE* fp;

    if(argc < 2){                                       //No files given, my-cat will just exit
        exit(0);
    }
    else{
        for(int i = 1; i<argc;i++){                     //This loop handles multiple files
            fileName = argv[i];

            if((fp = fopen(fileName,"r"))==NULL){       //Open the file
                perror("my-cat: cannot open file\n");
                exit(1);
            }
            else{
            while(getline(&line,&n,fp)!=-1){            //We use getline here to avoid any issues with a buffer that's too small
                printf("%s",line);
                line = NULL;                            //line needs to be set to NULL before calling getLine again.
            }
            fclose(fp);                                 //Close the stream
            }
        }
    }
    exit(0);
}