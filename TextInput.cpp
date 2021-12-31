#include "main.h"


size_t TextInput_resolveCursorPos(TextInput *textInput, float *cursorPos = nullptr)
{
	std::string text = textInput->getText();

	//Should we use an inputted cursor position or the current one. Important for text highlighting on selection
	float offsetX = 0.f;
	if(cursorPos != nullptr)
		offsetX = cursorPos[0] - (textInput->getX() + textInput->padding[0]);
	else offsetX = guiApplication->getCursorInfo()->cursorPosition[0] - (textInput->getX() + textInput->padding[0]);

	float stringWidth = getStringWidth(text, textInput->getFontSize(), 0);

	size_t len = strlen(text.c_str());

	if (!text.empty()) {

		if (offsetX >= stringWidth)
			return len;

		if (offsetX <= getStringWidth(text.substr(0, 1), textInput->getFontSize(), 0))
			return 0;

		float currentWidth = 0.f;
		size_t idx = 0;

		do {
			if (idx + 1 >= len)
				break;

			idx++;

			currentWidth = getStringWidth(textInput->getText().substr(0, idx + 1), textInput->getFontSize(), 0);

		} while (currentWidth <= offsetX);

		return idx;

	}
	return 0;
}

void TextInput_SelectAll_Click(guiObject *sender, EventArgs *e)
{
	auto textInput = (TextInput *)e;

	if (textInput) {
		switch (textInput->getObjectType()) {
		case ObjectType::OBJ_TextBox:
		case ObjectType::OBJ_NumericUpDown:
		{

			if(textInput->bFocus)
				textInput->SelectAll();
		}
			break;

		default: break;
		}
	}

}

void TextInput_Delete_Click(guiObject *sender, EventArgs *e)
{
	auto textInput = (TextInput *)e;

	if (textInput) {
		switch (textInput->getObjectType()) {
		case ObjectType::OBJ_TextBox:
		case ObjectType::OBJ_NumericUpDown:
		{
			if (textInput->bFocus) {
				if (textInput->select_startIndex != -1 || textInput->select_stopIndex != -1) {

					size_t start = min(textInput->select_startIndex, textInput->select_stopIndex );
					size_t stop = max(textInput->select_startIndex, textInput->select_stopIndex);

					textInput->text.erase(start, stop - start);
					textInput->DeselectText();
					textInput->updateValue(textInput->text);
					textInput->updateTextElems();

					textInput->textOffset = start;
					textInput->moveCursor();
				}
			}
		}
		break;

		default: break;
		}
	}
}

void TextInput_Click(guiObject *sender, EventArgs *e)
{
	auto textInput = (TextInput *)sender;

	if (!e)
		textInput->DeselectText();

	if (!textInput->bFocus) {
		textInput->setFocused(true);
		guiApplication->sendEvent(eventFocus, sender);

		auto oldFocusedObject = guiApplication->getFocusedObject();

		if (oldFocusedObject != nullptr) {
			if (oldFocusedObject->getObjectType() == ObjectType::OBJ_MenuStrip)
				oldFocusedObject->hide();
			else {
				auto focusedObject = (TextInput *)guiApplication->getFocusedObject();
				focusedObject->setFocused(false);
			}
		}

		guiApplication->setFocusedObject(textInput);
	}

	size_t newTextOffset = TextInput_resolveCursorPos(textInput);

	if (textInput->textOffset == newTextOffset) {
		textInput->clickCount++;
	}
	else textInput->clickCount = 1;

	ULONGLONG delta = GetTickCount64() - textInput->lastClickTime;
	textInput->lastClickTime = GetTickCount64();

	if (textInput->clickCount >= 2) {
		if (delta <= 400 && textInput->text.size() > 0) {
			textInput->select_startIndex = 0;
			textInput->select_stopIndex = textInput->text.size();
			textInput->updateGuiElements(0);
		}

		textInput->clickCount = 0;
	}

	textInput->textOffset = newTextOffset;

	textInput->moveCursor();
}

void TextInput_RightClick(guiObject *sender, EventArgs *e)
{
	auto textInput = (TextInput *)sender;

	EventArgs test = {};

	TextInput_Click(sender, &test);

	for (auto child : textInput->getChildren()) {
		if (child->getObjectType() == ObjectType::OBJ_MenuStrip) {

			auto menuStrip = (MenuStrip *)child;

			if (!child->Enabled())
				child->show();

			child->setPosition(guiApplication->getCursorInfo()->cursorPosition[0], guiApplication->getCursorInfo()->cursorPosition[1]);

			break;
		}
	}
}

void TextInput_Drag(guiObject *sender, EventArgs *e)
{
	auto textInput = (TextInput *)sender;

	if (!textInput->bFocus) {
		textInput->bFocus = true;
		guiApplication->sendEvent(eventFocus, sender);

		if (guiApplication->getFocusedObject() != nullptr) {
			auto focusedObject = (TextInput *)guiApplication->getFocusedObject();
			focusedObject->bFocus = false;
		}

		guiApplication->setFocusedObject(textInput);
	}

	if (!textInput->bSelecting) {
		textInput->bSelecting = true;

		textInput->select_startIndex = TextInput_resolveCursorPos(textInput, guiApplication->getCursorInfo()->pStartPoint);
		textInput->select_stopIndex = TextInput_resolveCursorPos(textInput);

		size_t start = min(textInput->select_startIndex, textInput->select_stopIndex);
		size_t stop = max(textInput->select_startIndex, textInput->select_stopIndex);
		size_t count = stop - start;

		textInput->textOffset = start;

		textInput->updateSelectionElems(start, count);
	}

	else {
		textInput->select_stopIndex = TextInput_resolveCursorPos(textInput);

		size_t start = min(textInput->select_startIndex, textInput->select_stopIndex);
		size_t stop = max(textInput->select_startIndex, textInput->select_stopIndex);
		size_t count = stop - start;

		textInput->textOffset = textInput->select_stopIndex;

		textInput->updateSelectionElems(start, count);
		textInput->moveCursor();
	}
}

void TextInput_Drop(guiObject *sender, EventArgs *e)
{
	auto textInput = (TextInput *)sender;
	size_t start = min(textInput->select_startIndex, textInput->select_stopIndex);
	size_t stop = max(textInput->select_startIndex, textInput->select_stopIndex);
	size_t count = stop - start;

	textInput->bSelecting = false;

	float strWidth = (count != 0) ? getStringWidth(textInput->getText().substr(start, count), textInput->getFontSize(), 0) : 0.f;

	float x = getStringWidth(textInput->getText().substr(0, textInput->select_startIndex), textInput->getFontSize(), 0);

	textInput->updateSelectionElems(start, count);
}

void TextInput_Focus(guiObject *sender, EventArgs *e)
{
	auto textInput = (TextInput *)sender;

	if (textInput->bFocus) {
		if (textInput->timer1->timerReady()) {
			textInput->blinkCursor();
		}
		guiApplication->sendEventIgnoreExisting(eventFocus, sender);
	}
	else {
		textInput->updateValue(textInput->text);
		textInput->hideCursor();
		textInput->DeselectText();
	}
}

void TextInput_Hover(guiObject *sender, EventArgs *e)
{
	guiApplication->getCursorInfo()->hCursor = LoadCursor(NULL, IDC_IBEAM);
}

void TextInput_Unhover(guiObject *sender, EventArgs *e)
{
	guiApplication->getCursorInfo()->hCursor = LoadCursor(NULL, IDC_ARROW);
}

void TextInput_KeyPress(guiObject *sender, EventArgs *e)
{
	auto textInput = (TextInput *)sender;

	UINT key = (UINT)e;

	if (textInput->bFocus) {
		switch (key) {

		case 0x01:
			textInput->SelectAll();
			break;

		case 0x08: //Backspace
		{
			size_t start = min(textInput->select_startIndex, textInput->select_stopIndex);
			size_t stop = max(textInput->select_startIndex, textInput->select_stopIndex);
			size_t count = stop - start;

			if (start != stop) {
				textInput->text.erase(start, count);
				textInput->bSelecting = false;
				textInput->textOffset = start;

				textInput->DeselectText();
			}
			else {
				if (textInput->textOffset > 0) {
					textInput->text.erase(textInput->text.begin() + textInput->textOffset - 1);
					textInput->textOffset--;
				}
			}
			textInput->updateTextElems();
			textInput->moveCursor();
			break;
		}


		case 0x7F: //Ctrl+Backspace
			if (textInput->textOffset > 0) {
				size_t pos = textInput->textOffset;
				size_t count = 0;

				do {
					if (textInput->text.c_str()[pos] != ' ') {
						count++;
						pos--;
					}
					else {
						if (count == 1 && pos == textInput->textOffset - 1) {
							count++;
							pos--;
						}
						else {
							textInput->text.erase(pos + 1, count - 1);
							textInput->textOffset = pos + 1;
							textInput->updateTextElems();
							textInput->moveCursor();
							break;
						}
					}

				} while (pos > 0);

				if (pos == 0) {
					textInput->text.erase(pos, count);
					textInput->textOffset = 0;
					textInput->updateValue(textInput->text);
					textInput->updateTextElems();
					textInput->moveCursor();
				}
			}
			break;

		case KEYPRESS_DEL:

			if (textInput->select_startIndex != -1 || textInput->select_stopIndex != -1) {
				size_t start = min(textInput->select_startIndex, textInput->select_stopIndex);
				size_t stop = max(textInput->select_startIndex, textInput->select_stopIndex);

				textInput->text.erase(start, stop - start);
				textInput->DeselectText();
				textInput->updateValue(textInput->text);
				textInput->updateTextElems();

				textInput->textOffset = start;
				textInput->moveCursor();
			}

			else if (textInput->textOffset < textInput->text.size()) {
				textInput->text.erase(textInput->textOffset, 1);
				textInput->updateTextElems();
				textInput->moveCursor();

			}

			break;

		case  KEYPRESS_RIGHT:
		case KEYPRESS_LEFT:
		{
			int n = key == KEYPRESS_LEFT ? -1 : 1;

			if ((n == -1 && textInput->textOffset + n != -1) || (n == 1 && textInput->textOffset + n <= textInput->text.size())) {

				bool ctrlPressed = (GetKeyState(VK_CONTROL) & 0x100) != 0 ? true : false;
				bool shiftPressed = (GetKeyState(VK_SHIFT) & 0x100) != 0 ? true : false;

				size_t newTextOffset = textInput->textOffset + n;

				if (ctrlPressed)
					newTextOffset = n == -1 ? 0 : textInput->text.size();

				if (shiftPressed) {

					size_t start = textInput->select_startIndex;
					size_t stop = textInput->select_stopIndex;

					if (start == -1)
						start = (n == 1) ? textInput->textOffset : newTextOffset;
					if (stop == -1)
						stop = (n == 1) ? newTextOffset : textInput->textOffset;
					else {

						size_t *a = nullptr;
						size_t *b = nullptr;
						size_t bound = 0;

						if (n == -1) {
							a = &stop;
							b = &start;
							bound = 0;
						}
						else {
							a = &start;
							b = &stop;
							bound = textInput->text.size();
						}

						if (*a == textInput->textOffset) {
							if (ctrlPressed) {
								*a = *b;
								*b = bound;
							}
							else {
								*a += n;
								if (*a == *b)
									textInput->DeselectText();
							}
						}
						else {
							if ((n == -1 && int(*b + n) >= 0) || (n == 1 && int(*b + n) <= bound)) {
								if (ctrlPressed)
									*b = bound;
								else *b += n;
							}
						}
					}

					textInput->select_startIndex = start;
					textInput->select_stopIndex = stop;
				}

				if (!shiftPressed && (textInput->select_startIndex != -1 || textInput->select_stopIndex != -1)) {
					textInput->DeselectText();
					textInput->textOffset = ctrlPressed ? newTextOffset : textInput->textOffset;
				}
				else textInput->textOffset = newTextOffset;

				textInput->updateValue(textInput->text);
				textInput->updateGuiElements(0);
			}
			break;
		}
		case  KEYPRESS_UP:
		case  KEYPRESS_DOWN:
			break;

		case 0x00:
		case 0x02:
		case 0x03: //Ctrl+C
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x07:
		case 0x09:
		case 0x0A:
		case 0x0B:
		case 0x0C:
		case 0x0D:
		case 0x0E:
		case 0x0F:
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15:
		case 0x16: //Ctrl+V
		case 0x17:
		case 0x18: //Ctrl+X
		case 0x19:
			break;

		default:

			if (textInput->isCharacterAllowed(key)) {
				if (textInput->select_startIndex != -1 && textInput->select_stopIndex != -1) {
					size_t start = min(textInput->select_startIndex, textInput->select_stopIndex);
					size_t stop = max(textInput->select_startIndex, textInput->select_stopIndex);
					size_t count = stop - start;

					textInput->text.erase(start, count);
					textInput->DeselectText();

					textInput->textOffset = start;
				}

				textInput->text.insert(textInput->text.begin() + textInput->textOffset, key);

				textInput->textOffset++;

				textInput->updateTextElems();
				textInput->moveCursor();
			}


			break;
		}

		textInput->processCustomizedInputCustom(key);
	}
}

bool TextInput::isFocused()
{
	return this->bFocus;
}

float TextInput::getFontSize()
{
	return this->fontSize;
}

void TextInput::setFontSize(float fontSize)
{
	this->fontSize = fontSize;

	if (this->textElem && this->textElem->elem)
		this->textElem->elem->fontSize = fontSize;
}

void TextInput::setFocused(bool value)
{
	this->bFocus = value;

	for (auto child : this->getChildren()) {
		if (child->getObjectType() == ObjectType::OBJ_MenuStrip) {
			auto menuStrip = (MenuStrip *)child;

			if (menuStrip->Enabled()) {
				menuStrip->hide();
			}

			break;
		}
	}
}

void TextInput::DeselectText()
{
	if (this->selectionElem && this->selectionElem->elem) {
		this->selectionElem->MoveOverTime(0, this->getX() + this->padding[0], this->getY());
		this->selectionElem->ScaleOverTime(0, 1, this->getHeight());
		this->selectionElem->FadeOverTime(0, 0, 128, 255, 0);
	}

	this->select_startIndex = -1;
	this->select_stopIndex = -1;
}

void TextInput::SelectAll()
{
	this->select_startIndex = 0;
	this->select_stopIndex = this->text.size();
	this->textOffset = 0;
	this->moveCursor();

	this->updateSelectionElems(0, this->text.size());
}

void TextInput::updateTextElems()
{
	if (this->textElem != nullptr && this->textElem->elem != nullptr) {
		if (this->text.empty()) {
			this->textElem->ChangeText(this->placeholder);
			this->textElem->FadeOverTime(0, 128.f, 128.f, 128.f, this->Enabled() ? 255.f : 0.f);
		}

		else {
			this->textElem->ChangeText(this->text);
			this->textElem->FadeOverTime(0, 0.f, 0.f, 0.f, this->Enabled() ? 255.f : 0.f);
		}
	}
	else printf("Error\n");
}

void TextInput::moveCursor()
{
	if (this->cursorElem && this->cursorElem->elem) {
		std::string str = this->text.substr(0, this->textOffset);

		float strWidth = getStringWidth(str, this->getFontSize(), 0);

		if (this->textOffset > 0)
			this->cursorElem->MoveOverTime(100, this->getX() + this->padding[0] + strWidth - 1, this->getY());
		else
			this->cursorElem->MoveOverTime(100, this->getX() + this->padding[0] + strWidth, this->getY());
	}

}

void TextInput::updateSelectionElems(size_t start, size_t count)
{
	float strWidth = (count != 0) ? getStringWidth(this->getText().substr(start, count), this->getFontSize(), 0) : 0.f;

	float x = this->getX() + this->padding[0] + getStringWidth(this->text.substr(0, start), this->getFontSize(), 0);

	this->selectionElem->ScaleOverTime(0, strWidth, this->getHeight());
	this->selectionElem->MoveOverTime(0, x, this->getY());
	this->selectionElem->FadeOverTime(0, 0, 128, 255, 255);
}

void TextInput::blinkCursor()
{
	if (this->cursorElem && this->cursorElem->elem) {
		this->cursorElem->FadeOverTime(50, 0.f, 0.f, 0.f, this->cursorElem->elem->color[3] == 0 ? 255.f : 0.f);
	}
}

void TextInput::hideCursor()
{
	if (this->cursorElem && this->cursorElem->elem)
		this->cursorElem->FadeOverTime(50, 0.f, 0.f, 0.f, 0.f);
}

void TextInput::setText(std::string text)
{
	this->text = text;

	this->updateTextElems();
}

std::string TextInput::getText()
{
	return std::string(this->text);
}

void TextInput::setPlaceHolder(std::string placeholder)
{
	this->placeholder = placeholder;

	this->updateTextElems();
}

std::string TextInput::getPlaceholder()
{
	return std::string(this->placeholder);
}

void TextInput::updateBaseGuiElements(int time)
{
	if (this->bodyElem && this->bodyElem->elem) {
		this->bodyElem->MoveOverTime(time, this->getX(), this->getY());
		this->bodyElem->ScaleOverTime(time, this->getWidth(), this->getHeight());
	}

	if (this->textElem) {
		this->textElem->MoveOverTime(time, this->getX() + this->padding[0], this->getY() + this->padding[1]);
	}

	if (this->cursorElem) {


		std::string str = this->text.substr(0, this->textOffset);

		float strWidth = getStringWidth(str, this->getFontSize(), 0);


		this->cursorElem->ScaleOverTime(100, 1.f, this->getHeight());

		if (this->textOffset > 0)
			this->cursorElem->MoveOverTime(100, this->getX() + this->padding[0] + strWidth - 1.f, this->getY());
		else
			this->cursorElem->MoveOverTime(100, this->getX() + this->padding[0] + strWidth, this->getY());
	}


	if (this->select_startIndex != -1 && this->select_stopIndex != -1) {
		size_t start = min(this->select_startIndex, this->select_stopIndex);
		size_t stop = max(this->select_startIndex, this->select_stopIndex);
		size_t count = stop - start;

		if (this->selectionElem) {

			float strWidth = (count != 0) ? getStringWidth(this->getText().substr(start, count), this->getFontSize(), 0) : 0.f;

			float x = this->getX() + this->padding[0] + getStringWidth(this->text.substr(0, start), this->getFontSize(), 0);

			this->selectionElem->MoveOverTime(0, x, this->getY());
			this->selectionElem->ScaleOverTime(0, strWidth, this->getHeight());
			this->selectionElem->FadeOverTime(0, 0, 128, 255, 255);
		}
	}
	else DeselectText();
}

void TextInput::showBaseElems()
{
	if (this->bodyElem && this->bodyElem->elem)
		this->bodyElem->FadeOverTime(0, 255, 255, 255, 255);

	if (this->textElem && this->textElem->elem) {
		if(!this->text.empty())
			this->textElem->FadeOverTime(0, 0, 0, 0, 255);
		else this->textElem->FadeOverTime(0, 128, 128, 128, 255);

	}
}

void TextInput::hideBaseElems()
{
	this->bFocus = false;

	if (this->bodyElem && this->bodyElem->elem)
		this->bodyElem->FadeOverTime(0, 255.f, 255.f, 255.f, 0.f);

	if (this->selectionElem && this->selectionElem->elem)
		this->selectionElem->FadeOverTime(0, 0.f, 0.f, 255.f, 0.f);

	if (this->cursorElem && this->cursorElem->elem)
		this->cursorElem->FadeOverTime(0, 0.f, 0.f, 0.f, 0.f);

	if (this->textElem && this->textElem->elem)
		this->textElem->FadeOverTime(0, 0.f, 0.f, 0.f, 0.f);
}

void TextInput::setTextOffset(size_t textOffset)
{
	this->textOffset = textOffset;
	this->moveCursor();
}

//Virtual funtion
void TextInput::updateGuiElements(int time)
{
}

//Virtual funtion
void TextInput::show()
{
	this->bVisible = true;
}

//Virtual funtion
void TextInput::hide()
{
	this->bVisible = false;
}

//Virtual funtion
bool TextInput::isCharacterAllowed(UINT key)
{
	return true;
}

void TextInput::processCustomizedInputCustom(UINT key)
{
}

//Virtual funtion
void TextInput::updateValue(std::string newValue)
{
}

TextInput::TextInput(guiObject *parent, ObjectType objectType) : guiObject(parent, objectType)
{
	if (parent) {
		parent->addChild(this);
		this->setEnabled(parent->Enabled());
	}

	this->bodyElem = new game_hudelem_s();
	this->selectionElem = new game_hudelem_s();
	this->cursorElem = new game_hudelem_s();
	this->textElem = new game_hudelem_s();

	this->setPosition(0, 0);
	this->setSize(0, 0);

	this->text = std::string();
	this->placeholder = std::string();

	this->fontSize = 12.f;

	this->padding[0] = 4.f;
	this->padding[1] = 2.f;

	this->select_startIndex = -1;
	this->select_stopIndex = -1;

	this->timer1 = new Timer(500);

	this->bFocus = false;
	this->textOffset = 0;

	this->bodyElem->SetShader(this->getX(), this->getY(), this->getWidth(), this->getHeight(), 255, 255, 255, this->Enabled() ? 255.f : 0.f);
	this->selectionElem->SetShader(this->getX(), this->getY(), this->getWidth(), this->getHeight(), 0, 0, 255, this->Enabled() ? 255.f : 0.f);
	this->cursorElem->SetShader(this->getX() + this->padding[0], this->getY() + this->padding[1], 1.f, this->getHeight(), 0.f, 0.f, 0.f, 0.f);
	this->textElem->SetText(this->text, this->getX() + this->padding[0], this->getY() + this->padding[1], this->fontName, this->getFontSize(), false, false, false, 0.f, 0.f, 0.f, this->Enabled() ? 255.f : 0.f);


	MenuStrip *menuStrip = new MenuStrip(this);
	menuStrip->addOption("Cut");
	menuStrip->addOption("Copy");
	menuStrip->addOption("Paste");
	menuStrip->addOption("Delete", TextInput_Delete_Click);
	menuStrip->addOption("Select All", TextInput_SelectAll_Click);

	this->addEvent(eventClick, TextInput_Click);
	this->addEvent(eventFocus, TextInput_Focus);
	this->addEvent(eventHover, TextInput_Hover);
	this->addEvent(eventUnhover, TextInput_Unhover);
	this->addEvent(eventDrag, TextInput_Drag);
	this->addEvent(eventDrop, TextInput_Drop);
	this->addEvent(eventKeyPress, TextInput_KeyPress);
	this->addEvent(eventRightClick, TextInput_RightClick);
}