#include "main.h"

void MenuStripButton_Hover(guiObject *obj, EventArgs *e)
{
	auto button = (MenuStripButton *)obj;

	if (button->Enabled()) {
		if (button->backgroundElem != nullptr)
			button->backgroundElem->FadeOverTime(250, button->buttonHoverColor[0], button->buttonHoverColor[1], button->buttonHoverColor[2], button->buttonHoverColor[3]);
	}
}

void MenuStripButton_Unhover(guiObject *obj, EventArgs *e)
{
	auto button = (MenuStripButton *)obj;
	if(button->backgroundElem != nullptr)
	button->backgroundElem->FadeOverTime(250, button->buttonColor[0], button->buttonColor[1], button->buttonColor[2], button->Visible() ? 255.f : 0.f);
}

void MenuStripButton::show()
{
	if (this->getParent()->getObjectType() == ObjectType::OBJ_MenuStrip) {
		auto menuStrip = (MenuStrip *)this->getParent();

		this->initElems();

		//If MenuStrip is being used.
		if (menuStrip->Enabled()) {

			if (this->backgroundElem != nullptr) {

				this->backgroundElem->FadeOverTime(0, this->buttonColor[0], this->buttonColor[1], this->buttonColor[2], 255);
				this->textElem->FadeOverTime(0, this->textColor[0], this->textColor[1], this->textColor[2], 255);
			}

			this->bVisible = true;
		}
	}
}

void MenuStripButton::hide()
{
	this->destroyElems();

	this->bVisible = false;
}

void MenuStripButton::updateGuiElements(int time)
{
	if (this->backgroundElem) {
		this->backgroundElem->MoveOverTime(time, this->getX(), this->getY());
		this->backgroundElem->ScaleOverTime(time, this->getWidth(), this->getHeight());
	}

	if (this->textElem) {
		float textHeight = getStringHeight(this->text, 12.f, this->textElem->elem->font);
		float y = floor(this->getY() + (this->getHeight() / 2.f) - (textHeight / 2.f) - 1);
		this->textElem->MoveOverTime(time, this->getX() + 6.f, y);
	}
}


void MenuStripButton::initElems()
{
	if (!this->backgroundElem) {
		this->backgroundElem = new game_hudelem_s();
		this->backgroundElem->SetShader(this->getX(), this->getY(), this->getWidth(), this->getHeight(), this->buttonColor[0], this->buttonColor[1], this->buttonColor[2], 0);
	}

	if (!this->textElem) {
		this->textElem = new game_hudelem_s();
		float textHeight = getStringHeight(this->text, 12.f, this->textElem->elem->font);
		this->textElem->SetText(this->text, this->getX() + 6.f, floor(this->getY() + (this->getHeight() / 2.f) - (textHeight / 2.f) - 1), 0, 12.f, false, false, false, this->textColor[0], this->textColor[1], this->textColor[2], 0);
	}
}

void MenuStripButton::destroyElems()
{
	if (this->backgroundElem) {
		delete this->backgroundElem;
		this->backgroundElem = nullptr;
		guiApplication->setHudElemCount(guiApplication->getHudElemCount() - 1);
	}

	if (this->textElem) {
		delete this->textElem;
		this->textElem = nullptr;
		guiApplication->setHudElemCount(guiApplication->getHudElemCount() - 1);
	}
}

void MenuStripButton::setText(std::string text)
{
	this->text = text;
}

MenuStripButton::MenuStripButton(guiObject *parent) : guiObject(parent, ObjectType::OBJ_MenuStripButton)
{
	if (parent) {
		parent->addChild(this);
		this->setEnabled(parent->Enabled());
	}

	this->text = std::string("MenuStripButton");

	this->setSize(60.f, 20.f);
	this->addEvent(eventHover, MenuStripButton_Hover);
	this->addEvent(eventUnhover, MenuStripButton_Unhover);


	//Default blue button color
	this->buttonColor[0] = 47.f;
	this->buttonColor[1] = 128.f;
	this->buttonColor[2] = 237.f;
	this->buttonColor[3] = 255.f;

	//Default Darker blue  color for when hovering
	this->buttonHoverColor[0] = 0.f;
	this->buttonHoverColor[1] = 0.f;
	this->buttonHoverColor[2] = 205.f;
	this->buttonHoverColor[3] = 255.f;

	this->textColor[0] = 255.f;
	this->textColor[1] = 255.f;
	this->textColor[2] = 255.f;
	this->textColor[3] = 255.f;
}
