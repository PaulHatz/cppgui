#pragma once
#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  TextInput : public guiObject
#else
class _declspec(dllimport)  TextInput : public guiObject
#endif
{
protected:
	game_hudelem_s *bodyElem;
	game_hudelem_s *cursorElem;
	game_hudelem_s *selectionElem;
	game_hudelem_s *textElem;

	float padding[2];
	unsigned int fontName;


	void updateBaseGuiElements(int time);
	void showBaseElems();
	void hideBaseElems();

	void setTextOffset(size_t textOffset);

	virtual void moveCursor();
	virtual void updateSelectionElems(size_t start, size_t count);

	virtual void blinkCursor();
	virtual void hideCursor();

	virtual void updateGuiElements(int time);
	virtual void show();
	virtual void hide();

	//Use this to filter out undesired characters.
	//Example: only return true with numbers on a numericUpDown
	virtual bool isCharacterAllowed(UINT key);
	virtual void processCustomizedInputCustom(UINT key);
	virtual void updateValue(std::string newValue);

private:
	std::string placeholder;
	std::string text;
	size_t textOffset;

	bool bFocus;
	size_t select_startIndex;
	size_t select_stopIndex;

	ULONGLONG lastClickTime;
	int clickCount;
	bool bSelecting;

	float fontSize;

	class Timer *timer1;

	void DeselectText();
	void SelectAll();

	void updateTextElems();
	
public:

	void setText(std::string text);
	std::string getText();

	void setPlaceHolder(std::string placeholder);
	std::string getPlaceholder();

	bool isFocused();
	float getFontSize();
	void setFontSize(float fontSize);
	void setFocused(bool value);

	TextInput(guiObject *parent, ObjectType objectType);

	friend void TextInput_Click(guiObject *sender, EventArgs *e);
	friend void TextInput_Focus(guiObject *sender, EventArgs *e);
	friend void TextInput_Drag(guiObject *sender, EventArgs *e);
	friend size_t TextInput_resolveCursorPos(TextInput *TextInput, float *cursorPos);
	friend void TextInput_Drop(guiObject *sender, EventArgs *e);
	friend void TextInput_KeyPress(guiObject *sender, EventArgs *e);
	friend void TextInput_RightClick(guiObject *sender, EventArgs *e);
	friend void TextInput_SelectAll_Click(guiObject *sender, EventArgs *e);
	friend void TextInput_Delete_Click(guiObject *sender, EventArgs *e);

};