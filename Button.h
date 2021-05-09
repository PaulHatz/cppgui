#pragma once

enum class ButtonText_Align
{
	ButtonText_Left,
	ButtonText_Center
};

#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  Button : public guiObject
#else
class _declspec(dllimport)  Button : public guiObject
#endif
{
private:

	float buttonColor[4];
	float buttonHoverColor[4];
	float textColor[4];

	float fontSize;

	std::string text;
	
	class game_hudelem_s *textElem;
	class game_hudelem_s *buttonElem;

	ButtonText_Align textAlign;

public:

	//Override guiObject methods
	void updateGuiElements(int time);
	void show();
	void hide();

	//Class-specific methods
	void setText(std::string text);
	void setColor(float r, float g, float b, float a);
	void setTextColor(float r, float g, float b, float a);
	void setHoverColor(float r, float g, float b, float a);

	void setTextAlign(ButtonText_Align newAlign);

	Button(guiObject *parent);

	//Event trigger methods
	friend void Button_Hover(guiObject *obj, EventArgs *e);
	friend void Button_Unhover(guiObject *obj, EventArgs *e);
};

