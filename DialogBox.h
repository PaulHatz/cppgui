#pragma once
class GuiDialogBox : public guiObject
{
private:
	game_hudelem_s *backGround;
	game_hudelem_s *borders[4];

	game_hudelem_s *titleElem;

	guiObject *previousActiveForm;

	class Label *textLabel;

public:

	void show();
	void hide();
	void updateGuiElements(int time);

	void initializeDialogBox(std::string message);


	static void Show(std::string message);
	static void Show(std::string message, std::string title);


	GuiDialogBox(guiObject *parent);

	friend void btnClick(guiObject *obj, EventArgs *e);

};

extern GuiDialogBox *GuiMessageBox;