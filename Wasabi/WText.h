/*********************************************************************
******************* W A S A B I   E N G I N E ************************
copyright (c) 2016 by Hassan Al-Jawaheri
desc.: Wasabi Engine text component
*********************************************************************/

#pragma once

#include "Wasabi.h"

typedef struct W_FONT_OBJECT {
	unsigned int ID;
	std::string name;
	void* cdata;
	int num_chars;
	int char_height;
	class WImage* img;
} W_FONT_OBJECT;

class WTextComponent {
	typedef struct W_RENDERING_TEXT {
		std::string str;
		W_FONT_OBJECT font;
		WColor col;
		float fHeight;
		int x, y;
	} W_RENDERING_TEXT;

public:
	WTextComponent(Wasabi* app);
	~WTextComponent();

	void AddFontDirectory(std::string dir);
	WError Initialize();

	WError CreateFont(unsigned int ID, std::string fontName);
	WError DestroyFont(unsigned int ID);

	WError SetTextColor(WColor col);
	WError SetFont(unsigned int ID);
	WError RenderText(std::string text, int x, int y, float fHeight);
	WError RenderText(std::string text, int x, int y, float fHeight, unsigned int fontID);
	WError RenderText(std::string text, int x, int y, float fHeight, unsigned int fontID, WColor col);
	void Render(class WRenderTarget* rt);

	unsigned int GetTextWidth(std::string text, float fHeight, unsigned int fontID = -1);

protected:
	Wasabi* m_app;
	std::vector<std::string> m_directories;
	std::map<unsigned int, W_FONT_OBJECT> m_fonts;
	vector<W_RENDERING_TEXT> m_texts;
	unsigned int m_curFont;
	WColor m_curColor;
	class WGeometry* m_textGeometry;
	class WMaterial* m_textMaterial;
};