#include "main.h"

GuiDialogBox *GuiMessageBox = nullptr;

void btnClick(guiObject *obj, EventArgs *e)
{
	auto dialogBox = (GuiDialogBox *)obj->getParent();

	guiApplication->setActiveForm(dialogBox->previousActiveForm);
	dialogBox->previousActiveForm->setEnabled(true);

	dialogBox->setEnabled(false);
	dialogBox->hide();
}

void GuiDialogBox_Drag(guiObject *sender, EventArgs *e)
{
	guiObject *parent = sender->getParent();

	float pos[2] = { 0 };

	memcpy(pos, guiApplication->getCursorInfo()->cursorPosition, 8);

	float newXPos = (pos[0] + guiApplication->getCursorInfo()->offset[0]);
	float newYPos = (pos[1] + guiApplication->getCursorInfo()->offset[1]);

	parent->setPosition(newXPos, newYPos);
}

void GuiDialogBox::show()
{
	if (this->backGround)
		this->backGround->FadeOverTime(0, 0, 0, 0, 250.f);
	
	if (this->titleElem)
		this->titleElem->FadeOverTime(0, 255.f, 255.f, 255.f, 255.f);

	for (int i = 0; i < 4; i++) {
		if (this->borders[i])
			this->borders[i]->FadeOverTime(0, 47.f, 128.f, 237.f, 255.f);
	}
	
	for (auto child : this->getChildren()) {
		child->show();
	}
}

void GuiDialogBox::hide()
{
	if (this->backGround)
		this->backGround->FadeOverTime(0, 0, 0, 0, 0);

	if (this->titleElem)
		this->titleElem->FadeOverTime(0, 255.f, 255.f, 255.f, 0.f);

	for (int i = 0; i < 4; i++) {
		if (this->borders[i])
			this->borders[i]->FadeOverTime(0, 47.f, 128.f, 237.f, 0.f);
	}

	for (auto child : this->getChildren()) {
		child->hide();
	}
}

void GuiDialogBox::updateGuiElements(int time)
{
	float x = this->getX();
	float y = this->getY();
	float width = this->getWidth();
	float height = this->getHeight();

	if (this->backGround)
		this->backGround->MoveOverTime(time, x, y);


	if (this->titleElem)
		this->titleElem->MoveOverTime(time, x + 10.f, y + 5.f);

	if (this->borders[0] != nullptr) {
		this->borders[0]->MoveOverTime(time, x, y);
		this->borders[0]->ScaleOverTime(time, 2.f, height + 2.f);
	}

	if (this->borders[1] != nullptr) {
		this->borders[1]->MoveOverTime(time, x + width - 2.f, y);
		this->borders[1]->ScaleOverTime(time, 2.f, height + 2.f);
	}

	if (this->borders[2] != nullptr) {
		this->borders[2]->MoveOverTime(time, x + 2.f, y + height);
		this->borders[2]->ScaleOverTime(time, width - 4.f, 2.f);
	}

	if (this->borders[3] != nullptr) {
		this->borders[3]->MoveOverTime(time, x + 2.f, y);
		this->borders[3]->ScaleOverTime(time, width - 4.f, 30.f);
	}
}

void GuiDialogBox::initializeDialogBox(std::string message)
{
	this->textLabel = new Label(this);
	textLabel->setPosition(this->getX() + 20.f, this->getY() + 50.f);
	textLabel->setFontScale(14.f);
	textLabel->setText(message);

	Button *btn = new Button(this);
	btn->setPosition(this->getX() + this->getWidth() - 60.f, this->getY() + this->getHeight() - 35.f);
	btn->setSize(50.f, 25.f);
	btn->setText("Okay");

	btn->addEvent(eventClick, btnClick);
}

void GuiDialogBox::Show(std::string message)
{
	if (!GuiMessageBox) {
		GuiMessageBox = new GuiDialogBox(nullptr);
		GuiMessageBox->initializeDialogBox(message);
	}

	GuiMessageBox->previousActiveForm = guiApplication->getActiveForm();
	GuiMessageBox->previousActiveForm->setEnabled(false);

	guiApplication->setActiveForm(GuiMessageBox);

	GuiMessageBox->titleElem->ChangeText("");
	GuiMessageBox->setEnabled(true);
	GuiMessageBox->show();

}

void GuiDialogBox::Show(std::string message, std::string title)
{
	if (!GuiMessageBox) {
		GuiMessageBox = new GuiDialogBox(nullptr);
		GuiMessageBox->initializeDialogBox(message);
	}

	GuiMessageBox->previousActiveForm = guiApplication->getActiveForm();
	GuiMessageBox->previousActiveForm->setEnabled(false);

	guiApplication->setActiveForm(GuiMessageBox);
	GuiMessageBox->textLabel->setText(message);
	GuiMessageBox->titleElem->ChangeText(title);
	GuiMessageBox->setEnabled(true);
	GuiMessageBox->show();

}

GuiDialogBox::GuiDialogBox(guiObject *parent) : guiObject(parent, ObjectType::OBJ_DialogBox)
{
	if (parent) {
		this->setEnabled(false);
	}

	this->setPosition(100.f, 100.f);
	this->setSize(400.f, 200.f);

	this->previousActiveForm = nullptr;

	this->backGround = new game_hudelem_s();

	for (int i = 0; i < 4; i++)
		this->borders[i] = new game_hudelem_s();

	titleElem = new game_hudelem_s();


	float x = this->getX();
	float y = this->getY();
	float width = this->getWidth();
	float height = this->getHeight();

	guiObject *dragHitBox = new guiObject(this);
	dragHitBox->setSize(width, 30.f);
	dragHitBox->setPosition(x, y);
	dragHitBox->addEvent(eventDrag, GuiDialogBox_Drag);

	this->addChild(dragHitBox);

	this->backGround->SetShader(x, y, width, height, 0, 0, 0, 0);
	this->titleElem->SetText("", x + 10.f, y + 5.f, 0, 16.f, false, false, false, 255.f, 255.f, 255.f, 0.f);

	this->borders[0]->SetShader(x, y, 2.f, height + 2.f, 47.f, 128.f, 237.f, 0); //Left
	this->borders[1]->SetShader(x + width - 2.f, y, 2.f, height + 2.f, 47.f, 128.f, 237.f, 0); //Right
	this->borders[2]->SetShader(x + 2.f, y + height, width - 4.f, 2.f, 47.f, 128.f, 237.f, 0); //Bottom
	this->borders[3]->SetShader(x + 2.f, y, width - 4.f, 30.f, 47.f, 128.f, 237.f, 0); //Top
}
