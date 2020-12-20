/*--------------------------------------------------------------
*
*  Description - This program defines the functions which the 
*                main program will use
*
*  Programmer - Jacob Hisscock
*
*---------------------------------------------------------------
*/

#define _USE_MATH_DEFINES

#include "functions.h"
#include <math.h>

//Matrix multiplication
vector<double> functions::matrixMultiplication(vector<double> v, double a [][3], int size){
    vector<double> resultVector;
    v[2] = 1;
    
    //Multiply matricies values and insert them into result vector which will be returned
    for(int i = 0; i < size; i++){
        int sum = 0;
        for(int j = 0; j < size; j++){
            sum += a[i][j] * v[j];
        }
        resultVector.push_back(sum);
    }

    return resultVector;
}

vector<double> functions::rotate(vector<double> v, double rotation){
    //Convert radians to degrees then define rotation matrix for given point
    rotation *= M_PI / 180;
    double rotationMatrix [3][3] {{cos(rotation), -sin(rotation), 0}, {sin(rotation), cos(rotation), 0}, {0, 0, 0}};

    //Return multiplication of rotation matrix and the current point
    return matrixMultiplication(v, rotationMatrix, 2);
}

vector<double> functions::scale(vector<double> v, double x, double y){
    //Define scale matrix based on user input
    double scaleMatrix [3][3] {{x, 0, 0}, {0, y, 0}, {0, 0, 0}};
    
    //Return multiplication of scale matrix and the current point
    return matrixMultiplication(v, scaleMatrix, 2);
}

vector<double> functions::translate(vector<double> v, double x, double y){
    //Define translation matrix based on user input
    double translationMatrix [3][3] {{1, 0, x}, {0, 1, y}, {0, 0, 1}};

    //Return multiplication of translation matrix and the current point
    return matrixMultiplication(v, translationMatrix, 3);
}