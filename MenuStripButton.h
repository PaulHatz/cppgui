#pragma once

#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  MenuStripButton : public guiObject
#else
class _declspec(dllimport)  MenuStripButton : public guiObject
#endif
{
private:
    game_hudelem_s *backgroundElem;
    game_hudelem_s *textElem;

    float buttonColor[4];
    float buttonHoverColor[4];
    float textColor[4];


    std::string text;

public:
    void show();
    void hide(); 
    void updateGuiElements(int time);

    void initElems();
    void destroyElems();

    void setText(std::string text);

    MenuStripButton(guiObject *parent);

    friend void MenuStripButton_Hover(guiObject *obj, EventArgs *e);
    friend void MenuStripButton_Unhover(guiObject *obj, EventArgs *e);

};

