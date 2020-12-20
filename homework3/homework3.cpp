/*--------------------------------------------------------------
*
*  Description - This program takes a point and then performs
*                the user provided tranformation on that point.
*
*  Programmer - Jacob Hisscock
*
*---------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include "functions.h"

using namespace std;

int main(){
    double x, y;
    int transformType;
    functions f; //define fucntions

    //Get intial point and save into vector
    cout << "Enter Point (x, y) with space in between values: ";
    cin >> x;
    cin >> y;

    vector<double> point {x, y, 1};

    //Repeat program until user terminates by entering 0
    int retry = 1;
    while(retry == 1){
        //User chooses transformation type
        cout << "Enter tranformation type (1 = translate, 2 = rotate, 3 = scale): ";
        cin >> transformType;

        switch(transformType){
            case 1:
                double transformX, transformY;
                cout << "Enter transformation for x and y with space in between (transformation x, transformation y): ";
                cin >> transformX;
                cin >> transformY;

                //Call translate function, print out result, modify point to have new location values
                point = f.translate(point, transformX, transformY);
                for(int i = 0; i < 2; i++){
                    cout << point[i] << " ";
                }
                cout << "\n";

                break;
            case 2:
                double rotation;

                cout << "Enter rotation in degrees: ";
                cin >> rotation;

                //Call rotate function, print out result, modify point to have new location values
                point = f.rotate(point, rotation);
                for(int i = 0; i < 2; i++){
                    cout << point[i] << " ";
                }
                cout << "\n";

                break;
            case 3:
                double xScale, yScale;

                cout << "Enter scaling value for x and y with a space in between (scale x, scale y): ";
                cin >> xScale;
                cin >> yScale;

                //Call scale function, print out result, modify point to have new location values
                point = f.scale(point, xScale, yScale);
                for(int i = 0; i < 2; i++){
                    cout << point[i] << " ";
                }
                cout << "\n";

                break;
            default:
                break;
        }

        //Ask user if they want to repeat program
        cout << "Continue? (0 = No, 1 = Yes): ";
        cin >> retry;
        cout << "\n";
    }
}