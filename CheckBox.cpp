#include "main.h"

void CheckBox_Click(guiObject *sender, EventArgs *e)
{
	CheckBox *checkBox = (CheckBox *)sender;

	checkBox->bChecked = !checkBox->bChecked;

	checkBox->checkElem->FadeOverTime(0, 47.f, 128.f, 237.f, checkBox->bChecked ? 255.f : 0.f);

	guiApplication->sendEvent(eventCheckChanged, sender);
}

void CheckBox::updateGuiElements(int time)
{
	if (this->textElem)
		this->textElem->MoveOverTime(time, this->getX() + 25.f, this->getY());

	if (this->boxElem)
		this->boxElem->MoveOverTime(time, this->getX() + 1.f, this->getY() + 1.f);

	if (this->checkElem)
		this->checkElem->MoveOverTime(time, this->getX() + 3.f, this->getY() + 3.f);

	if (this->borders[0])
		this->borders[0]->MoveOverTime(time, this->getX(), this->getY());

	if (this->borders[1])
		this->borders[1]->MoveOverTime(time, this->getX(), this->getY() + 16.f);

	if (this->borders[2])
		this->borders[2]->MoveOverTime(time, this->getX(), this->getY());

	if (this->borders[3])
		this->borders[3]->MoveOverTime(time, this->getX() + 16.f, this->getY());
}

void CheckBox::show()
{
	int time = 0;

	this->bVisible = true;

	if (this->boxElem)
		this->boxElem->FadeOverTime(time, 0, 0, 0, 255);

	if (this->checkElem)
		this->checkElem->FadeOverTime(time, 47.f, 128.f, 237.f, this->Checked() ? 255.f : 0.f);

	if (this->textElem)
		this->textElem->FadeOverTime(time, 255, 255, 255, 255);

	if (this->borders[0])
		this->borders[0]->FadeOverTime(time, 47, 128, 237, 255);

	if (this->borders[1])
		this->borders[1]->FadeOverTime(time, 47, 128, 237, 255);

	if (this->borders[2])
		this->borders[2]->FadeOverTime(time, 47, 128, 237, 255);

	if (this->borders[3])
		this->borders[3]->FadeOverTime(time, 47, 128, 237, 255);

}

void CheckBox::hide()
{
	int time = 0;

	this->bVisible = false;

	if (this->boxElem)
		this->boxElem->FadeOverTime(time, 0, 0, 0, 0);

	if (this->checkElem)
		this->checkElem->FadeOverTime(time, 0, 255, 0, 0);

	if (this->textElem)
		this->textElem->FadeOverTime(time, 255, 255, 255, 0);

	if (this->borders[0])
		this->borders[0]->FadeOverTime(time, 47, 128, 237, 0);

	if (this->borders[1])
		this->borders[1]->FadeOverTime(time, 47, 128, 237, 0);

	if (this->borders[2])
		this->borders[2]->FadeOverTime(time, 47, 128, 237, 0);

	if (this->borders[3])
		this->borders[3]->FadeOverTime(time, 47, 128, 237, 0);
}

bool CheckBox::Checked()
{
	return this->bChecked;
}

void CheckBox::setChecked(bool checked)
{
	this->bChecked = checked;
}

std::string CheckBox::getText()
{
	return this->text;
}

void CheckBox::setText(std::string text)
{
	this->text = text;
	this->textElem->ChangeText(text);
	this->setSize(getStringWidth(this->text, this->fontScale, this->font) + 25, 15);
}

CheckBox::CheckBox(guiObject *parent) : guiObject(parent, ObjectType::OBJ_CheckBox)
{
	if (parent) {
		parent->addChild(this);
		this->setEnabled(parent->Enabled());
	}

	this->boxElem = new game_hudelem_s();
	this->checkElem = new game_hudelem_s();
	this->textElem = new game_hudelem_s();
	this->borders[0] = new game_hudelem_s();
	this->borders[1] = new game_hudelem_s();
	this->borders[2] = new game_hudelem_s();
	this->borders[3] = new game_hudelem_s();

	this->bChecked = false;

	this->textColor[0] = 255;
	this->textColor[1] = 255;
	this->textColor[2] = 255;
	this->textColor[3] = 255;

	this->text = std::string("label");

	this->font = 0;
	this->fontScale = 12.f;

	this->setPosition(200, 200);
	this->setSize(getStringWidth(this->text, this->fontScale, this->font) + 25, 15);

	

	float x = this->getX(),
		y = this->getY(),
		width = this->getWidth(),
		height = this->getHeight();

	this->borders[0]->SetShader(x, y, 17.f, 1.f, 47, 128, 237, this->Enabled() ? 255.f : 0.f);
	this->borders[1]->SetShader(x, y + 16.f, 17.f, 1.f, 47, 128, 237, this->Enabled() ? 255.f : 0.f);
	this->borders[2]->SetShader(x, y, 1.f, 17.f, 47, 128, 237, this->Enabled() ? 255.f : 0.f);
	this->borders[3]->SetShader(x + 16.f, y, 1.f, 17.f, 47, 128, 237, this->Enabled() ? 255.f : 0.f);

	this->boxElem->SetShader(x + 1, y + 1, 15.f, 15.f, 0, 0, 0, this->Enabled() ? 255.f : 0.f);
	this->checkElem->SetShader(x + 3, y + 3, 11, 11, 0, 255, 0, 0);
	this->textElem->SetText(this->text, x + 25, y, this->font, this->fontScale, false, false, false, 255.f, 255.f, 255.f, this->Enabled() ? 255.f : 0);


	this->addEvent(eventClick, CheckBox_Click);
}