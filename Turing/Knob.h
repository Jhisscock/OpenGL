extern float knobPos[][3];

void drawCylinder(float radius, float height, float scale, float r, float g, float b);
void drawRectangularPrism(float x, float y, float z, float scale, float r, float g, float b,float xMod);
void drawKnobRect(float x, float y, float z, float scale, float r, float g, float b, float xMod);
void drawChord(float radius, float scale, float r, float g, float b, float size, float x, float y, float z, int startPos, bool horiz, float xMod, float yMod);