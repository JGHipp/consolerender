/*
	Written by John Hippisley, 1/13/19

*/

#include <iostream>
using namespace std;

//characters printed to console
#define UPPER_BLOCK "\u2580"
#define LOWER_BLOCK "\u2584"
#define FULL_BLOCK "\u2588"
#define CHAR_EMPTY " "
#define PIXEL_ON 1
#define PIXEL_OFF 0

//definition of pixel (monochrome)
typedef bool pixel_t;

//dimensions of buffer
const int BUFFER_WIDTH = 64;
const int BUFFER_HEIGHT = 32;
bool imageBuffer[BUFFER_WIDTH * BUFFER_HEIGHT];

//rendering-related functions
void init();
void renderBuffer();
bool inRange(int x, int y);
pixel_t getPixel(int x, int y);
void putPixel(int x, int y, pixel_t value);
void drawLine(int x1, int y1, int x2, int y2, pixel_t value);
void drawRect(int x, int y, int width, int height, pixel_t value);
void drawTexture(int x, int y, pixel_t* texture, int width, int height);

int main()
{
	init();
	renderBuffer();
	return 0;
}

void init()
{
	pixel_t cocaCola[54 * 19] =
		{0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
		0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,
		1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,1,1,
		1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,
		1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,
		1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
		0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,1,0,
		0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,
		0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0};
	drawTexture(0, 0, cocaCola, 54, 19);
}

void renderBuffer()
{
	//divide buffer into 2 row segments
	int nSegments = BUFFER_HEIGHT / 2;
	for(int segment = 0; segment < nSegments; ++segment)
	{
		//calculate y's for both rows
		int y1 = segment * 2;
		int y2 = segment * 2 + 1;
		//cycle through rows in segment
		for(int x = 0; x < BUFFER_WIDTH; ++x)
		{
			//determine which character should be printed
			/***/if(getPixel(x, y1) && !getPixel(x, y2)){ cout << UPPER_BLOCK; }
			else if(getPixel(x, y2) && !getPixel(x, y1)){ cout << LOWER_BLOCK; }
			else if(getPixel(x, y1) && getPixel(x, y2)) { cout << FULL_BLOCK;  }
			else cout << CHAR_EMPTY;
		}
		//newline
		cout << endl;
	}
}

bool inRange(int x, int y)
{
	if(x >= 0 && y >= 0 && x < BUFFER_WIDTH && y < BUFFER_HEIGHT) return true;
	else return false;
}

pixel_t getPixel(int x, int y)
{
	if(inRange(x, y)) return imageBuffer[x + y * BUFFER_WIDTH];
	else return PIXEL_OFF;
}

void putPixel(int x, int y, pixel_t value)
{
	if(inRange(x, y)) imageBuffer[x + y * BUFFER_WIDTH] = value;
}


void drawRect(int x, int y, int width, int height, pixel_t value)
{
	for(int dx = 0; dx < width; ++dx)
	{
		for(int dy = 0; dy < height; ++dy)
		{
			int sx = dx + x;
			int sy = dy + y;
			putPixel(sx, sy, value);
		}
	}
}

void drawTexture(int x, int y, pixel_t* texture, int width, int height)
{
	for(int dx = 0; dx < width; ++dx)
  	{
    	for(int dy = 0; dy < height; ++dy)
    	{
      		int sx = dx + x;
      		int sy = dy + y;
	  		bool value = texture[dx + dy * width];
      		putPixel(sx, sy, value);
    	}
  	}
}
