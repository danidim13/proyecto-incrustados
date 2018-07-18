/*
 * FramesCommon.hpp
 *
 *  Created on: Jul 17, 2018
 *      Author: daniel
 */

#ifndef FRAMESCOMMON_HPP_
#define FRAMESCOMMON_HPP_

#include "msp.h"

extern "C"
{
    #include <grlib.h>
}

#define FR_XS 128
#define FR_YS 128

#define FRAME_READY 1
#define NEW_FB 2

//typedef int8_t frame8row_t[FR_XS];
//typedef frame8row_t frame8_t[FR_YS];
//typedef frame8row_t* frame8p_t;

struct stFrame {
    int8_t pixels[FR_XS * FR_YS];
};

typedef struct stFrame frame8_t ;

typedef struct stFrame* frame8p_t;

/***********************************/
/* Informacion del mapa (pantalla) */
/***********************************/

#define CELL_X 16
#define CELL_Y 16

#define GRID_LX 8
#define GRID_LY 8

#define COLOR_BITS 4;
#define COLOR_BG  0x0f00;
#define COLOR_FG  0xf000;

const int16_t TOP_B  = 1;
const int16_t LEFT_B = 2;
const int16_t BOT_B  =  4;
const int16_t RIGHT_B = 8;


struct stMapa {
    int16_t grid[GRID_LY * GRID_LX] = {
         0b0011,0b1101,0b0111,0b1001,0b0111,0b1101,0b10111,9,
         2,0,0,0,0,0,0,8,
         2,0,0,0,0,0,0,8,
         2,0,0,0,3,0,0,8,
         2,0,0,0,0,0,0,8,
         2,0,0,0,0,0,0,8,
         2,0,0,0,0,0,0,8,
         6,4,4,4,4,4,4,12
    };
    int32_t bg = GRAPHICS_COLOR_BLACK;
    int32_t fg = GRAPHICS_COLOR_WHITE_SMOKE;
};

extern int32_t g_pColorTable[16];
/*{
    GRAPHICS_COLOR_BLACK,
    GRAPHICS_COLOR_WHITE,
    GRAPHICS_COLOR_GREEN,
    GRAPHICS_COLOR_BLUE,
    GRAPHICS_COLOR_WHITE_SMOKE,
    GRAPHICS_COLOR_SIENNA,
    GRAPHICS_COLOR_YELLOW,
    -----------------------
    GRAPHICS_COLOR_ROYAL_BLUE,
    GRAPHICS_COLOR_ALICE_BLUE,
    GRAPHICS_COLOR_ANTIQUE_WHITE,
    GRAPHICS_COLOR_AQUA,
    GRAPHICS_COLOR_AQUAMARINE,
    GRAPHICS_COLOR_AZURE,
    GRAPHICS_COLOR_BEIGE,
    GRAPHICS_COLOR_BISQUE,
    GRAPHICS_COLOR_BLACK,
    GRAPHICS_COLOR_BLANCHED_ALMOND,
    GRAPHICS_COLOR_BLUE_VIOLET,
    GRAPHICS_COLOR_BROWN,
    GRAPHICS_COLOR_BURLY_WOOD,
    GRAPHICS_COLOR_CADET_BLUE,
    GRAPHICS_COLOR_CHARTREUSE,
    GRAPHICS_COLOR_CHOCOLATE,
    GRAPHICS_COLOR_CORAL,
    GRAPHICS_COLOR_CORNFLOWER_BLUE,
    GRAPHICS_COLOR_CORNSILK,
    GRAPHICS_COLOR_CRIMSON,
    GRAPHICS_COLOR_CYAN,
    GRAPHICS_COLOR_DARK_BLUE,
    GRAPHICS_COLOR_DARK_CYAN,
    GRAPHICS_COLOR_DARK_GOLDENROD,
    GRAPHICS_COLOR_DARK_GRAY,
    GRAPHICS_COLOR_DARK_GREEN,
    GRAPHICS_COLOR_DARK_KHAKI,
    GRAPHICS_COLOR_DARK_MAGENTA,
    GRAPHICS_COLOR_DARK_OLIVE_GREEN,
    GRAPHICS_COLOR_DARK_ORANGE,
    GRAPHICS_COLOR_DARK_ORCHID,
    GRAPHICS_COLOR_DARK_RED,
    GRAPHICS_COLOR_DARK_SALMON,
    GRAPHICS_COLOR_DARK_SEA_GREEN,
    GRAPHICS_COLOR_DARK_SLATE_BLUE,
    GRAPHICS_COLOR_DARK_SLATE_GRAY,
    GRAPHICS_COLOR_DARK_TURQUOISE,
    GRAPHICS_COLOR_DARK_VIOLET,
    GRAPHICS_COLOR_DEEP_PINK,
    GRAPHICS_COLOR_DEEP_SKY_BLUE,
    GRAPHICS_COLOR_DIM_GRAY,
    GRAPHICS_COLOR_DODGER_BLUE,
    GRAPHICS_COLOR_FIRE_BRICK,
    GRAPHICS_COLOR_FLORAL_WHITE,
    GRAPHICS_COLOR_FOREST_GREEN,
    GRAPHICS_COLOR_FUCHSIA,
    GRAPHICS_COLOR_GAINSBORO,
    GRAPHICS_COLOR_GHOST_WHITE,
    GRAPHICS_COLOR_GOLD,
    GRAPHICS_COLOR_GOLDENRON,
    GRAPHICS_COLOR_GRAY,
    GRAPHICS_COLOR_GREEN_YELLOW,
    GRAPHICS_COLOR_HONEYDEW,
    GRAPHICS_COLOR_HOT_PINK,
    GRAPHICS_COLOR_INDIAN_RED,
    GRAPHICS_COLOR_INDIGO,
    GRAPHICS_COLOR_IVORY,
    GRAPHICS_COLOR_KHAKI,
    GRAPHICS_COLOR_LAVENDER,
    GRAPHICS_COLOR_LAVENDER_BLUSH,
    GRAPHICS_COLOR_LAWN_GREEN,
    GRAPHICS_COLOR_LEMON_CHIFFON,
    GRAPHICS_COLOR_LIGHT_BLUE,
    GRAPHICS_COLOR_LIGHT_CORAL,
    GRAPHICS_COLOR_LIGHT_CYAN,
    GRAPHICS_COLOR_LIGHT_GOLDENRON_YELLOW,
    GRAPHICS_COLOR_LIGHT_GREEN,
    GRAPHICS_COLOR_LIGHT_GRAY,
    GRAPHICS_COLOR_LIGHT_PINK,
    GRAPHICS_COLOR_LIGHT_SALMON,
    GRAPHICS_COLOR_LIGHT_SEA_GREEN,
    GRAPHICS_COLOR_LIGHT_SKY_BLUE,
    GRAPHICS_COLOR_LIGHT_SLATE_GRAY,
    GRAPHICS_COLOR_LIGHT_STEEL_BLUE,
    GRAPHICS_COLOR_LIGHT_YELLOW,
    GRAPHICS_COLOR_LIME,
    GRAPHICS_COLOR_LIME_GREEN,
    GRAPHICS_COLOR_LINEN,
    GRAPHICS_COLOR_MAGENTA,
    GRAPHICS_COLOR_MAROON,
    GRAPHICS_COLOR_MEDIUM_AQUAMARINE,
    GRAPHICS_COLOR_MEDIUM_BLUE,
    GRAPHICS_COLOR_MEDIUM_ORCHID,
    GRAPHICS_COLOR_MEDIUM_PURPLE,
    GRAPHICS_COLOR_MEDIUM_SEA_GREEN,
    GRAPHICS_COLOR_MEDIUM_SLATE_BLUE,
    GRAPHICS_COLOR_MEDIUM_SPRING_GREEN,
    GRAPHICS_COLOR_MEDIUM_TURQUOISE,
    GRAPHICS_COLOR_MEDIUM_VIOLET_RED,
    GRAPHICS_COLOR_MIGNIGHT_BLUE,
    GRAPHICS_COLOR_MINT_CREAM,
    GRAPHICS_COLOR_MISTY_ROSE,
    GRAPHICS_COLOR_MOCCASIN,
    GRAPHICS_COLOR_NAVAJO_WHITE,
    GRAPHICS_COLOR_NAVY,
    GRAPHICS_COLOR_OLD_LACE,
    GRAPHICS_COLOR_OLIVE,
    GRAPHICS_COLOR_OLIVE_DRAB,
    GRAPHICS_COLOR_ORANGE,
    GRAPHICS_COLOR_ORANGE_RED,
    GRAPHICS_COLOR_ORCHID,
    GRAPHICS_COLOR_PALE_GOLDENRON,
    GRAPHICS_COLOR_PALE_GREEN,
    GRAPHICS_COLOR_PALE_TURQUOISE,
    GRAPHICS_COLOR_PALE_VIOLET_RED,
    GRAPHICS_COLOR_PAPAYA_WHIP,
    GRAPHICS_COLOR_PEACH_PUFF,
    GRAPHICS_COLOR_PERU,
    GRAPHICS_COLOR_PINK,
    GRAPHICS_COLOR_PLUM,
    GRAPHICS_COLOR_POWDER_BLUE,
    GRAPHICS_COLOR_PURPLE,
    GRAPHICS_COLOR_RED,
    GRAPHICS_COLOR_ROSY_BROWN,
    GRAPHICS_COLOR_SADDLE_BROWN,
    GRAPHICS_COLOR_SALMON,
    GRAPHICS_COLOR_SANDY_BROWN,
    GRAPHICS_COLOR_SEA_GREEN,
    GRAPHICS_COLOR_SEASHELL,
    GRAPHICS_COLOR_SILVER,
    GRAPHICS_COLOR_SKY_BLUE,
    GRAPHICS_COLOR_SLATE_BLUE,
    GRAPHICS_COLOR_SLATE_GRAY,
    GRAPHICS_COLOR_SNOW,
    GRAPHICS_COLOR_SPRING_GREEN,
    GRAPHICS_COLOR_STEEL_BLUE,
    GRAPHICS_COLOR_TAN,
    GRAPHICS_COLOR_TEAL,
    GRAPHICS_COLOR_THISTLE,
    GRAPHICS_COLOR_TOMATO,
    GRAPHICS_COLOR_TURQUOISE,
    GRAPHICS_COLOR_VIOLET,
    GRAPHICS_COLOR_WHEAT,
    GRAPHICS_COLOR_YELLOW_GREEN,
};*/

/**
 * A la hora de direccionar usar frame[y][x]!
 */




#endif /* FRAMESCOMMON_HPP_ */
