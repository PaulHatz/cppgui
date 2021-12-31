#pragma once

enum class ObjectType
{
	OBJ_None,
	OBJ_Other,
	OBJ_Form,
	OBJ_DialogBox,
	OBJ_GroupBox,
	OBJ_TabControl,
	OBJ_TabPage,
	OBJ_Label,
	OBJ_Button,
	OBJ_CheckBox,
	OBJ_RadioButton,
	OBJ_MenuStrip,
	OBJ_MenuStripButton,
	OBJ_TextBox,
	OBJ_NumericUpDown,
	OBJ_DataGridView,
	OBJ_DataGridViewRow,
	OBJ_DataGridViewCell,
	OBJ_TrackBar,
};

#ifdef CPPGUI_DLLMODE
class _declspec(dllexport) guiObject
#else
class _declspec(dllimport) guiObject
#endif
{
private:
	ObjectType objectType;

	std::vector< guiObject *> children;


	guiObject *parent;

	float x, y;
	float width, height;

	float offsetX, offsetY;

protected:
	bool bEnabled;
	bool bVisible;

public:
	void setPosition(float x, float y);
	void setSize(float width, float height);

	void updateChildren();

	virtual void show();
	virtual void hide();

	//virtual void showGuiElements(int time);
	//virtual void hideGuiElements(int time);
	virtual void updateGuiElements(int time);


	void addEvent(EventList eventName, std::function<void(guiObject *, EventArgs *)> function);
	
	float getX();
	float getY();
	float getOffsetX();
	float getOffsetY();

	ObjectType getObjectType();
	void setObjectType(ObjectType objectType);


	float getWidth();
	float getHeight();

	void addChild(guiObject *obj);
	std::vector<guiObject *> getChildren();

	guiObject *getParent();


	virtual void setEnabled(bool value);
	bool Enabled();

	bool Visible();


	guiObject(guiObject *parent);
	guiObject(guiObject *parent, ObjectType objectType);
};

extern std::vector <guiObject *> globalGuiObjectArray;