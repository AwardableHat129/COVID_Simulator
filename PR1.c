#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum BOOL {FALSE, TRUE};
enum INFECTION_STATUS {SANO, INFECTADO, RECUPERADO};
enum STATUS_CELL {LIBRE, OCUPADA};

#define ROWS 10
#define COLUMNS 10

int contadorSanos;
int contadorEnfermos;
int contadorRecuperados;

typedef struct CELL{

    enum STATUS_CELL statusCell;
    int cellID;
    int age;
    enum INFECTION_STATUS infectionStatus;
    int sickDays;
    enum BOOL mask;

} CELL;

int randNum(int n){

    return rand() %  n;

}

int trySuccess(int success){

    int chance = randNum(100);
    return (chance <= success);

}

int resetMatrix(CELL *pointer){    

    CELL *cellPointer = pointer;
    for(int i = 0; i < (ROWS*COLUMNS); i++){

        cellPointer -> statusCell = LIBRE;
        cellPointer -> cellID = -1;
        cellPointer -> age = -1;
        cellPointer -> infectionStatus = -1;
        cellPointer -> sickDays = 0;
        cellPointer -> mask = -1;

        cellPointer += 1;

    }

}

void printMatrix(CELL *pointer){

    printf("\n");    

    CELL *cellPointer = pointer;

    int charStatus;    

    for(int i = 0; i < ROWS; i++){

        for(int j = 0; j < COLUMNS; j++){

            if(cellPointer -> statusCell == LIBRE){

                printf("  ");

            } else {

                charStatus = ((cellPointer -> infectionStatus) * 2) + (cellPointer -> mask);
    //Esto lo que hace es multiplicar el valor de infectionStatus por dos y sumárselo al de máscara para obtener los 5 casos distintos
    //Sano y sin máscara resultara 0, sano con máscara resultará 1, infectado sin máscara resultará 2, infectado con máscara resultará 3
    //y recuperado será 4 o 5

                switch(charStatus){

                    case 0: printf(" S"); break;
                    case 1: printf(" s"); break;
                    case 2: printf(" E"); break;
                    case 3: printf(" e"); break;
                    default: printf(" r"); break;

                }
            }

            cellPointer += 1;

        }

        printf("\n");

    }

}

void initializer(CELL *matrixPointer, int occupationPercentage){

    CELL *cellPointer;

    int positionInMatrix = 0;
    int totalCells = ROWS * COLUMNS;
    int cellsToOccupy = (totalCells * occupationPercentage) / 100;
    int occupiedCellsCounter = 0;
           

    while(occupiedCellsCounter < cellsToOccupy){ //Este ciclo debe continuar hasta que se llenen las celdas necesarias.

        cellPointer = matrixPointer + positionInMatrix; //Con esto navegamos por la matriz.

        if((cellPointer -> statusCell == LIBRE) && trySuccess(50)){

            cellPointer -> statusCell = OCUPADA;
            cellPointer -> cellID = occupiedCellsCounter + 1;
            cellPointer -> age = randNum(90) + 1;
            cellPointer -> infectionStatus = SANO;
            contadorSanos++;

            if((occupiedCellsCounter + 1) % 2){

                cellPointer -> mask = TRUE;

            } else {

                cellPointer -> mask = FALSE;

            } //Esto asigna máscaras a la mitad de las celdas.

            occupiedCellsCounter++;

        }
        
        positionInMatrix = positionInMatrix % totalCells; //Esto resetea a positionInMatrix si excede totalCells

    }


}


int main(){

    int percentageOccupiedCells = 80;
    int days = 10;

    contadorSanos = 0;
    contadorEnfermos = 0;
    contadorRecuperados = 0;

    setbuf(stdout, NULL);

    srand(time(NULL));

    CELL matrix[ROWS][COLUMNS];

    resetMatrix((CELL *) matrix);

    initializer((CELL *) matrix, 80);

    printMatrix((CELL *) matrix);

    //printMatrix((CELL *) matrix);


}
