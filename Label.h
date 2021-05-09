#pragma once
#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  Label : public guiObject
#else
class _declspec(dllimport)  Label : public guiObject
#endif
{
private:

	unsigned int font;
	float fontScale;


	bool bOutlined;
	bool bCentered;
	bool bJustified;

	float color[4];

	std::string text;

	game_hudelem_s *textElem;
public:

	void setFont(int fontIndex);
	void setFontScale(float fontScale);
	void setColor(float r, float g, float b, float a);
	void setOutline(bool value);
	void setCentered(bool value);
	void setJustified(bool value);

	
	void setText(std::string text);

	void updateGuiElements(int time);
	void show();
	void hide();

	Label(guiObject *parent);
};

