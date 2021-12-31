#pragma once

float CalculateDistance(float *a, float *b);

bool DetectDrag(float *originalPos, float *currentPos);

void DRAW_TEXT(std::string text, float x, float y, float scale, unsigned int font, float R, float G, float B, float A);
void DRAW_RECT(float posX, float posY, float width, float height, float R, float G, float B, float A);
