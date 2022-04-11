#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void readLines(FILE* fp, char *searchedString){

        char* line = NULL;
        size_t n = 0;
        
        int stringLength;
        stringLength = strlen(searchedString);
        int currentChar;


        while(getline(&line,&n,fp)!=-1){                                                                    //Get line from file
            for(int charInRow=0; charInRow<strlen(line);charInRow++){                                       //Iterate over individual characters of the line
                currentChar = line[charInRow];                                 
                if(currentChar == searchedString[0]){                                                       //If character matches with the beginning of the searched pattern
                    for(int matchedChars = 0; matchedChars<=stringLength; matchedChars++){                  //Begin a loop that gets iterated as many times as there are characters in the searched pattern. 
                        if(matchedChars == stringLength){                                                   //This evaluates to true only when a full match has been found, and we can start printing the line.
                            for(int delimiterChar = 0; delimiterChar<strlen(line);delimiterChar++){         //Print each character from the line and add a marker at the start and end of the matched pattern.
                                if(delimiterChar==charInRow || delimiterChar==stringLength+charInRow){      //Note that my-grep will continue the matching from where it stopped. So a new match is detected even within the matched text.
                                    printf("'");                                                            
                                }
                                printf("%c",line[delimiterChar]);
                            }
                            matchedChars = 0;
                            break;
                        }
                        else if(searchedString[matchedChars] == line[charInRow+matchedChars]){              //This checks if the current character is the same as in the pattern we are matching it to. If it succeeds, we just continue the iteration.
                        }
                        else{                                                                               //If we detect that the current character is not the same as in the pattern we are matching, we'll break out of the loop and continue searching the line.
                            break;
                        }
                    }
                }
            }
            line = NULL;                                                                                    //Line needs to get set to Null before we can get another new line.
        }
}

int main (int argc, char* argv[]){
    if(argc < 2){                                                                                           //Too few arguments invoke an error
        perror("my-grep: searchterm [file ...]\n");
        exit(1);
    }
    char* fileName;
    char searchedString[strlen(argv[1])];

    strcpy(searchedString,argv[1]);

    FILE* fp;

    if(argc == 2){                                                                                          //1 given argument (Just the searched string) uses stdin instead of a file
        fp = stdin;
        readLines(fp,searchedString);                                                                       //readLines takes any file pointer as an argument, so stdin works here.
    }
    else if(argc >= 3){                                                                                     //2 or more given arguments signal that we need to read files. 
        int l = 1;

        while(l <= argc-2){                                                                                 //This loop executes grep for each argument(file) we were given
                    fileName = argv[l+1];

        if((fp = fopen(fileName,"r"))==NULL){                                                               //A file stream gets opened here, it gets closed within readlines().
            perror("my-grep: cannot open file\n");
            exit(0);
        }
        else{
            readLines(fp,searchedString);         
            fclose(fp);                                                                                     //Finally we'll close the stream.                                                          
        }
        l++;
        }
    }
    exit(0);
}