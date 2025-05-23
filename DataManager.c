#include "DataManager.h"
#include "CsvParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


RESOURCE_DATA_VECTOR dataBaseInfo;

void startUpDataBase(){

    dataBaseInfo.dataVector = NULL;
    dataBaseInfo.dataResourcesCount =0;

    if(checkDataBase()){

        getDataFromDataBase();
    }
}

unsigned char requestInfo(){
    
    printf("Request Info Stuff\n");
    unsigned char result = SUCCESS_DATABASE_OPERATION;
    char resouceName[200];

    if(!checkDataBase()){
        proccessDataBaseDoesntExist();
    }else{
        printf("Inserta el nombre de recurso que deseas consultar : ");
        scanf("%s", resouceName);

        showSelectedResourceInfo(resouceName);
    }

    return result;
}

void showSelectedResourceInfo(char *name){

    unsigned char found = 0;

    for(int i = 0 ; i < dataBaseInfo.dataResourcesCount; i++){
        if(strcmp(dataBaseInfo.dataVector[i].name, name)==0){
            found = 1;

            printf("Nombre -> %s , Enlace -> %s , Tipo -> %s\n",
            dataBaseInfo.dataVector[i].name,dataBaseInfo.dataVector[i].link,dataBaseInfo.dataVector[i].type);

            break;
        }
    }

    if(found == 0){
        char input;
        printf("No existe el recurso, ¿desea introducrlo?[s/n]\n");
        scanf("%c",&input);

        if(input == 's'){
            insertInfo();
        }

    }
}

unsigned char insertInfo(){

    unsigned char result = SUCCESS_DATABASE_OPERATION;

    RESOURCE_DATA insertData;

    printf("Introduzca los datos de insercion:\nNombre : ");
    scanf("%s",insertData.name);

    printf("\nEnlace : ");
    scanf("%s",insertData.link);

    printf("\nTipo : ");
    scanf("%s",insertData.type);
    printf("\n");

    //TODO : Check if exists

    if(addData2DataVector(&insertData) != SUCCESS_DATABASE_OPERATION){
        result = ERROR_DATABASE_OPERATION;
    }

    return result;

}

unsigned char addData2DataVector(RESOURCE_DATA* data2Insert){

    unsigned char result = SUCCESS_DATABASE_OPERATION;

    if(dataBaseInfo.dataResourcesCount == 0){
        dataBaseInfo.dataResourcesCount++;
        dataBaseInfo.dataVector = (RESOURCE_DATA *)malloc(sizeof(RESOURCE_DATA));
    }else{
        dataBaseInfo.dataResourcesCount++;
        dataBaseInfo.dataVector = (RESOURCE_DATA *)realloc(dataBaseInfo.dataVector,dataBaseInfo.dataResourcesCount * sizeof(RESOURCE_DATA));
    }   

    sprintf(dataBaseInfo.dataVector[dataBaseInfo.dataResourcesCount -1 ].name,"%s",data2Insert->name);
    sprintf(dataBaseInfo.dataVector[dataBaseInfo.dataResourcesCount -1 ].link,"%s",data2Insert->link);
    sprintf(dataBaseInfo.dataVector[dataBaseInfo.dataResourcesCount -1 ].type,"%s",data2Insert->type);

    return result;

}

unsigned char deleteInfo(){

    unsigned char result = SUCCESS_DATABASE_OPERATION;
    char deletedResourceName[300]="";

    printf("Introduzca el nombre del recurso que desea borrar\n");
    scanf("%s",deletedResourceName);

    if(resourceFound(deletedResourceName) == ERROR_RESOURCE_NOT_FOUND){
        result = ERROR_RESOURCE_NOT_FOUND;
    }else{
        deleteResourceFromDataVector(deletedResourceName);
    }

    return result;

}

unsigned resourceFound(char *resourceName){

    unsigned char result = ERROR_RESOURCE_NOT_FOUND;

    for(int i = 0 ; i < dataBaseInfo.dataResourcesCount; i++){
        if(strcmp(dataBaseInfo.dataVector[i].name, resourceName)==0){
            
            result = RESOURCE_FOUND;
            break;
        }
    }
    return result;
}   

void deleteResourceFromDataVector(char *resourceName){

    int deletedResourceIndex = -1;

    for(int i = 0 ; i < dataBaseInfo.dataResourcesCount; i++){
        if(strcmp(dataBaseInfo.dataVector[i].name, resourceName)==0){
            
            deletedResourceIndex = i;
            break;
        }
    }

     // Mover los elementos desde el índice 3 al índice 2
    //memmove(&array[2], &array[3], 2 * sizeof(MyStruct));
    //memmove(&dataBaseInfo.dataVector[deletedResourceIndex],&dataBaseInfo.dataVector[deletedResourceIndex+1],dataBaseInfo.dataResourcesCount - (deletedResourceIndex +1));
    memcpy(&dataBaseInfo.dataVector[deletedResourceIndex],&dataBaseInfo.dataVector[deletedResourceIndex+1],(dataBaseInfo.dataResourcesCount - (deletedResourceIndex +1)) * sizeof(RESOURCE_DATA));

    dataBaseInfo.dataResourcesCount--;
    dataBaseInfo.dataVector = (RESOURCE_DATA*)realloc(dataBaseInfo.dataVector, dataBaseInfo.dataResourcesCount * sizeof(RESOURCE_DATA));

}

unsigned char checkDataBase(){

    FILE *fp = fopen(DATABASE_NAME, "r");
    unsigned char is_exist = 0;
    if (fp != NULL)
    {
        is_exist = 1;
        fclose(fp); // close the file
    }
    return is_exist;
}

void proccessDataBaseDoesntExist(){

    printf("La BDD no existe desea crearla?[s/n]");

}

void getDataFromDataBase(){

    struct csvDoc *doc = NULL;
    struct csvDoc *nodoUso;
    unsigned char finish = 0;

    doc = parseCsvFile(DATABASE_NAME);

    if(doc==NULL){
        printf("Error al parsear la base de datos\n");
    }else{
        nodoUso = doc;
        do{
            
            if(dataBaseInfo.dataVector == NULL){
                dataBaseInfo.dataVector = (RESOURCE_DATA*)malloc(sizeof(RESOURCE_DATA));
            }else{
                dataBaseInfo.dataVector = (RESOURCE_DATA*)realloc(dataBaseInfo.dataVector,(dataBaseInfo.dataResourcesCount +1) * sizeof(RESOURCE_DATA));
            }

            for(int i = 0; i < nodoUso->contentsCount; i++){

                if(i==0){
                    sprintf(dataBaseInfo.dataVector[dataBaseInfo.dataResourcesCount].name,"%s",nodoUso->content[i]);
                }else if(i==1){
                     sprintf(dataBaseInfo.dataVector[dataBaseInfo.dataResourcesCount].link,"%s",nodoUso->content[i]);
                }else if(i==2){
                    sprintf(dataBaseInfo.dataVector[dataBaseInfo.dataResourcesCount].type,"%s",nodoUso->content[i]);
                }
            }
            
            //printf("%s \n",dataBaseInfo.dataVector[dataBaseInfo.dataResourcesCount].name);

            dataBaseInfo.dataResourcesCount++;
            
            if(nodoUso->next == NULL){
                finish = 1;
            }else{
                nodoUso = nodoUso->next;
            }

        }while(finish == 0);
        
        free(doc);
    }
}

unsigned char showDataBase(){

    unsigned char result = SUCCESS_DATABASE_OPERATION;

    printf("\nValores de la BDD : \n\n");
    for(int i = 0; i < dataBaseInfo.dataResourcesCount ; i++ ){
        printf("%s %s %s\n",dataBaseInfo.dataVector[i].name,dataBaseInfo.dataVector[i].link,dataBaseInfo.dataVector[i].type);
    }
    printf("\n\n");

    return result;
}

unsigned char saveDataIntoDataBase(){

    unsigned char result = SUCCESS_DATABASE_OPERATION;

    struct csvDoc *doc = NULL;
    struct csvDoc *nodoUso;

    for(int i = 0; i < dataBaseInfo.dataResourcesCount ; i++ ){

        if(doc==NULL){
            doc = (struct csvDoc*)malloc(sizeof(struct csvDoc));
            nodoUso = doc;
        }else{
            nodoUso->next = (struct csvDoc*)malloc(sizeof(struct csvDoc));
            nodoUso = nodoUso->next;
        } 
        nodoUso->next = NULL;  

        nodoUso->contentsCount = 3;  //Fixed value from my format
        nodoUso->content = (char**)malloc(3 * sizeof(char*));

        nodoUso->content[0] = (char*)malloc(strlen(dataBaseInfo.dataVector[i].name) * sizeof(char));
        nodoUso->content[1] = (char*)malloc(strlen(dataBaseInfo.dataVector[i].link) * sizeof(char));
        nodoUso->content[2] = (char*)malloc(strlen(dataBaseInfo.dataVector[i].type) * sizeof(char));

        sprintf(nodoUso->content[0],"%s",dataBaseInfo.dataVector[i].name);
        sprintf(nodoUso->content[1],"%s",dataBaseInfo.dataVector[i].link);
        sprintf(nodoUso->content[2],"%s",dataBaseInfo.dataVector[i].type);

    }
    
    if(!writeCsvFile(DATABASE_NAME,doc)){
        result = ERROR_DATABASE_SAVE;
    }
    free(doc);

    return result;

}