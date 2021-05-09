#pragma once
#include "Object.h"
#ifdef CPPGUI_DLLMODE
class _declspec(dllexport)  TrackBar : public guiObject
#else
class _declspec(dllimport)  TrackBar : public guiObject
#endif
{
private:
	float value;
	float minValue;
	float maxValue;
	
	game_hudelem_s *lineElem;
	game_hudelem_s *selectorElem;
	
public:

	void show();
	void hide();
	void updateGuiElements(int time);

	void setMinimum(float value);
	void setMaximum(float value);
	void setValue(float value);

	TrackBar(guiObject *parent);

	friend void TrackBar_Drag(guiObject *obj, EventArgs *e);
	friend void TrackBar_Click(guiObject *obj, EventArgs *e);
};

