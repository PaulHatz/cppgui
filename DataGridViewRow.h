#pragma once
#include "Object.h"

class DataGridViewCell : public guiObject
{
private:
	game_hudelem_s *backgroundElem;
	game_hudelem_s *textElem;

	std::string text;

public:
	void updateGuiElements(int time);
	void show();
	void hide();
	void setText(std::string text);

	void selectCell();
	void deselectCell();

	DataGridView *getParentDataGridView();

	DataGridViewCell(guiObject *parent);

	friend void DataGridView_ClickOnCell(guiObject *obj, EventArgs *e);
	friend void DataGridView_RightClickOnCell(guiObject *obj, EventArgs *e);
};

class DataGridViewRow : public guiObject
{
private:

public:
	DataGridViewRow(guiObject *parent);
};

