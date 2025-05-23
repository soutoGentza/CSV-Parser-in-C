#include <stdio.h>
#include "DataManager.h"
#include "Interface.h"

const int END_PROGRAMME = 99;
const int INCORRECT_INPUT = 90;

unsigned char incorrectFormat(int input);
unsigned char proccessSelectedOption(int input);
void manageError(unsigned char result);

int main(){

    unsigned char result;
    int input;

    printWelcomeMenu();

    startUpDataBase();

    do{
        printOptionsMenu();
        scanf("%d", &input);  
        result = proccessSelectedOption(input);

        if(result != SUCCESS_DATABASE_OPERATION && result != END_PROGRAMME){

            manageError(result);

        }

    }while(result != END_PROGRAMME);

    printEndMessage();
}


unsigned char proccessSelectedOption(int input){

    unsigned char result;

    if(incorrectFormat(input)){

        result = INCORRECT_INPUT;

    }else{
        switch (input)
        {   
            case 1:

                result = requestInfo();
                break;

            case 2:

                result = insertInfo();
                break;

            case 3:

                result = deleteInfo();
                break;

            case 4:

                result = showDataBase();
                break;

            case 5:

                result = END_PROGRAMME;
                break;

            case 6:
                
                result = saveDataIntoDataBase();
                if(result == SUCCESS_DATABASE_OPERATION){
                    result = END_PROGRAMME;
                }
                break;
        
            default:

                printf("INPUT desconocido\n");
                result = INCORRECT_INPUT;
                break;
        }
    }

    return result;
}

unsigned char incorrectFormat(int input){

    unsigned char result = 0;

    //TODO : Manage correct format

    return result;
}

void manageError(unsigned char result){

    printf("Resultado erroneo, se procesa\n");

    switch (result)
    {   
        case ERROR_RESOURCE_NOT_FOUND:

            printf("[ERROR] Recurso no encontrado\n");
            break;

        case ERROR_DATABASE_SAVE:

            printf("[ERROR] No se puede guardar los ultimos valores en la BDD\n");
            break;

        default:
            break;
    }
}