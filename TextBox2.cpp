#include "main.h"


void TextBox2::updateGuiElements(int time)
{
	this->updateBaseGuiElements(time);
}

void TextBox2::show()
{
	this->bVisible = true;

	this->showBaseElems();
}

void TextBox2::hide()
{
	this->bVisible = false;

	this->hideBaseElems();
}

TextBox2::TextBox2(guiObject *parent) : TextInput(parent, ObjectType::OBJ_TextBox)
{
	//Set default position, size, and placeholder
	this->setPosition(460, 250);
	this->setSize(200, 25.f);
	this->setFontSize(12.f);
	this->setPlaceHolder("Placeholder");	
}