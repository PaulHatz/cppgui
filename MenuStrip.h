#pragma once

#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  MenuStrip : public guiObject
#else
class _declspec(dllimport)  MenuStrip : public guiObject
#endif
{
private:
	//game_hudelem_s *backgroundElem;

	bool bOpened;
	guiObject *oldFocused;

	size_t objCount;

public:

	void updateGuiElements(int time);
	void show();
	void hide();
	void setEnabled(bool value);

	void addOption(std::string text, std::function<void(guiObject *, EventArgs *)> function = nullptr);

	MenuStrip(guiObject *parent);

	friend void Button_RightClick(guiObject *obj, EventArgs *e);
};