#include "main.h"

void MenuStrip_ButtonClick(guiObject *obj, EventArgs *e)
{
	if (obj != nullptr) {
		auto parent = obj->getParent();

		if (parent->getObjectType() == ObjectType::OBJ_MenuStrip) {
			auto menuStrip = (MenuStrip *)parent;

			//Invoke action onto parent of MenuStrip, ex: TextInput for SelectAll
			guiApplication->sendEvent(eventClick, *obj->getChildren().begin(), (EventArgs *)parent->getParent());

			parent->hide();
		}
	}
}

void MenuStrip_ButtonEmptyClick(guiObject *obj, EventArgs *e)
{
	printf("This button has not yet been implemented.\n");
}

void MenuStrip::updateGuiElements(int time)
{
	this->updateChildren();
}

void MenuStrip::show()
{
	this->bVisible = true;

	this->oldFocused = guiApplication->getFocusedObject();

	this->bOpened = true;
	this->setEnabled(true);


	this->objCount = this->getChildren().size();


	for (auto child : this->getChildren()) {
		child->show();
	}

	guiApplication->setFocusedObject(this);
}

void MenuStrip::hide()
{
	this->bVisible = false;

	this->bOpened = false;
	this->setEnabled(false);

	for (auto child : this->getChildren()) {
		child->hide();
	}
	
	if (this->oldFocused) {
		auto textInput = (TextInput *)this->oldFocused;
		if(textInput->isFocused())
			guiApplication->setFocusedObject(this->oldFocused);
	}

}

void MenuStrip::setEnabled(bool value)
{
	if (this->bOpened == value) {
		this->bEnabled = value;

		for (auto child : this->getChildren()) {
			child->setEnabled(value);
		}
	}
}

void MenuStrip::addOption(std::string text, std::function<void(guiObject *, EventArgs *)> function)
{
	auto newOption = new MenuStripButton(this);

	float pos_x = this->getX();
	float pos_y = this->getY();

	newOption->setText(text);
	newOption->setEnabled(false);
	newOption->setSize(120.f, 20.f);

	this->setSize(newOption->getWidth(), this->getHeight() + newOption->getHeight());

	newOption->setPosition(pos_x, pos_y + this->getHeight() - newOption->getHeight());
	newOption->addEvent(eventClick, MenuStrip_ButtonClick);

	auto optEv = new guiObject(newOption);
	optEv->addEvent(eventClick, function == nullptr ? MenuStrip_ButtonEmptyClick : function);
	newOption->addChild(optEv);

	this->addChild(newOption);
}

MenuStrip::MenuStrip(guiObject *parent) : guiObject(parent, ObjectType::OBJ_MenuStrip)
{
	if (parent) {
		parent->addChild(this);
	}
	this->setEnabled(false);

	this->setSize(0, 0);
	this->setPosition(this->getParent()->getX(), this->getParent()->getY());

	this->oldFocused = nullptr;
	this->bOpened = false;
	this->objCount = 0;
}