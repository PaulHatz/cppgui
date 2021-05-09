#pragma once

enum class HUDTYPE
{
	HUD_UNUSED,
	HUD_RESERVED,
	HUD_TEXT,
	HUD_TEXT_WRAPPED,
	HUD_SHADER,
	HUD_SPRITE,
	HUD_CIRCLE,
	HUD_SWITCH,
	HUD_VALUE,
};

enum ValueType
{
	VALUE_NONE,
	VALUE_BOOL,
	VALUE_INT,
	VALUE_STRING,
	VALUE_FLOAT
};

struct hudelem_s
{
	HUDTYPE Type;

	std::string *Text;

	float x;
	float y;

	float width;
	float height;

	unsigned int font;
	float fontSize;

	float color[4];

	float fromX;
	float fromY;

	float fromWidth;
	float fromHeight;

	float fromColor[4];

	long moveStartTime;
	long moveTime;

	long scaleStartTime;
	long scaleTime;

	long fadeStartTime;
	long fadeTime;

	hudelem_s();
};

class game_hudelem_s
{
private:

public:
	game_hudelem_s();
	~game_hudelem_s();
	//hudelem_s *elem;
	hudelem_s *elem;

	void SetShader(float x, float y, float width, float height, float r, float g, float b, float a);
	void SetText(std::string Text, float x, float y, unsigned int font, float fontScale, bool justified, bool centered, bool outlined, float r, float g, float b, float a);

	void ChangeText(std::string Text);

	void MoveOverTime(long time, float x, float y);
	void ScaleOverTime(long time, float width, float height);
	void FadeOverTime(long time, float r, float g, float b, float a);
};

float getStringWidth(std::string text, float scale, unsigned int font);
float getStringHeight(std::string text, float scale, unsigned int font);
