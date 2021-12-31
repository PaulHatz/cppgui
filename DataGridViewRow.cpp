#include "main.h"

DataGridViewRow::DataGridViewRow(guiObject *parent) : guiObject(parent, ObjectType::OBJ_DataGridViewRow)
{
	if (this->getParent()) {
		parent->addChild(this);
		this->setEnabled(parent->Enabled());


		if (this->getParent()->getObjectType() == ObjectType::OBJ_DataGridView) {
			auto dataGridView = (DataGridView *)this->getParent();


			this->setPosition(dataGridView->getX() + 2, dataGridView->getY() + (dataGridView->rowCount * 20.f) + 2.f);

			size_t colomnCount = dataGridView->getNumberOfColomns();

			float currentX = dataGridView->getX() + 2.f; //2.f is padding

			for (auto colomn : dataGridView->colomns) {

				auto cell = new DataGridViewCell(this);
				cell->setSize(colomn.colomnWidth, 20.f); //Height
				cell->setPosition(currentX, dataGridView->getY() + 2.f + (dataGridView->rowCount * 20.f)); //20.f is height

				this->addChild(cell);

				currentX += colomn.colomnWidth;
				this->setSize(this->getWidth() + colomn.colomnWidth, 20.f);
			}
		}
	}
}

void DataGridViewCell::updateGuiElements(int time)
{
	if (this->backgroundElem) {
		this->backgroundElem->MoveOverTime(time, this->getX(), this->getY());
		this->backgroundElem->ScaleOverTime(time, this->getWidth(), this->getHeight());
	}

	if (this->textElem)
		this->textElem->MoveOverTime(time, this->getX() + 2.f, this->getY());
}

void DataGridViewCell::show()
{
	this->bVisible = true;

	if (this->backgroundElem)
		this->backgroundElem->FadeOverTime(0, 255, 255, 255, 255);
	
	if (this->textElem)
		this->textElem->FadeOverTime(0, 0, 0, 0, 255);

}

void DataGridViewCell::hide()
{
	this->bVisible = false;

	if (this->backgroundElem)
		this->backgroundElem->FadeOverTime(0, 255, 255, 255, 0);

	if (this->textElem)
		this->textElem->FadeOverTime(0, 0, 0, 0, 0);
}

void DataGridViewCell::setText(std::string text)
{
	this->text = text;

	if (this->textElem)
		this->textElem->ChangeText(this->text);
}

void DataGridViewCell::selectCell()
{
	if (this->Enabled()) {

		if (this->backgroundElem)
			this->backgroundElem->FadeOverTime(0, 0, 0, 255, 255);

		if (this->textElem)
			this->textElem->FadeOverTime(0, 255, 255, 255, 255);
	}

}

void DataGridViewCell::deselectCell()
{
	if (this->backgroundElem)
		this->backgroundElem->FadeOverTime(0, 255, 255, 255, this->Enabled() ? 255 : 0);

	if (this->textElem)
		this->textElem->FadeOverTime(0, 0, 0, 0, this->Enabled() ? 255 : 0);
}

DataGridView *DataGridViewCell::getParentDataGridView()
{
	if (this->getParent() && this->getParent()->getParent()) {
		auto dataGridView = (DataGridView *)this->getParent()->getParent();

		if (dataGridView->getObjectType() == ObjectType::OBJ_DataGridView)
			return dataGridView;

		else printf("Error: Parent is not a DataGridView\n");

	}

	return nullptr;
}

DataGridViewCell::DataGridViewCell(guiObject *parent) : guiObject(parent, ObjectType::OBJ_DataGridViewCell)
{
	if (this->getParent()) {
		parent->addChild(this);
		this->setEnabled(parent->Enabled());
	}

	this->backgroundElem = new game_hudelem_s();
	this->textElem = new game_hudelem_s();

	if (this->backgroundElem)
		this->backgroundElem->SetShader(0, 0, 0, 0, 255, 255, 255, 0);

	if (this->textElem)
		this->textElem->SetText(this->text, 0, 0, 0, 12.f, false, false, false, 0, 0, 0, 0);
}
