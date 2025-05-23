#define SUCCESS_DATABASE_OPERATION 1
#define ERROR_DATABASE_OPERATION 2
#define ERROR_RESOURCE_NOT_FOUND 3
#define RESOURCE_FOUND 4
#define ERROR_DATABASE_SAVE 5


#define DATABASE_NAME "misDatos.csv"

typedef struct resourceData{

    char name[300];
    char link[300];
    char type[300];

}RESOURCE_DATA;

typedef struct resourceDataVector{

    RESOURCE_DATA *dataVector;
    int dataResourcesCount;

}RESOURCE_DATA_VECTOR;

extern RESOURCE_DATA_VECTOR dataBaseInfo;

void startUpDataBase();
unsigned char requestInfo();
void showSelectedResourceInfo(char *name);
unsigned char insertInfo();
unsigned char addData2DataVector(RESOURCE_DATA* data2Insert);
unsigned char deleteInfo();
void deleteResourceFromDataVector(char *resourceName);
unsigned resourceFound(char *resourceName);
unsigned char checkDataBase();
void proccessDataBaseDoesntExist();
void getDataFromDataBase();
unsigned char showDataBase();
unsigned char saveDataIntoDataBase();