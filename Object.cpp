#include "main.h"

 std::vector <guiObject *> globalGuiObjectArray;

void guiObject::setPosition(float x, float y)
{
	if (this->x == x && this->y == y)
		return;

	this->x = x;
	this->y = y;

	if (this->parent) {
		this->offsetX = this->x - this->parent->getX();
		this->offsetY = this->y - this->parent->getY();
	}

	for (guiObject *child : this->children) {
		child->setPosition(this->x + child->offsetX, this->y + child->offsetY);
	}

	this->updateGuiElements(0);
}

void guiObject::setSize(float width, float height)
{
	this->width = width;
	this->height = height;

	this->updateGuiElements(0);
}

void guiObject::updateChildren()
{
	for (guiObject *child : this->children) {
		child->updateGuiElements(0);
	}
}

void guiObject::show()
{
	this->bVisible = true;

	for (auto child : this->getChildren()) {
		child->show();
	}
}

void guiObject::hide()
{
	this->bVisible = false;

	for (auto child : this->getChildren()) {
		child->hide();
	}
}

void guiObject::updateGuiElements(int time)
{
	for (auto child : this->getChildren()) {
		child->updateGuiElements(time);
	}
}

void guiObject::addEvent(EventList eventName, std::function<void(guiObject *, EventArgs *)> function)
{
	guiApplication->addEvent(this, eventName, function);
}

float guiObject::getX()
{
	return this->x;
}

float guiObject::getY()
{
	return this->y;
}

float guiObject::getOffsetX()
{
	return this->offsetX;
}

float guiObject::getOffsetY()
{
	return this->offsetY;
}

ObjectType guiObject::getObjectType()
{
	return this->objectType;
}

void guiObject::setObjectType(ObjectType objectType)
{
	this->objectType = objectType;
}

float guiObject::getWidth()
{
	return this->width;
}

float guiObject::getHeight()
{
	return this->height;
}

void guiObject::addChild(guiObject *obj)
{
	this->children.push_back(obj);
}

std::vector<guiObject *> guiObject::getChildren()
{
	return this->children;
}

guiObject *guiObject::getParent()
{
	return this->parent;
}

void guiObject::setEnabled(bool value)
{
	this->bEnabled = value;

	for (auto child : this->getChildren()) {
		child->setEnabled(value);
	}
}

bool guiObject::Enabled()
{
	return this->bEnabled;
}

bool guiObject::Visible()
{
	return this->bVisible;
}

guiObject::guiObject(guiObject *parent)
{
	this->objectType = ObjectType::OBJ_Other;

	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, ObjectType objectType)
{
	this->objectType = objectType;
	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->offsetX = 0;
	this->offsetY = 0;
	this->width = 0;
	this->height = 0;
	globalGuiObjectArray.push_back(this);
}