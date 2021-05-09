#pragma once

#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  CheckBox : public guiObject
#else
class _declspec(dllimport)  CheckBox : public guiObject
#endif
{
private:
	int textColor[4];	

	bool bChecked;

	std::string text;
	unsigned int font;
	float fontScale;

	game_hudelem_s *textElem;
	game_hudelem_s *boxElem;
	game_hudelem_s *checkElem;
	game_hudelem_s *borders[4];
public:

	void updateGuiElements(int time);

	void show();
	void hide();

	bool Checked();
	void setChecked(bool checked);

	std::string getText();
	void setText(std::string text);

	CheckBox(guiObject *parent);

	friend void CheckBox_Click(guiObject *sender, EventArgs *e);
};

