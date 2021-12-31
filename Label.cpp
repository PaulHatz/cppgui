#include "main.h"

void Label::setFont(int fontIndex)
{
	this->font = fontIndex;
}

void Label::setFontScale(float fontScale)
{
	this->fontScale = fontScale;
	this->textElem->elem->fontSize = this->fontScale;
}

void Label::setColor(float r, float g, float b, float a)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
	this->color[3] = a;

	this->updateGuiElements(0);
}

void Label::setOutline(bool value)
{
	this->bOutlined = value;
}

void Label::setCentered(bool value)
{
	this->bCentered = value;
}

void Label::setJustified(bool value)
{
	this->bJustified = value;
}

void Label::setText(std::string text)
{
	this->text = text;

	this->setSize(getStringWidth(this->text, this->fontScale, this->font), getStringHeight(this->text, this->fontScale, this->font));

	this->textElem->ChangeText(text);

	this->updateGuiElements(0);

	guiApplication->sendEvent(eventValueChanged, this);
}

void Label::updateGuiElements(int time)
{
	if (this->textElem) {
		this->textElem->MoveOverTime(time, this->getX(), this->getY());
	}
}

void Label::show()
{
	this->bVisible = true;

	if (this->textElem)
		this->textElem->FadeOverTime(0, this->color[0], this->color[1], this->color[2], 255.f);
}

void Label::hide()
{
	this->bVisible = false;

	if (this->textElem)
		this->textElem->FadeOverTime(0, this->color[0], this->color[1], this->color[2], 0.f);
}

Label::Label(guiObject *parent) : guiObject(parent, ObjectType::OBJ_Label)
{
	if (parent) {
		parent->addChild(this);
	}

	this->textElem = new game_hudelem_s();

	this->text = std::string("label");

	this->font = 0;
	this->fontScale = 12.f;
	
	this->bCentered = false;
	this->bJustified = false;
	this->bOutlined = false;
	
	color[0] = 255.f;
	color[1] = 255.f;
	color[2] = 255.f;
	color[3] = 255.f;

	this->setSize(getStringWidth(this->text, this->fontScale, this->font), getStringHeight(this->text, this->fontScale, this->font));

	this->textElem->SetText(this->text, this->getX(), this->getY(), this->font, this->fontScale, this->bJustified, this->bCentered, this->bOutlined, this->color[0], this->color[1], this->color[2], this->Enabled() ? this->color[3] : 0);
}

