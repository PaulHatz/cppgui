#pragma once
#include "Object.h"

#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  RadioButton : public guiObject
#else
class _declspec(dllimport)  RadioButton : public guiObject
#endif
{
private:
	float textColor[4];

	bool bChecked;

	std::string text;
	unsigned int font;
	float fontScale;

	game_hudelem_s *textElem;
	game_hudelem_s *boxElem;
	game_hudelem_s *checkElem;

public:
	void updateGuiElements(int time);
	void show();
	void hide();
	void setChecked(bool checked);

	std::string getText();
	void setText(std::string text);

	RadioButton(guiObject *parent);

	friend void RadioButton_Click(guiObject *sender, EventArgs *e);
};

