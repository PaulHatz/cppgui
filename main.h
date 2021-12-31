#pragma once

#define CPPGUI_DLLMODE
 

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <queue>


#include "Timer.h"

#include "Huds.h"


#include "Functions.h"

#include "Event.h" 
#include "Object.h"
#include "Form.h"
#include "DialogBox.h"
#include "GroupBox.h"
#include "TabControl.h"
#include "TabPage.h"
#include "Label.h"
#include "Button.h"
#include "CheckBox.h"
#include "RadioButton.h"
#include "TextInput.h"
#include "TextBox2.h"
#include "TrackBar.h"
#include "NumericUpDown.h"
#include "DataGridView.h"
#include "DataGridViewRow.h"
#include "MenuStrip.h"
#include "MenuStripButton.h"


#include "GUI.h"

#include "Menu.h"

#define KEYPRESS_DEL 0x44454C
#define KEYPRESS_UP 0x5550
#define KEYPRESS_DOWN 0x444F574E
#define KEYPRESS_LEFT 0x4C454654
#define KEYPRESS_RIGHT 0x52495445

extern GUI *guiApplication;


__declspec(dllimport) void __cdecl initializeWindow(WNDPROC WndProc2, void(*DrawingFuntion)());
__declspec(dllimport) void __cdecl drawBox(float x, float y, float w, float h, float r, float g, float b, float a);
__declspec(dllimport) void __cdecl drawText(const char *text, float x, float y, class Font *font, float fontSize, float r, float g, float b, float a);
__declspec(dllexport) class Font *__cdecl getRobotoFont();
__declspec(dllimport) float __cdecl getTextWidth(const char *text, class Font *font, float fontSize);
__declspec(dllimport) float __cdecl getTextHeight(const char *text, Font *font, float fontSize);
__declspec(dllimport) HWND __cdecl getWindowHWND();
