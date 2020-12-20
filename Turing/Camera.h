extern float angle;
extern float lx, lz;
extern float x, z;
extern float deltaAngle;
extern float deltaMove;

void pressKey(int key, int xx, int yy);
void releaseKey(int key, int x, int y);
void computePos(float deltaMove);
void computeDir(float deltaAngle);
void changeSize(int w, int h);