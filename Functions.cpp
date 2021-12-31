#include "main.h"
#include "Functions.h"

float CalculateDistance(float *a, float *b)
{
	return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
}

bool DetectDrag(float *originalPos, float *currentPos)
{
	float distance = CalculateDistance(originalPos, currentPos);

	if (distance > 1)
		return true;

	else return false;
}


void DRAW_TEXT(std::string text, float x, float y, float scale, unsigned int font, float R, float G, float B, float A)
{
	drawText(text.c_str(), x, y, getRobotoFont(), scale, R, G, B, A);
}

void DRAW_RECT(float posX, float posY, float width, float height, float R, float G, float B, float A)
{
	drawBox(posX, posY, width, height, R, G, B, A);
}
