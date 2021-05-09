#pragma once
#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  TabControl : public guiObject
#else
class _declspec(dllimport)  TabControl : public guiObject
#endif
{
private:

	std::vector<TabPage *> pages;

	TabPage *activeTabPage;

	game_hudelem_s *backgroundElem;

public:
	//Override guiObject methods
	void show();
	void hide();
	void updateGuiElements(int time);
	void setEnabled(bool value);


	//Class-specific methods
	std::vector<TabPage *> getTabPages();
	
	void changeTabPage(TabPage *newPage);

	TabPage *getActiveTabPage();


	TabPage *addNewTabPage(std::string text);

	TabControl(guiObject *parent);

	friend void TabControl_Click(guiObject *sender, TabChangeEventArgs *e);
};

