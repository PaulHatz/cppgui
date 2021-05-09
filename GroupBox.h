#pragma once

#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  GroupBox : public guiObject
#else
class _declspec(dllimport)  GroupBox : public guiObject
#endif
{
private:
	float borderColor[4];
	float backgroundColor[4];

	std::string text;


	game_hudelem_s *textElem;
	game_hudelem_s *backgroundElem;
	game_hudelem_s *borderElems[5];


public:

	void updateGuiElements(int time);
	void show();
	void hide();

	void setText(std::string text);
	void setBorderColor(float r, float g, float b);
	void setBackgroundColor(float r, float g, float b);

	GroupBox(guiObject *parent);
};

