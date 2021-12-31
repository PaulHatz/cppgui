#include "main.h"

void RadioButton_Click(guiObject *sender, EventArgs *e)
{
	guiObject *parent = sender->getParent();
	std::vector<guiObject *> radioButtons;

	for (guiObject *child : parent->getChildren()) {
		if (child->getObjectType() == ObjectType::OBJ_RadioButton) {
			radioButtons.push_back(child);
		}
	}

	for (guiObject *radioButtonObj : radioButtons) {
		RadioButton *radioButton = (RadioButton *)radioButtonObj;
		radioButton->setChecked((radioButtonObj != sender) ? false : true);
	}

	guiApplication->sendEvent(eventCheckChanged, sender);
}

void RadioButton::updateGuiElements(int time)
{
	if (this->textElem)
		this->textElem->MoveOverTime(time, this->getX() + 25.f, this->getY());

	if (this->boxElem)
		this->boxElem->MoveOverTime(time, this->getX(), this->getY());

	if (this->checkElem)
		this->checkElem->MoveOverTime(time, this->getX() + 2, this->getY() + 2);
}

void RadioButton::show()
{
	this->bVisible = true;

	int time = 0;
	if (this->textElem)
		this->textElem->FadeOverTime(time, this->textColor[0], this->textColor[1], this->textColor[2], 255.f);

	if (this->boxElem)
		this->boxElem->FadeOverTime(time, 128.f, 128.f, 128.f, 255.f);

	if (this->checkElem)
		this->checkElem->FadeOverTime(time, 255.f, 255.f, 255.f, this->bChecked ? 255.f : 0.f);
}


void RadioButton::hide()
{
	this->bVisible = false;

	int time = 0;
	if (this->textElem)
		this->textElem->FadeOverTime(time, this->textColor[0], this->textColor[1], this->textColor[2], 0.f);

	if (this->boxElem)
		this->boxElem->FadeOverTime(time, 128.f, 128.f, 128.f, 0.f);

	if (this->checkElem)
		this->checkElem->FadeOverTime(time, 255.f, 255.f, 255.f, 0.f);
}

void RadioButton::setChecked(bool checked)
{
	this->bChecked = checked;
	this->checkElem->FadeOverTime(0, 255.f, 255.f, 255.f, this->bChecked ? 255.f : 0.f);
}

std::string RadioButton::getText()
{
	return this->text;
}

void RadioButton::setText(std::string text)
{
	this->text = text;
	this->textElem->ChangeText(text);
	this->setSize(getStringWidth(this->text, this->fontScale, this->font) + 25, 15);
}

RadioButton::RadioButton(guiObject *parent) : guiObject(parent, ObjectType::OBJ_RadioButton)
{
	if (parent) {
		parent->addChild(this);
		this->setEnabled(parent->Enabled());
	}

	this->boxElem = new game_hudelem_s();
	this->checkElem = new game_hudelem_s();
	this->textElem = new game_hudelem_s();

	this->bChecked = false;

	this->textColor[0] = 255;
	this->textColor[1] = 255;
	this->textColor[2] = 255;
	this->textColor[3] = 255;

	this->text = std::string("radioButton");

	this->font = 0;
	this->fontScale = 12.f;

	this->setPosition(200, 200);
	this->setSize(getStringWidth(this->text, this->fontScale, this->font) + 25, 15);



	float x = this->getX(),
		y = this->getY(),
		width = this->getWidth(),
		height = this->getHeight();

	this->boxElem->SetShader(x, y, 15.f, 15.f, 128, 128, 128, this->Enabled() ? 255.f : 0.f);
	this->checkElem->SetShader(x + 2, y + 2, 11, 11, 255.f, 255.f, 255.f, 0.f);
	this->textElem->SetText(this->text, x + 25, y, this->font, this->fontScale, false, false, false, 255.f, 255.f, 255.f, this->Enabled() ? 255.f : 0.f);

	this->addEvent(eventClick, RadioButton_Click);
}
