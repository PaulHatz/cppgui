#include "main.h"

void Form_MinimizeButtonPressed(guiObject *sender, EventArgs *e)
{
	Form *currentForm = (Form *)sender->getParent();
	currentForm->setEnabled(false);
	currentForm->hide();
}

void Form_KeyPressedF5(guiObject *sender, EventArgs *e)
{
	Form *currentForm = (Form *)sender;
	currentForm->setEnabled(true);
	currentForm->show();
}

void Form::setMinSize(float minWidth, float minHeight)
{
	this->minWidth = minWidth;
	this->minHeight = minHeight;
}

void Form::setMaxSize(float maxWidth, float maxHeight)
{
	this->maxWidth = maxWidth;
	this->maxHeight = maxHeight;
}

void Form::setResizeable(bool isResizable)
{
	this->bResizable = isResizable;
}

void Form::setClosable(bool isClosable)
{
	this->bCanBeClosed = isClosable;
}

void Form::setColor(float r, float g, float b, float a)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
	this->color[3] = a;
}

void Form::setTitle(std::string title)
{
	this->title = title;
	this->titleElem->ChangeText(title);
}

void Form::updateGuiElements(int time)
{
	float x = this->getX(), y = this->getY();
	float width = this->getWidth(), height = this->getHeight();

	if (draggableTopbar != nullptr) {
		this->draggableTopbar->setPosition(x, y);
		this->draggableTopbar->setSize(width, 30.f);
	}

	if (this->elem)
		this->elem->MoveOverTime(time, x + 2.f, y + 30.f);
	if (this->borders[0])
		this->borders[0]->MoveOverTime(time, x, y);
	if (this->borders[1])
		this->borders[1]->MoveOverTime(time, x + width - 2.f, y);
	if (this->borders[2])
		this->borders[2]->MoveOverTime(time, x + 2.f, y + height);
	if (this->borders[3])
		this->borders[3]->MoveOverTime(time, x + 2.f, y);
	if (this->titleElem)
		this->titleElem->MoveOverTime(time, x + 2.f, y + 5.f);
	if (this->minimizeBtnElem)
		this->minimizeBtnElem->MoveOverTime(time, x + this->getWidth() - 60.f, y + 5.f);


	this->updateChildren();
}

void Form::show()
{
	this->bVisible = true;

	int time = 0;

	if (this->elem)
		this->elem->FadeOverTime(time, this->color[0], this->color[1], this->color[2], this->color[3]);
	if (this->borders[0])
		this->borders[0]->FadeOverTime(time, 47, 128, 237, 255);

	if (this->borders[1])
		this->borders[1]->FadeOverTime(time, 47, 128, 237, 255);

	if (this->borders[2])
		this->borders[2]->FadeOverTime(time, 47, 128, 237, 255);

	if (this->borders[3])
		this->borders[3]->FadeOverTime(time, 47, 128, 237, 255);

	if (this->titleElem)
		this->titleElem->FadeOverTime(time, 255, 255, 255, 255);

	if (this->minimizeBtnElem)
		this->minimizeBtnElem->FadeOverTime(time, 255, 255, 255, 255);

	for (auto child : this->getChildren()) {
		child->show();
	}
}

void Form::hide()
{
	this->bVisible = false;

	int time = 0;
	if (this->elem)
		this->elem->FadeOverTime(time, this->color[0], this->color[1], this->color[2], 0);
	if (this->borders[0])
		this->borders[0]->FadeOverTime(time, 47.f, 128.f, 237.f, 0.f);

	if (this->borders[1])
		this->borders[1]->FadeOverTime(time, 47.f, 128.f, 237.f, 0.f);

	if (this->borders[2])
		this->borders[2]->FadeOverTime(time, 47.f, 128.f, 237.f, 0.f);

	if (this->borders[3])
		this->borders[3]->FadeOverTime(time, 47.f, 128.f, 237.f, 0.f);

	if (this->titleElem)
		this->titleElem->FadeOverTime(time, 255.f, 255.f, 255.f, 0.f);

	if (this->minimizeBtnElem)
		this->minimizeBtnElem->FadeOverTime(time, 255, 255, 255, 0.f);

	for (auto child : this->getChildren()) {
		child->hide();
	}
}

void Form_Drag(guiObject *sender, EventArgs *e)
{
	guiObject *parent = sender->getParent();
	
	float pos[2] = { 0 };
	
	memcpy(pos, guiApplication->getCursorInfo()->cursorPosition, 8);
	
	float newXPos = (pos[0] + guiApplication->getCursorInfo()->offset[0]);
	float newYPos = (pos[1] + guiApplication->getCursorInfo()->offset[1]);
	
	parent->setPosition(newXPos, newYPos);
}

void Form_Unhover(guiObject *sender, EventArgs *e)
{
	//UI::_SET_CURSOR_SPRITE(1);
}

void Form_Hover(guiObject *sender, EventArgs *e)
{
	//UI::_SET_CURSOR_SPRITE(4);
}

Form::Form(guiObject *parent) : guiObject(parent, ObjectType::OBJ_Form)
{
	this->draggableTopbar = nullptr;

	this->elem = new game_hudelem_s();
	this->borders[0] = new game_hudelem_s();
	this->borders[1] = new game_hudelem_s();
	this->borders[2] = new game_hudelem_s();
	this->borders[3] = new game_hudelem_s();
	this->titleElem = new game_hudelem_s();
	this->minimizeBtnElem = new game_hudelem_s();


	this->setPosition(100, 100);
	this->setSize(720, 500);
	this->setResizeable(false);
	this->setClosable(false);
	this->setColor(0, 0, 0, 180);
	this->setEnabled(true);
	this->addEvent(eventF5Pressed, Form_KeyPressedF5);


	float x = this->getX();
	float y = this->getY();

	float width = this->getWidth();
	float height = this->getHeight();

	this->draggableTopbar = new guiObject(this);
	this->addChild(this->draggableTopbar);
	this->draggableTopbar->setPosition(this->getX(), this->getY());
	this->draggableTopbar->setSize(this->getWidth(), 30.f);
	this->draggableTopbar->addEvent(eventDrag, Form_Drag);

	//this->draggableTopbar->addEvent("hover", Form_Hover);
	//this->draggableTopbar->addEvent("unhover", Form_Unhover);

	this->minimizeBtn = new guiObject(this);
	this->addChild(this->minimizeBtn);
	this->minimizeBtn->setEnabled(true);
	this->minimizeBtn->setPosition(x + width - 60.f, y + 5.f);
	this->minimizeBtn->setSize(30, 20);
	this->minimizeBtn->addEvent(eventClick, Form_MinimizeButtonPressed);

	this->elem->SetShader(x + 2.f, y + 30.f, width - 4.f, height - 30.f, this->color[0], this->color[1], this->color[2], this->color[3]);
	this->borders[0]->SetShader(x, y, 2.f, height + 2.f, 47.f, 128.f, 237.f, 255.f); //Left
	this->borders[1]->SetShader(x + width - 2.f, y, 2.f, height + 2.f, 47.f, 128.f, 237.f, 255.f); //Right
	this->borders[2]->SetShader(x + 2.f, y + height, width - 4.f, 2.f, 47.f, 128.f, 237.f, 255.f); //Bottom
	this->borders[3]->SetShader(x + 2.f, y, width - 4.f, 30.f, 47.f, 128.f, 237.f, 255.f); //Top
	this->titleElem->SetText("", x + 2.f, y + 5.f, 0, 16.f, false, false, false, 255.f, 255.f, 255.f, 255.f);
	this->minimizeBtnElem->SetShader(x + width - 60.f, y + 5.f, 30, 20, 255.f, 255.f, 255.f, 255.f);


}