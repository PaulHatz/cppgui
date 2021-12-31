#pragma once

struct DataGridViewColomn
{
	std::string colomnText;
	float colomnWidth; //Leave at 0 for automatic.

	DataGridViewColomn(std::string text, float width);
};


class DataGridView : public guiObject
{
private:

	game_hudelem_s *backgroundElem;
	class DataGridViewCell *selectedCell;

	class MenuStrip *menuStrip;

public:

	size_t colomnCount;
	size_t rowCount;

	std::vector < DataGridViewColomn > colomns;

	void updateGuiElements(int time);
	void show();
	void hide();

	size_t getNumberOfColomns();

	void addColomn(std::string colomnText, float width);

	//Add a specified number of rows
	void addRows(int numRows);
	void set(size_t rowIndex, size_t colIndex, std::string string);

	void linkMenuStrip(class MenuStrip *menuStrip);

	DataGridView(guiObject *parent);

	friend void DataGridView_ClickOnCell(guiObject *obj, EventArgs *e);
	friend void DataGridView_RightClickOnCell(guiObject *obj, EventArgs *e);

};