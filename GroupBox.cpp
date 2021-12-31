#include "main.h"

void GroupBox::updateGuiElements(int time)
{
	float x = this->getX(), y = this->getY(),
		width = this->getWidth(), height = this->getHeight();

	float strWidth = getStringWidth(this->text, 12.f, 0);
	float strHeight = getStringHeight(this->text, 12.f, 0);

	if (this->backgroundElem) {
		this->backgroundElem->MoveOverTime(time, x + 2, y + 2);
		this->backgroundElem->ScaleOverTime(time, width - 4, height - 4);
	}

	if (this->borderElems[0]) {
		this->borderElems[0]->MoveOverTime(time, x, y);
		this->borderElems[0]->ScaleOverTime(time, 8, 2);
	}	
	
	if (this->borderElems[1]) {
		this->borderElems[1]->MoveOverTime(time, x + strWidth + 10, y);
		this->borderElems[1]->ScaleOverTime(time, width - strWidth - 10, 2);
	}

	if (this->borderElems[2]) {
		this->borderElems[2]->MoveOverTime(time, x, y + height - 2);
		this->borderElems[2]->ScaleOverTime(time, width, 2);
	}

	if (this->borderElems[3]) {
		this->borderElems[3]->MoveOverTime(time, x, y);
		this->borderElems[3]->ScaleOverTime(time, 2, height);
	}

	if (this->borderElems[4]) {
		this->borderElems[4]->MoveOverTime(time, x + width - 2, y);
		this->borderElems[4]->ScaleOverTime(time, 2, height);
	}
	
	if (this->textElem) {
		this->textElem->MoveOverTime(time, x + 10, y - (strHeight));
	}

	this->updateChildren();
}

void GroupBox::show()
{
	this->bVisible = true;

	int time = 0;

	if (this->backgroundElem != nullptr)
		this->backgroundElem->FadeOverTime(time, this->backgroundColor[0], this->backgroundColor[1], this->backgroundColor[2], 255.f);

	if (this->borderElems[0] != nullptr)
		this->borderElems[0]->FadeOverTime(time, this->borderColor[0], this->borderColor[1], this->borderColor[2], 255.f);

	if (this->borderElems[1] != nullptr)
		this->borderElems[1]->FadeOverTime(time, this->borderColor[0], this->borderColor[1], this->borderColor[2], 255.f);

	if (this->borderElems[2] != nullptr)
		this->borderElems[2]->FadeOverTime(time, this->borderColor[0], this->borderColor[1], this->borderColor[2], 255.f);

	if (this->borderElems[3] != nullptr)
		this->borderElems[3]->FadeOverTime(time, this->borderColor[0], this->borderColor[1], this->borderColor[2], 255.f);

	if (this->borderElems[4] != nullptr)
		this->borderElems[4]->FadeOverTime(time, this->borderColor[0], this->borderColor[1], this->borderColor[2], 255.f);

	if (this->textElem != nullptr)
		this->textElem->FadeOverTime(time, 255.f, 255.f, 255.f, 255.f);

	for (auto child : this->getChildren()) {
		child->show();
	}
}

void GroupBox::hide()
{
	this->bVisible = false;

	int time = 0;
	if (this->backgroundElem != nullptr)
		this->backgroundElem->FadeOverTime(time, this->backgroundColor[0], this->backgroundColor[1], this->backgroundColor[2], 0.f);

	if (this->borderElems[0] != nullptr)
		this->borderElems[0]->FadeOverTime(time, this->borderColor[0], this->borderColor[1], this->borderColor[2], 0.f);

	if (this->borderElems[1] != nullptr)
		this->borderElems[1]->FadeOverTime(time, this->borderColor[0], this->borderColor[1], this->borderColor[2], 0.f);

	if (this->borderElems[2] != nullptr)
		this->borderElems[2]->FadeOverTime(time, this->borderColor[0], this->borderColor[1], this->borderColor[2], 0.f);

	if (this->borderElems[3] != nullptr)
		this->borderElems[3]->FadeOverTime(time, this->borderColor[0], this->borderColor[1], this->borderColor[2], 0.f);

	if (this->borderElems[4] != nullptr)
		this->borderElems[4]->FadeOverTime(time, this->borderColor[0], this->borderColor[1], this->borderColor[2], 0.f);

	if (this->textElem != nullptr)
		this->textElem->FadeOverTime(time, 255.f, 255.f, 255.f, 0.f);

	for (auto child : this->getChildren()) {
		child->hide();
	}
}

void GroupBox::setText(std::string text)
{
	this->text = text;

	float strWidth = getStringWidth(this->text, 12.f, 0);
	float strHeight = getStringHeight(this->text, 12.f, 0);

	this->borderElems[1]->MoveOverTime(0, this->getX() + strWidth +8 , this->getY());
	this->borderElems[1]->ScaleOverTime(0, this->getWidth() - strWidth - 8, 2);

	this->textElem->ChangeText(text);
}

void GroupBox::setBorderColor(float r, float g, float b)
{
	this->borderColor[0] = r;
	this->borderColor[1] = g;
	this->borderColor[2] = b;
}

void GroupBox::setBackgroundColor(float r, float g, float b)
{
	this->backgroundColor[0] = r;
	this->backgroundColor[1] = g;
	this->backgroundColor[2] = b;
}

GroupBox::GroupBox(guiObject *parent) : guiObject(parent, ObjectType::OBJ_GroupBox)
{
	if (parent) {
		parent->addChild(this);
		this->setEnabled(parent->Enabled());
	}

	this->textElem = new game_hudelem_s();
	this->backgroundElem = new game_hudelem_s();
	this->borderElems[0] = new game_hudelem_s();
	this->borderElems[1] = new game_hudelem_s();
	this->borderElems[2] = new game_hudelem_s();
	this->borderElems[3] = new game_hudelem_s();
	this->borderElems[4] = new game_hudelem_s();

	this->setBackgroundColor(40, 40, 40);
	this->setBorderColor(255, 255, 255);

	this->setPosition(120, 300);
	this->setSize(150, 150);
	
	this->text = std::string("groupbox");


	float x = this->getX(), y = this->getY(),
		width = this->getWidth(), height = this->getHeight();

	float strWidth = getStringWidth(this->text, 12.f, 0);
	float strHeight = getStringHeight(this->text, 12.f, 0);

	this->backgroundElem->SetShader(x + 2, y + 2, width - 2, height - 2, this->backgroundColor[0], this->backgroundColor[1], this->backgroundColor[2], 0.f);
	this->borderElems[0]->SetShader(x, y, 8, 2, this->borderColor[0], this->borderColor[1], this->borderColor[2], 0.f);
	this->borderElems[1]->SetShader(x + strWidth + 10, y, width - strWidth - 10, 2, this->borderColor[0], this->borderColor[1], this->borderColor[2], 0.f);
	this->borderElems[2]->SetShader(x, y + height - 2, width, 2, this->borderColor[0], this->borderColor[1], this->borderColor[2], 0.f);
	this->borderElems[3]->SetShader(x, y, 2, height, this->borderColor[0], this->borderColor[1], this->borderColor[2], 0.f);
	this->borderElems[4]->SetShader(x + width - 2, y, 2, height, this->borderColor[0], this->borderColor[1], this->borderColor[2], 0.f);
	
	this->textElem->SetText(this->text, x + 10, y/* - (2 * strHeight)*/, 0, 12.f, false, false, false, 255.f, 255.f, 255.f, 0.f);

	if (this->Enabled()) {
		this->show();
	}
}
