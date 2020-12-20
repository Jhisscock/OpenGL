/*---------------------------------------------------------------
*
*  Description - Create the header file for our functions program
*                to use
*
*  Programmer - Jacob Hisscock
*
*----------------------------------------------------------------
*/

#include <vector>
using namespace std;

#ifndef functions_h
#define functions_h

class functions{

    public:
      vector<double> matrixMultiplication(vector<double> v, double a [][3], int size);
      vector<double> translate(vector<double> v, double x, double y);
      vector<double> scale(vector<double> v, double x, double y);
      vector<double> rotate(vector<double> v, double rotation);
    
};
#endif