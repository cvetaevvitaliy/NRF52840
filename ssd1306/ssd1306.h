#ifndef SSD1306_H_
#define SSD1306_H_
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "image.h"
#include "fonts.h"
#include "nrf_drv_twi.h"

#define SSD1306_128X32
//#define SSD1306_128X64

// I2c address
#define SSD1306_I2C_ADDR 0x3C // 0x3C default

#ifdef SSD1306_128X64
#define SSD1306_GEOMETRY GEOMETRY_128_64
// SSD1306 width in pixels
#define SSD1306_WIDTH 128
// SSD1306 LCD height in pixels
#define SSD1306_HEIGHT 64
#endif
#ifdef SSD1306_128X32
#define SSD1306_GEOMETRY GEOMETRY_128_32
// SSD1306 width in pixels
#define SSD1306_WIDTH 128
// SSD1306 LCD height in pixels
#define SSD1306_HEIGHT 32
#endif

// SSD1306 LCD Buffer Size
#define SSD1306_BUFFER_SIZE (SSD1306_WIDTH * SSD1306_HEIGHT / 8)

// Display commands
#define CHARGEPUMP                    0x8D
#define COLUMNADDR                    0x21
#define COMSCANDEC                    0xC8
#define COMSCANINC                    0xC0
#define DISPLAYALLON                  0xA5
#define DISPLAYALLON_RESUME           0xA4
#define DISPLAYOFF                    0xAE
#define DISPLAYON                     0xAF
#define EXTERNALVCC                   0x1
#define INVERTDISPLAY                 0xA7
#define MEMORYMODE                    0x20
#define NORMALDISPLAY                 0xA6
#define PAGEADDR                      0x22
#define SEGREMAP                      0xA0
#define SETCOMPINS                    0xDA
#define SETCONTRAST                   0x81
#define SETDISPLAYCLOCKDIV            0xD5
#define SETDISPLAYOFFSET              0xD3
#define SETHIGHCOLUMN                 0x10
#define SETLOWCOLUMN                  0x00
#define SETMULTIPLEX                  0xA8
#define SETPRECHARGE                  0xD9
#define SETSEGMENTREMAP               0xA1
#define SETSTARTLINE                  0x40
#define SETVCOMDETECT                 0xDB
#define SWITCHCAPVCC                  0x2

#define SSD1306_ACTIVATE_SCROLL                         0x2F
#define SSD1306_DEACTIVATE_SCROLL                       0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL                 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL                  0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL    0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL     0x2A

#define SSD1306_CMD_SCRL_HR                             0x26   // Setup continuous horizontal scroll right
#define SSD1306_CMD_SCRL_HL                             0x27   // Setup continuous horizontal scroll left
#define SSD1306_CMD_SCRL_VHR                            0x29  // Setup continuous vertical and horizontal scroll right
#define SSD1306_CMD_SCRL_VHL                            0x2A  // Setup continuous vertical and horizontal scroll left
#define SSD1306_CMD_SCRL_STOP                           0x2E // Deactivate scroll
#define SSD1306_CMD_SCRL_ACT                            0x2F  // Activate scroll

#define SWAP_INT16_T(a, b) \
  {                        \
    int16_t t = a;         \
    a = b;                 \
    b = t;                 \
  }

//
//  Enumeration for screen colors
//
typedef enum{
  Black = 0x00, // Black color, no pixel
  White = 0x01, //Pixel is set. Color depends on LCD
  Inverse = 0x02

} SSD1306_COLOR;

typedef enum{
  GEOMETRY_128_64 = 0,
  GEOMETRY_128_32 = 1

} SSD1306_Geometry;
//
//  Struct to store transformations
//
typedef struct{
  uint16_t CurrentX;
  uint16_t CurrentY;
  uint8_t Inverted;
  SSD1306_COLOR Color;
  const nrf_drv_twi_t oled_twi_master;

} SSD1306_t;

enum{
  LCD_SCROLL_RIGHT = 0, // Scroll right
  LCD_SCROLL_LEFT = 1   // Scroll left

};

// Screen scroll interval enumeration
enum{
  LCD_SCROLL_IF2 = 0x07,   // 2 frames
  LCD_SCROLL_IF3 = 0x04,   // 3 frames
  LCD_SCROLL_IF4 = 0x05,   // 4 frames
  LCD_SCROLL_IF5 = 0x00,   // 5 frames
  LCD_SCROLL_IF25 = 0x06,  // 25 frames
  LCD_SCROLL_IF64 = 0x01,  // 64 frames
  LCD_SCROLL_IF128 = 0x02, // 128 frames
  LCD_SCROLL_IF256 = 0x03  // 256 frames
  
};

/* Private function prototypes -----------------------------------------------*/
uint16_t ssd1306_GetWidth(void);
uint16_t ssd1306_GetHeight(void);
SSD1306_COLOR ssd1306_GetColor(void);
void ssd1306_SetColor(SSD1306_COLOR color);
bool ssd1306_Init(void);
void ssd1306_Fill();
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y);
void ssd1306_DrawBitmap(uint8_t X, uint8_t Y, uint8_t W, uint8_t H, const uint8_t *pBMP);
void ssd1306_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void ssd1306_DrawVerticalLine(int16_t x, int16_t y, int16_t length);
void ssd1306_DrawHorizontalLine(int16_t x, int16_t y, int16_t length);
void ssd1306_DrawRect(int16_t x, int16_t y, int16_t width, int16_t height);
void ssd1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);
void ssd1306_FillRect(int16_t xMove, int16_t yMove, int16_t width, int16_t height);
void ssd1306_DrawCircle(int16_t x0, int16_t y0, int16_t radius);
void ssd1306_FillCircle(int16_t x0, int16_t y0, int16_t radius);
void ssd1306_DrawCircleQuads(int16_t x0, int16_t y0, int16_t radius, uint8_t quads);
void ssd1306_DrawProgressBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress);
void ssd1306_Draw_String(const char *str, int x, int y, const tFont *font);
void ssd1306_Draw_Bitmap_Mono(int x, int y, const tImage *image);
void ssd1306_SetCursor(uint8_t x, uint8_t y);
void ssd1306_DisplayOn(void);
void ssd1306_DisplayOff(void);
void ssd1306_InvertDisplay(void);
void ssd1306_NormalDisplay(void);
void ssd1306_ResetOrientation(void);
void ssd1306_FlipScreenVertically(void);
void ssd1306_MirrorScreen(void);
void ssd1306_Clear(void);

void ssd1306_Start_Scroll_Right(uint8_t start, uint8_t stop);
void SSD1306_ScrollDSetup(uint8_t dir, uint8_t start, uint8_t end, uint8_t interval, uint8_t voffs);
void SSD1306_ScrollHSetup(uint8_t dir, uint8_t start, uint8_t end, uint8_t interval);
void SSD1306_ScrollStart(void);
void SSD1306_ScrollStop(void);

void i2c_init(void);

#endif /* SSD1306_H_ */
