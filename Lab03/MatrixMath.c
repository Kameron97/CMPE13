//Kameron Gill
//1476833
//kgill2@ucsc.edu

//lab 3
//MatrixMath.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "MatrixMath.h"




//MatrixxMulitply,
//Multiply matrixes

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    int x, y, z;
    // result[3][3] = {0}; //set all variables in matrix to 0.

    //goes through each matrix input
    for (x = 0; x <= 2; x++) {
        for (y = 0; y <= 2; y++) {
            for (z = 0; z <= 2; z++) {
                result[x][y] += mat1[x][z] * mat2[z][y];
                //multiplication of matrix.
                //for iteration of i, j = 0 will be:
                //result[0][0]= mat1[0][0]*mat2[0][0]+mat1[0][1]*mat2[1][0]
                //                 +mat1[2][0]*mat2[0][2]
            }
        }
    }
}


//MatrixAdd()
//adds matrix

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]) {

    int x, y;

    //goes through [0][0]->[3][3]]
    for (x = 0; x <= 2; x++) {
        for (y = 0; y <= 2; y++) {
            result[x][y] = mat1[x][y] + mat2[x][y];
            //adds result to matrix in each slot
            //for result[0][0], it will be
            //mat1[0][0]+ mat2[0][0]]
        }
    }

}

//MatrixEqual
// checks to see if each slot of both matrix are equal to eachother

int MatrixEquals(float mat1[3][3], float mat2[3][3]) {
    int x, y;
    int result = 1;

    //goes through the matrix [0][0]->[3][3]
    for (x = 0; x <= 2; x++) {
        for (y = 0; y <= 2; y++) {

            //checks if  each input of the matrix is equal to the other
            if (fabs(mat1[x][y] - mat2[x][y]) > FP_DELTA) {
                result = 0;
            }
        }
    }
    return result;

}


//matrix scalarMultiply
//multiplies a matrix by a number

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]) {
    int z, y;

    for (z = 0; z <= 2; z++) {
        for (y = 0; y <= 2; y++) {
            result[z][y] = x * mat[z][y];
        }
    }
}

//matrixScalarAdd
//adds a digit to all inputs of matrix inputs

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]) {
    int z, y;

    for (z = 0; z <= 2; z++) {
        for (y = 0; y <= 2; y++) {
            result[z][y] = mat[z][y] + x;
        }
    }
}


//matrixDeterminant

float MatrixDeterminant(float mat[3][3]) {
    float det1, det2, det3 = 0; //addition diagonls
    float det4, det5, det6 = 0; //subtraction diagonals
    float detTotal = 0;

    //below is the formula to get the determinant:

    //we get the product of the diagonals of the top 3 numbers
    det1 = mat[0][0] * mat[1][1] * mat[2][2];
    det2 = mat[1][0] * mat[2][1] * mat[0][2];
    det3 = mat[2][0] * mat[0][1] * mat[1][2];

    //and the products of the bottom 3 diagonsla
    det4 = mat[0][2] * mat[1][1] * mat[2][0];
    det5 = mat[1][2] * mat[2][1] * mat[0][0];
    det6 = mat[2][2] * mat[0][1] * mat[1][0];

    //and add and subtract them together
    detTotal = det1 + det2 + det3 - (det4 + det5 + det6);
    return detTotal;

}


//MatrixTrace
//get diagonal of matrix

float MatrixTrace(float mat[3][3]) {
    return mat[0][0] + mat[1][1] + mat[2][2];
}

//MatrixTranspose

void MatrixTranspose(float mat[3][3], float result[3][3]) {
    int x, y;

    for (x = 0; x <= 2; x++) {
        for (y = 0; y <= 2; y++) {
            result[y][x] = mat[x][y];
        }
    }
}

//MatrixInverse

void MatrixInverse(float mat[3][3], float result[3][3]) {
    
    //uses the inverse equation discussed in the handout
  result[0][0] = (mat[1][1] * mat[2][2] - (mat[1][2] * mat[2][1]));
    result[0][1] = -((mat[0][1] * mat[2][2]) - (mat[0][2] * mat[2][1]));
    result[0][2] = ((mat[0][1] * mat[1][2]) - (mat[0][2] * mat[1][1]));
    result[1][0] = -((mat[1][0] * mat[2][2]) - (mat[1][2] * mat[2][0]));
    result[1][1] = ((mat[0][0] * mat[2][2]) - (mat[0][2] * mat[2][0]));
    result[1][2] = -((mat[0][0] * mat[1][2]) - (mat[0][2] * mat[1][0]));
    result[2][0] = ((mat[1][0] * mat[2][1]) - (mat[1][1] * mat[2][0]));
    result[2][1] = -((mat[0][0] * mat[2][1]) - (mat[0][1] * mat[2][0]));
    result[2][2] = ((mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]));


    MatrixScalarMultiply(1 / MatrixDeterminant(mat), result, result);






}
//did not make Adjugate

void MatrixAdjugate(float math[3][3], float result[3][3]) {

}

void MatrixPrint(float mat[3][3]) {
    int a, b;
    printf("\nThe matrix is");
    for (a = 0; a < 3; a++) {
        printf("\n");
        for (b = 0; b < 3; b++) {
            printf("mat[%d][%d]: %.2f\t", a, b, (double) mat[a][b]);
        }
    }
}
