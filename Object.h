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

union guiObjectUnion 
{
	class guiObject *unkObject;
	class Form *formObj;
	class GuiDialogBox *guiDialogBoxObj;
	class GroupBox *groupBoxObj;
	class TabControl *tabControlObj;
	class TabPage *tabPageObj;
	class Label *labelObj;
	class Button *buttonObj;
	class CheckBox *checkBoxObj;
	class RadioButton *radioButtonObj;
	class MenuStrip *menuStripObj;
	class MenuStripButton *menuStripButtonObj;
	class TextBox2 *textBoxObj;
	class NumericUpDown *numericUpDownObj;
	class DataGridView *dataGridViewObj;	
	class DataGridViewRow *dataGridViewRowObj;
	class DataGridViewCell *dataGridViewCellObj;
	class TrackBar *trackBarObj;
};


#ifdef CPPGUI_DLLMODE
class _declspec(dllexport) guiObject
#else
class _declspec(dllimport) guiObject
#endif
{
private:
	ObjectType objectType;
	guiObjectUnion guiObjectPtr;

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

	guiObject(guiObject *parent, class Form *thisForm);
	guiObject(guiObject *parent, class GuiDialogBox *thisGuiDialogBox);
	guiObject(guiObject *parent, class Label *thisLabel);
	guiObject(guiObject *parent, class GroupBox *thisGroupBox);
	guiObject(guiObject *parent, class TabControl *thisTabControl);
	guiObject(guiObject *parent, class TabPage *thisTabPage);
	guiObject(guiObject *parent, class Button *thisButton);
	guiObject(guiObject *parent, class CheckBox *thisCheckBox);
	guiObject(guiObject *parent, class RadioButton *thisRadioButton);
	guiObject(guiObject *parent, class MenuStrip *thisMenuStrip);
	guiObject(guiObject *parent, class MenuStripButton *thisMenuStripButton);
	guiObject(guiObject *parent, class DataGridView *thisDataGridView);
	guiObject(guiObject *parent, class DataGridViewRow *thisDataGridViewRow);
	guiObject(guiObject *parent, class DataGridViewCell *thisDataGridViewCell);
	guiObject(guiObject *parent, class TrackBar *thisTrackBar);


	guiObject(guiObject *parent, class TextInput *thisTextInput, ObjectType objectType);
	guiObject(guiObject *parent, class TextBox *thisTextBox);
};

extern std::vector <guiObject *> globalGuiObjectArray;