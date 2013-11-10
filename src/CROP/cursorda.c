/* Cursorda.c - definition of some bitmaps for menu icons. */

#include "jimk.h"
#include "flicmenu.h"

#ifdef SLUFFED
static UBYTE iinsert[] = 
	{
	0x10,0x38,0x7C,0x82,
	};
struct cursor cinsert = 	{ 0, iinsert, 8, 4, 4, 2};


static UBYTE	ikill[] = {
		0x07, 0xC0, 0x0C, 0x60, 0x1E, 0x30, 0x13, 0x10, 0x11, 0x90,
		0x18, 0xF0, 0x0C, 0x60, 0x07, 0xC0, 
		};
struct cursor ckill = 	{ 0, ikill, 16, 8, 8, 4};


static UBYTE idown[] = 
	{
	0x10, 0x10, 0x10, 0x92, 0x7C, 0x38, 0x10,
	};
struct cursor cdown = 	{ 0, idown, 7, 7, 3, 3};
#endif /* SLUFFED */

static UBYTE ileft[] = 
	{
	0x10,0x20,0x60,0xff,0x60,0x20,0x10,
	};
struct cursor cleft = 	{ 0, ileft, 8, 7, 4, 3};


static UBYTE iright[] = 
	{
	0x08,0x04,0x06,0xFF,0x06,0x04,0x08,
	};
struct cursor cright = 	{ 0, iright, 8, 7, 4, 3};

#ifdef SLUFFED
static UBYTE iup[] = 
	{
	0x10,0x38,0x7C,0x92,0x10,0x10,0x10,
	};
struct cursor cup = 	{ 0, iup, 8, 7, 4, 3};



static UBYTE icright2[] = 
	{
	0x84,0x00, 0x42,0x00, 0x63, 0x00, 0x73, 0x80,
	0x63,0x00, 0x42,0x00, 0x84,0x00,
	};
struct cursor cright2 = 	{ 0, icright2, 9, 7, 5, 3};
#endif /* SLUFFED */


static UBYTE ictridown[] = 
	{
	0xff,0x80, 0x7f,0x00, 0x3e,0x00, 0x1c,0x00, 
	0x08,0x00,
	};
struct cursor ctridown = 	{ 0, ictridown, 9, 5, 4, 2};

static UBYTE ictriup[] = 
	{
	0x08,0x00, 0x1c,0x00, 0x3e,0x00, 0x7f,0x00, 
	0xff,0x80,
	};
struct cursor ctriup = 	{ 0, ictriup, 9, 5, 4, 2};



