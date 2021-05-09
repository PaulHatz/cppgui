#pragma once
#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  TextBox2 : public TextInput
#else
class _declspec(dllimport)  TextBox2 : public TextInput
#endif
{
private:

public:

	void updateGuiElements(int time);
	void show();
	void hide();


	TextBox2(guiObject *parent);
};