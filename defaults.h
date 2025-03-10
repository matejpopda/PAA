#pragma once

#include <array>

// SETTINGS

const int CANVAS_SIZE_X = 850;
const int CANVAS_SIZE_Y = 850;

const int CONTROLS_SIZE_X = 300;
const int CONTROLS_SIZE_Y = 450;


using TypePrecision = float;

const int NUMBER_OF_THREADS_FOR_MULTITHREADING = 128;


// Aliases

struct Color {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	//unsigned char alpha;
};


struct Bounds {
	TypePrecision left_x;
	TypePrecision right_x;
	TypePrecision top_y;
	TypePrecision bottom_y;
};



using CanvasArray = std::array<std::array<Color, CANVAS_SIZE_X>, CANVAS_SIZE_Y>;


enum //elements in GUI 
{
	ID_Hello ,
	ID_Canvas,
	ID_Controls,
	ID_Bitmap,
};




