#include <SDL_ttf.h>
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "invoker.h"


void setRect(SDL_Rect* rect, int x, int y, int width, int height) {
	rect->x = x;
	rect->y = y;
	rect->w = width;
	rect->h = height;
}

void setColor(SDL_Color* color, int r, int g, int b, int a) {
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
}

void init(Menu* menu, int lastSaved) {

	//tools
	menu->toolsCounter = 5;
	menu->tools = (ToolButton*)malloc(menu->toolsCounter * sizeof(ToolButton));
	menu->currentTool = 0;

	menu->tools[0].text = "pen";
	setRect(&menu->tools[0].rect, 110, 10, 50, 20);
	menu->tools[0].tool = PEN;

	menu->tools[1].text = "eraser";
	setRect(&menu->tools[1].rect, 110, 50, 50, 20);
	menu->tools[1].tool = ERASER;

	menu->tools[2].text = "line";
	setRect(&menu->tools[2].rect, 170, 10, 50, 20);
	menu->tools[2].tool = LINE;

	menu->tools[3].text = "rect";
	setRect(&menu->tools[3].rect, 170, 50, 50, 20);
	menu->tools[3].tool = RECT;

	menu->tools[4].text = "ellips";
	setRect(&menu->tools[4].rect, 230, 10, 50, 20);
	menu->tools[4].tool = ELLIPS;
	
	//colors
	menu->colorsCounter = 3;
	menu->colors = (ColorButton*)malloc(menu->colorsCounter * sizeof(ColorButton));
	menu->currentColor = 0;

	menu->colors[0].text = "r";
	setRect(&menu->colors[0].rect, 500, 10, 20, 20);
	menu->colors[0].color = RED;

	menu->colors[1].text = "g";
	setRect(&menu->colors[1].rect, 540, 10, 20, 20);
	menu->colors[1].color = GREEN;

	menu->colors[2].text = "b";
	setRect(&menu->colors[2].rect, 580, 10, 20, 20);
	menu->colors[2].color = BLUE;

	
	//widths
	menu->widthsCounter = 3;
	menu->widths = (WidthButton*)malloc(menu->widthsCounter * sizeof(WidthButton));
	menu->currentWidth = 0;

	menu->widths[0].text = "1";
	setRect(&menu->widths[0].rect, 700, 10, 20, 20);
	menu->widths[0].width = ONEPIX;

	menu->widths[1].text = "3";
	setRect(&menu->widths[1].rect, 740, 10, 20, 20);
	menu->widths[1].width = THREEPIX;

	menu->widths[2].text = "5";
	setRect(&menu->widths[2].rect, 780, 10, 20, 20);
	menu->widths[2].width = FIVEPIX;

	
	//generals
	menu->generalsCounter = 2;
	menu->generals = (GeneralButton*)malloc(menu->generalsCounter * sizeof(GeneralButton));

	menu->generals[0].text = "NEW";
	setRect(&menu->generals[0].rect, 25, 110, 50, 30);
	menu->generals[0].general = NEW;

	menu->generals[1].text = "SAVE";
	setRect(&menu->generals[1].rect, 25, 150, 50, 30);
	menu->generals[1].general = SAVE;

	
	//saves
	menu->savesCounter = 10;
	menu->saves = (SaveButton*)malloc(menu->savesCounter * sizeof(SaveButton));

	for (int i = 0; i < menu->savesCounter; i++) {

		menu->saves[i].text = (char*)malloc(sizeof(char));
		sprintf(menu->saves[i].text, "%d", i);

		setRect(&menu->saves[i].rect, 40, 250+40*i, 20, 20);
		menu->saves[i].num = i;
	}

	TTF_Init();
	font = TTF_OpenFont("Helvetica.ttf", 14);

	menu->lastSaved = lastSaved;

}


bool checkClick(SDL_Rect rect, int x, int y) {
	if (rect.x <= x && x <= rect.x + rect.w && rect.y <= y && y <= rect.y + rect.h) {
		return 1;
	}
	else {
		return 0;
	}
}

 Inf* checkButtonClick(Menu* menu, int x, int y) {
	 Inf* inf= (Inf*)malloc(sizeof(inf));

	 for (int i = 0; i < menu->toolsCounter; i++) {
		 if (checkClick(menu->tools[i].rect, x, y)) {
			 inf->type = TOOL;
			 inf->num = menu->tools[i].tool;
			 return inf;
		 }
	 }

	 for (int i = 0; i < menu->colorsCounter; i++) {
		 if (checkClick(menu->colors[i].rect, x, y)) {
			 inf->type = COLOR;
			 inf->num = menu->colors[i].color;
			 return inf;
		 }
	 }

	 for (int i = 0; i < menu->widthsCounter; i++) {
		 if (checkClick(menu->widths[i].rect, x, y)) {
			 inf->type = WIDTH;
			 inf->num = menu->widths[i].width;
			 return inf;
		 }
	 }

	 for (int i = 0; i < menu->generalsCounter; i++) {
		 if (checkClick(menu->generals[i].rect, x, y)) {
			 inf->type = GENERAL;
			 inf->num = menu->generals[i].general;
			 return inf;
		 }
	 }

	 for (int i = 0; i < menu->savesCounter; i++) {
		 if (checkClick(menu->saves[i].rect, x, y)) {
			 inf->type = SAVES;
			 inf->num = menu->saves[i].num;
			 return inf;
		 }
	 }

	 return NULL;

}