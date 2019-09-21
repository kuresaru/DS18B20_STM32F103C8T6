#ifndef __COLOR_H
#define __COLOR_H

#define RGB565 0
#define BGR565 1

#define COLOR_FORMAT BGR565

#if COLOR_FORMAT == BGR565
#define RGB(R, G, B) (((R >> 3) << 11) | ((G >> 2) << 5) | ((B >> 3) << 0))
#elif COLOR_FORMAT == RGB565
#define RGB(R, G, B) (((R >> 3) << 0) | ((G >> 2) << 5) | ((B >> 3) << 11))
#else
#error "Invalid color format"
#endif

enum COLOR
{
	clBlack = RGB(0, 0, 0),
	clWhite = RGB(255, 255, 255),
	clRed = RGB(255, 0, 0),
	clGreen = RGB(0, 255, 0),
	clBlue = RGB(0, 0, 255),
	clYellow = RGB(255, 255, 0),
	clGainsboro = RGB(220, 220, 220),
	clNavy = RGB(0, 0, 128),
	clAqua = RGB(0, 255, 255),
	clHotpink = RGB(255, 105, 180),
	clOrange = RGB(255, 165, 0),
	clDeepskyblue = RGB(0, 191, 255),
	clDimgray = RGB(105, 105, 105),
	cllightsalmon = RGB(255, 160, 122),
	cllightcoral = RGB(240, 128, 128),
	clpaleturquoise = RGB(175, 238, 238),
	clturquoise = RGB(64, 224, 208),
	clViolet = RGB(238, 130, 238),
	clGray1 = RGB(90, 90, 90),
	clGray2 = RGB(220, 220, 220),
	clGray3 = RGB(240, 240, 240),
	clDarkgray = RGB(169, 169, 169),
	clSkyblue = RGB(135, 206, 235),
	clChocolate = RGB(210, 105, 30),
	clMediumseagreen = RGB(60, 179, 113),
	clPeachpuff = RGB(255, 218, 185),
	clSeagreen = RGB(46, 139, 87),
};

#endif