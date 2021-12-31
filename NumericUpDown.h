#pragma once
#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  NumericUpDown : public TextInput
#else
class _declspec(dllimport)  NumericUpDown : public TextInput
#endif
{
private:
	float min;
	float max;
	float incr;

	float value;

	bool isCharacterAllowed(UINT key);
	void updateValue(std::string newValue);
	void processCustomizedInputCustom(UINT key);

	Button *incrButton;
	Button *decrButton;

public:

	void updateGuiElements(int time);
	void show();
	void hide();

	void setMinimum(float min);
	void setMaximum(float max);
	void setIncrement(float incr);

	NumericUpDown(guiObject *parent);

	friend void incrButton_Click(guiObject *obj, EventArgs *e);
	friend void decrButton_Click(guiObject *obj, EventArgs *e);
};