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
	this->guiObjectPtr.unkObject = nullptr;

	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, Form *thisForm)
{
	this->objectType = ObjectType::OBJ_Form;
	this->guiObjectPtr.formObj = thisForm;
	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, GuiDialogBox *thisGuiDialogBox)
{
	this->objectType = ObjectType::OBJ_DialogBox;
	this->guiObjectPtr.guiDialogBoxObj = thisGuiDialogBox;
	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, Label *thisLabel)
{
	this->objectType = ObjectType::OBJ_Label;
	this->guiObjectPtr.labelObj = thisLabel;
	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, GroupBox *thisGroupBox)
{
	this->objectType = ObjectType::OBJ_GroupBox;
	this->guiObjectPtr.groupBoxObj = thisGroupBox;
	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, TabControl *thisTabControl)
{
	this->objectType = ObjectType::OBJ_TabControl;
	this->guiObjectPtr.tabControlObj = thisTabControl;
	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, TabPage *thisTabPage)
{
	this->objectType = ObjectType::OBJ_TabPage;
	this->guiObjectPtr.tabPageObj = thisTabPage;
	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, Button *thisButton)
{
	this->objectType = ObjectType::OBJ_Button;
	this->guiObjectPtr.buttonObj = thisButton;
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

guiObject::guiObject(guiObject *parent, CheckBox *thisCheckBox)
{
	this->objectType = ObjectType::OBJ_CheckBox;
	this->guiObjectPtr.checkBoxObj = thisCheckBox;
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

guiObject::guiObject(guiObject *parent, RadioButton *thisRadioButton)
{
	this->objectType = ObjectType::OBJ_RadioButton;
	this->guiObjectPtr.radioButtonObj = thisRadioButton;
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

guiObject::guiObject(guiObject *parent, MenuStrip *thisMenuStrip)
{
	this->objectType = ObjectType::OBJ_MenuStrip;
	this->guiObjectPtr.menuStripObj = thisMenuStrip;
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

guiObject::guiObject(guiObject *parent, MenuStripButton *thisMenuStripButton)
{
	this->objectType = ObjectType::OBJ_MenuStripButton;
	this->guiObjectPtr.menuStripButtonObj = thisMenuStripButton;
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

guiObject::guiObject(guiObject *parent, DataGridView *thisDataGridView)
{
	this->objectType = ObjectType::OBJ_DataGridView;
	this->guiObjectPtr.dataGridViewObj = thisDataGridView;
	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, DataGridViewRow *thisDataGridViewRow)
{
	this->objectType = ObjectType::OBJ_DataGridViewRow;
	this->guiObjectPtr.dataGridViewRowObj = thisDataGridViewRow;
	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, DataGridViewCell *thisDataGridViewCell)
{
	this->objectType = ObjectType::OBJ_DataGridViewCell;
	this->guiObjectPtr.dataGridViewCellObj = thisDataGridViewCell;
	this->parent = parent;
	this->setEnabled(true);

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	globalGuiObjectArray.push_back(this);
}

guiObject::guiObject(guiObject *parent, TrackBar *thisTrackBar)
{
	this->objectType = ObjectType::OBJ_TrackBar;
	this->guiObjectPtr.trackBarObj = thisTrackBar;

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

guiObject::guiObject(guiObject *parent, TextInput *thisTextInput, ObjectType objectType)
{
	this->objectType = objectType;
	this->guiObjectPtr.unkObject = thisTextInput;

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
