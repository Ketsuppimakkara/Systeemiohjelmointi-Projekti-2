#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char* argv[]){
    FILE* fp;
    if (argc< 2){
        perror("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    else{
        for(int f = 1; f<argc;f++){                                     //This iterates over every file we were given as arguments
            if((fp = fopen(argv[f],"r"))==NULL){
                perror("error opening file!\n");
                exit(1);
            }

            char* line = NULL;
            size_t n;
            int consecutiveCharacters = 1;
            char currentCharacter;

            while(getline(&line,&n,fp)!=-1){                            //This iterates over every line in the current file.
                for(int i=0;i<strlen(line);i++){                        //This iterates over every character in the current line.
                    currentCharacter = line[i];
                    if(line[i+1]==line[i]){                             //This detects if there are multiple instances of the same character sequentially, and increments the consecutiveCharacters counter.
                        consecutiveCharacters++;
                    }
                    else{                                               //Once there is no more consecutive characters, it's time to write the 5-byte segment into the file. The first 4 bytes are an integer (sizeof(int) == 4), followed by 1 byte character(sizeof(char) == 1)
                        fwrite(&consecutiveCharacters,sizeof(int),1,stdout);
                        fwrite(&currentCharacter,sizeof(char),1,stdout);
                        consecutiveCharacters = 1;                      //Then we'll reset the consecutiveCharacters counter.
                    }
                }
                line = NULL;
            }
        }
            fclose(fp);                                                 //Stream gets closed after all files have been written.
    }
    exit(0);
}