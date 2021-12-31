#include "main.h"

void DataGridView_ClickOnCell(guiObject *obj, EventArgs *e)
{
	auto cell = (DataGridViewCell *)obj;
	
	auto view = cell->getParentDataGridView();

	if (view->selectedCell) {

		view->selectedCell->deselectCell();
		view->selectedCell = nullptr;
	}

	cell->selectCell();
	view->selectedCell = cell;
}

void DataGridView_RightClickOnCell(guiObject *obj, EventArgs *e)
{
	DataGridView_ClickOnCell(obj, e);

	auto cell = (DataGridViewCell *)obj;

	auto view = cell->getParentDataGridView();

	if (!view->menuStrip->Enabled())
		view->menuStrip->show();

	view->menuStrip->setPosition(guiApplication->getCursorInfo()->cursorPosition[0], guiApplication->getCursorInfo()->cursorPosition[1]);
}

DataGridViewColomn::DataGridViewColomn(std::string text, float width)
{
	this->colomnText = text;
	this->colomnWidth = width;
}

void DataGridView::updateGuiElements(int time)
{
	if (this->backgroundElem) {
		this->backgroundElem->MoveOverTime(time, this->getX(), this->getY());
		this->backgroundElem->ScaleOverTime(time, this->getWidth(), this->getHeight());
	}

	for (auto child : this->getChildren()) {
		child->updateGuiElements(time);
	}
}

void DataGridView::show()
{
	this->bVisible = true;

	if (this->backgroundElem)
		this->backgroundElem->FadeOverTime(0, 60, 60, 60, 255);

	for (auto child : this->getChildren()) {
		if(child->getObjectType() == ObjectType::OBJ_DataGridViewRow)
			child->show();
	}
}

void DataGridView::hide()
{
	this->bVisible = false;

	if (this->backgroundElem)
		this->backgroundElem->FadeOverTime(0, 60, 60, 60, 0);

	for (auto child : this->getChildren()) {
		child->hide();
	}
}

size_t DataGridView::getNumberOfColomns()
{
	return this->colomnCount;
}

void DataGridView::addColomn(std::string colomnText, float width)
{
	this->colomns.push_back(DataGridViewColomn(colomnText, width));
	this->colomnCount++;
	this->setSize(this->getWidth() + width, this->getHeight());
}

void DataGridView::addRows(int numRows)
{
	for (int i = 0; i < numRows; i++) {
		auto row = new DataGridViewRow(this);

		this->setSize(this->getWidth(), this->getHeight() + 20.f);
		this->rowCount++;
	}
}

void DataGridView::set(size_t rowIndex, size_t colIndex, std::string string)
{
	if (rowIndex >= this->rowCount) {
		printf("Error: rowIndex is out of bounds. rowIndex %i >= %i", rowIndex, rowCount);
		return;
	}

	auto rowObj = this->getChildren()[rowIndex];
	
	if (rowObj->getObjectType() == ObjectType::OBJ_DataGridViewRow) {
		auto row = (DataGridViewRow *)rowObj;

		auto cellObj = row->getChildren()[colIndex + 1]; //+ 1 because the first element is the MenuStrip
		if (cellObj) {
			if (cellObj->getObjectType() == ObjectType::OBJ_DataGridViewCell) {

				auto cell = (DataGridViewCell *)cellObj;
				cell->addEvent(eventClick, DataGridView_ClickOnCell);
				cell->addEvent(eventRightClick, DataGridView_RightClickOnCell);
				cell->setText(string);
			}
		}
		
	}
}

void DataGridView::linkMenuStrip(MenuStrip *menuStrip)
{
	this->menuStrip = menuStrip;
}

DataGridView::DataGridView(guiObject *parent) : guiObject(parent, ObjectType::OBJ_DataGridView)
{
	this->colomnCount = 0;
	this->selectedCell = nullptr;
	this->menuStrip = nullptr;

	if (parent) {
		parent->addChild(this);
		this->setEnabled(parent->Enabled());
	}
	this->backgroundElem = new game_hudelem_s();
	this->backgroundElem->SetShader(0, 0, 0, 0, 0, 0, 0, 0);


	this->setSize(4.f, 4.f);
}
