#include "main.h"

hudelem_s::hudelem_s()
{
	memset(this, 0, sizeof(hudelem_s));
}

game_hudelem_s::game_hudelem_s()
{
	this->elem = guiApplication->AllocHudElem();

	this->elem->Type = HUDTYPE::HUD_RESERVED;
}

game_hudelem_s::~game_hudelem_s()
{
	if (elem != NULL)
		memset(elem, 0, sizeof(hudelem_s));
}

void game_hudelem_s::SetShader(float x, float y, float width, float height, float r, float g, float b, float a)
{
	if (&elem) {
		elem->Type = HUDTYPE::HUD_SHADER;

		elem->x = x;
		elem->y = y;

		elem->fromX = elem->x;
		elem->fromY = elem->y;

		elem->width = width;
		elem->height = height;

		elem->fromWidth = elem->width;
		elem->fromHeight = elem->height;

		elem->color[0] = r;
		elem->color[1] = g;
		elem->color[2] = b;
		elem->color[3] = a;

		elem->fromColor[0] = elem->color[0];
		elem->fromColor[1] = elem->color[1];
		elem->fromColor[2] = elem->color[2];
		elem->fromColor[3] = elem->color[3];
	}
}

void game_hudelem_s::SetText(std::string Text, float x, float y, unsigned int font, float fontScale, bool justified, bool centered, bool outlined, float r, float g, float b, float a)
{
	if (elem) {
		elem->Type = HUDTYPE::HUD_TEXT;

		elem->Text = new std::string(Text);

		elem->x = x;
		elem->y = y;

		elem->fromX = elem->x;
		elem->fromY = elem->y;

		elem->font = font;
		elem->fontSize = fontScale;

		elem->color[0] = r;
		elem->color[1] = g;
		elem->color[2] = b;
		elem->color[3] = a;

		elem->fromColor[0] = elem->color[0];
		elem->fromColor[1] = elem->color[1];
		elem->fromColor[2] = elem->color[2];
		elem->fromColor[3] = elem->color[3];
	}
}

void game_hudelem_s::ChangeText(std::string Text)
{
	if (elem->Text != nullptr)
		delete elem->Text;
	elem->Text = new std::string(Text);
}

void game_hudelem_s::MoveOverTime(long time, float x, float y)
{
	if (elem) {

		elem->fromX = elem->x;
		elem->fromY = elem->y;

		elem->moveTime = time;
		elem->moveStartTime = MenuTime;

		elem->x = x;
		elem->y = y;

	}
}

void game_hudelem_s::ScaleOverTime(long time, float width, float height)
{
	if (elem) {
		elem->fromWidth = elem->width;
		elem->fromHeight = elem->height;

		elem->scaleTime = time;
		elem->scaleStartTime = MenuTime;

		elem->width = width;
		elem->height = height;
	}
}

void game_hudelem_s::FadeOverTime(long time, float r, float g, float b, float a)
{
	elem->fromColor[0] = elem->color[0];
	elem->fromColor[1] = elem->color[1];
	elem->fromColor[2] = elem->color[2];
	elem->fromColor[3] = elem->color[3];

	elem->fadeTime = time;
	elem->fadeStartTime = MenuTime;

	elem->color[0] = r;
	elem->color[1] = g;
	elem->color[2] = b;
	elem->color[3] = a;
}

float getStringWidth(std::string text, float scale, unsigned int font)
{
	if (scale == 0.f) return 0;
	return getTextWidth(text.c_str(), getRobotoFont(), scale);
}

float getStringHeight(std::string text, float scale, unsigned int font)
{
	return scale;
	//if (scale == 0.f) return 0;
	//return getTextHeight(text.c_str(), getRobotoFont(), scale);
}