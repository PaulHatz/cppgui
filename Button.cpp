#include "main.h"

void Button_Hover(guiObject *obj, EventArgs *e)
{
	auto button = (Button *)obj;
	
	if(button->Enabled())
		button->buttonElem->FadeOverTime(250, button->buttonHoverColor[0], button->buttonHoverColor[1], button->buttonHoverColor[2], button->buttonHoverColor[3]);
}

void Button_Unhover(guiObject *obj, EventArgs *e)
{
	auto button = (Button *)obj;

	button->buttonElem->FadeOverTime(250, button->buttonColor[0], button->buttonColor[1], button->buttonColor[2], button->Visible() ? 255.f : 0.f);
}

/*
	Override guiObject::updateGuiElements(int time)
	Modify all hud elems in this object to updated information
*/
void Button::updateGuiElements(int time)
{	
	if (this->buttonElem) {
		this->buttonElem->MoveOverTime(time, this->getX(), this->getY());
		this->buttonElem->ScaleOverTime(time, this->getWidth(), this->getHeight());
		this->buttonElem->FadeOverTime(time, this->buttonColor[0], this->buttonColor[1], this->buttonColor[2], this->Enabled() ? this->buttonColor[3] : 0);
	}
		
	if (this->textElem) {
		float textWidth = getStringWidth(this->text, this->fontSize, this->textElem->elem->font);
		float textHeight = getStringHeight(this->text, this->fontSize, this->textElem->elem->font);
												  
		float textX = 0.f; 

		switch (this->textAlign) {
		case ButtonText_Align::ButtonText_Center:
			textX = floor(this->getX() + (this->getWidth() / 2.f) - (textWidth / 2.f));
			break;
		case ButtonText_Align::ButtonText_Left:
			textX = this->getX() + 6.f;
			break;
		default: break;
		}



		float textY = floor(this->getY() + (this->getHeight() / 2.f) - (textHeight / 2.f) - 1);

		this->textElem->MoveOverTime(time, textX, textY);
		this->textElem->FadeOverTime(time, this->textColor[0], this->textColor[1], this->textColor[2], this->Enabled() ? this->textColor[3] : 0);
		this->textElem->ChangeText(text);
	}
}

/*
	Override guiObject::show()
	This method makes all hud elems of the object visible
	
*/
void Button::show()
{
	this->bVisible = true;

	if (this->buttonElem != nullptr)
		this->buttonElem->FadeOverTime(250, this->buttonColor[0], this->buttonColor[1], this->buttonColor[2], 255);

	if (this->textElem != nullptr)
		this->textElem->FadeOverTime(250, this->textColor[0], this->textColor[1], this->textColor[2], 255);
}

/*
	Override guiObject::hide()
	This method makes all hud elems of the object invisible
*/
void Button::hide()
{
	this->bVisible = false;

	if (this->buttonElem)
		this->buttonElem->FadeOverTime(250, this->buttonColor[0], this->buttonColor[1], this->buttonColor[2], 0);

	if (this->textElem)
		this->textElem->FadeOverTime(250, this->textColor[0], this->textColor[1], this->textColor[2], 0);

}

/*
	void Button::setText(std::string text)
	This method changes the string of the text in the button and triggers the hud elems to update with the updated infos.
*/
void Button::setText(std::string text)
{
	this->text = text;

	this->updateGuiElements(0);
}

/*
	void Button::setColor(float r, float g, float b, float a)
	This method sets the background color of the button and triggers the hud elems to update with the updated infos.
*/
void Button::setColor(float r, float g, float b, float a)
{
	this->buttonColor[0] = r;
	this->buttonColor[1] = g;
	this->buttonColor[2] = b;
	this->buttonColor[3] = a;

	this->updateGuiElements(0);
}

/*
	void Button::setTextColor(float r, float g, float b, float a)
	This method changes the color of the text in the button and triggers the hud elems to update with the new infos.
*/
void Button::setTextColor(float r, float g, float b, float a)
{
	this->textColor[0] = r;
	this->textColor[1] = g;
	this->textColor[2] = b;
	this->textColor[3] = a;
	
	this->updateGuiElements(0);
}

/*
	void Button::setHoverColor(float r, float g, float b, float a)
	This method changes  the color of the button when a user is highlighting over the button.
*/
void Button::setHoverColor(float r, float g, float b, float a)
{
	this->buttonHoverColor[0] = r;
	this->buttonHoverColor[1] = g;
	this->buttonHoverColor[2] = b;
	this->buttonHoverColor[3] = a;
}

void Button::setTextAlign(ButtonText_Align newAlign)
{
	this->textAlign = newAlign;
	this->updateGuiElements(0);
}

Button::Button(guiObject *parent) : guiObject(parent, ObjectType::OBJ_Button)
{
	if (parent) {
		parent->addChild(this);
		this->setEnabled(parent->Enabled());
	}

	this->buttonElem = new game_hudelem_s();
	this->textElem = new game_hudelem_s();

	this->setSize(60.f, 20.f);
	this->addEvent(eventHover, Button_Hover);
	this->addEvent(eventUnhover, Button_Unhover);

	this->fontSize = 12.f;

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

	this->textAlign = ButtonText_Align::ButtonText_Center;

	//Default button text
	this->text = "button";

	this->buttonElem->SetShader(this->getX(), this->getY(), this->getWidth(), this->getHeight(), this->buttonColor[0], this->buttonColor[1], this->buttonColor[2], this->Enabled() ? 255.f : 0.f);
	this->textElem->SetText(this->text, this->getX(), this->getY(), 0, this->fontSize, false, false, false, this->textColor[0], this->textColor[1], this->textColor[2], this->Enabled() ? 255.f : 0.f);

	this->bVisible = this->Enabled();

}																																					 



