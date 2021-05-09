#pragma once
#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  TabPage : public guiObject
#else
class _declspec(dllimport)  TabPage : public guiObject
#endif
{
private:
	unsigned int index;
	std::string text;

	game_hudelem_s *backgroundElem;

	game_hudelem_s *hitboxBackground;
	//game_hudelem_s *activeElem;
	game_hudelem_s *hitboxText;

	guiObject *hitBox;

public:

	float getHitboxWidth();

	void setText(std::string text);
	std::string getText();

	void setIndex(int index);
	int getIndex();

	void updateGuiElements(int time);

	void show();
	void hide();

	void tabChange_HideGuiElements(int time);

	TabPage(guiObject *parent, guiObject *hitBox, unsigned int index);

	friend void tpHitBox_Hover(guiObject *sender, EventArgs *e);
	friend void tpHitBox_Unhover(guiObject *sender, EventArgs *e);

};

