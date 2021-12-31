#pragma once

#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  Form : public guiObject
#else
class _declspec(dllimport)  Form : public guiObject
#endif
{
private:
	float minWidth, minHeight;
	float maxWidth, maxHeight;

	float color[4];

	bool bDraggable;
	bool bResizable;
	bool bCanBeClosed;

	std::string title;

	class guiObject *draggableTopbar;
	class guiObject *minimizeBtn;

	class game_hudelem_s *elem;
	class game_hudelem_s *borders[4];
	class game_hudelem_s *titleElem;
	class game_hudelem_s *minimizeBtnElem;

	class GuiDialogBox *dialogBox;

public:

	void setMinSize(float minWidth, float minHeight);
	void setMaxSize(float maxWidth, float maxHeight);
	void setResizeable(bool isResizable);
	void setClosable(bool isClosable);
	void setColor(float r, float g, float b, float a);
	void setTitle(std::string title);

	//void showDialog();
	
	void updateGuiElements(int time);

	void show();
	void hide();

	Form(guiObject *parent);

};
