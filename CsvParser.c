#include "CsvParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct csvDoc *parseCsvFile(const char *fileName){

    struct csvDoc *result = NULL;
    struct csvDoc *usingNode = NULL;
    char line[256];
    int lineCount=0;

    FILE *file = fopen(fileName, "r");
    if (file != NULL)
    {

        while (fgets(line, sizeof(line), file)) {
            if(result == NULL){

                result = (struct csvDoc*)malloc(sizeof(struct csvDoc));
            
                getContentFromFile(line, result);

                usingNode = result;

            }else{
                usingNode->next = (struct csvDoc*)realloc(usingNode->next,(lineCount +1 ) * sizeof(struct csvDoc));

                getContentFromFile(line, usingNode->next);
                usingNode = usingNode->next;
                usingNode->next = NULL; //Ultimo

            }
            lineCount++;
        }

        fclose(file);
    }

    #if DEBUG_PARSER
        revisaLoParseado(result);
    #endif

    return result;

}

void revisaLoParseado(struct csvDoc *result){

    struct csvDoc *nodoUso = result;

    do{

        if(nodoUso != NULL){
            for(int i =0 ; i<nodoUso->contentsCount ; i++){
                printf("%d Valor %s\n",i,nodoUso->content[i]);
            }
            printf("\n");
            nodoUso = nodoUso->next;

        }

    }while(nodoUso!= NULL);

}

void getContentFromFile(char *line,struct csvDoc *doc){

    char *token;
    int lineLenght = 0;
    char *lineCopy = NULL;

    lineCopy = (char*) malloc(strlen(line) * sizeof(char));
    sprintf(lineCopy,"%s",line);
    
    doc->contentsCount = 0;

    token = strtok(lineCopy, ";");

    while (token != NULL && token[0]!='\n') {
        lineLenght = strlen(token);

        if(doc->contentsCount == 0){
            doc->content = (char **)malloc(sizeof(char *));
            
        }else{
            doc->content = (char **)realloc(doc->content,(doc->contentsCount +1) * sizeof(char *));
        }

        doc->content[doc->contentsCount] = (char*)malloc(lineLenght * sizeof(char));
        sprintf( doc->content[doc->contentsCount],"%s",token);
        doc->contentsCount++;

        token = strtok(NULL, ";");
    }
}

unsigned char writeCsvFile(const char* fileName,struct csvDoc *doc ){

    struct csvDoc *nodoUso = doc;
    char line[20000] = "";
    char auxValue[200] = "";
    unsigned char result = SUCCESS_WRITECSV;

    FILE *file = fopen(fileName, "w");

    if (file != NULL && doc != NULL)
    {
        while (nodoUso != NULL) {

            line[0] = '\0';

            for (int i = 0; i < nodoUso->contentsCount; i++) {
                if (nodoUso->content[i] != NULL) {

                    snprintf(auxValue, sizeof(auxValue), "%s;", nodoUso->content[i]);
                    //printf("Aux value -%s-, current line -%s-\n", auxValue, line);

                    if (strlen(line) + strlen(auxValue) < sizeof(line)) {
                        strcat(line, auxValue);
                    } else {
                        printf("Línea demasiado larga para concatenar.\n");
                        break;
                    }
                }
            }
            fprintf(file, "%s\n", line);
            nodoUso = nodoUso->next;
        }
        fclose(file);
    }else{
        result = ERROR_WRITECSV;
    }

    return result;
}