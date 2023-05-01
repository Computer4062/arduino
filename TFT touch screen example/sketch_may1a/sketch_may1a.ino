#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0

#define LCD_RESET A4

#define BLACK        0x0000  /*   0,   0,   0 */
#define BLUE         0x001F  /*   0,   0, 255 */
#define RED          0xF800  /* 255,   0,   0 */
#define GREEN        0x07E0  /*   0, 255,   0 */
#define CYAN         0x07FF  /*   0, 255, 255 */
#define MAGENTA      0xF81F  /* 255,   0, 255 */
#define YELLOW       0xFFE0  /* 255, 255,   0 */
#define WHITE        0xFFFF  /* 255, 255, 255 */
#define NAVY         0x000F  /*   0,   0, 128 */
#define DARKGREEN    0x03E0  /*   0, 128,   0 */
#define DARKCYAN     0x03EF  /*   0, 128, 128 */
#define MAROON       0x7800  /* 128,   0,   0 */
#define PURPLE       0x780F  /* 128,   0, 128 */
#define OLIVE        0x7BE0  /* 128, 128,   0 */
#define LIGHTGREY    0xC618  /* 192, 192, 192 */
#define DARKGREY     0x7BEF  /* 128, 128, 128 */
#define ORANGE       0xFD20  /* 255, 165,   0 */
#define GREENYELLOW  0xAFE5  /* 173, 255,  47 */
#define PINK         0xF81F  /* 255,   0, 255 */

#define BUTTON_X 52
#define BUTTON_Y 150 
#define BUTTON_W 80
#define BUTTON_H 45
#define BUTTON_SPACING_X 26
#define BUTTON_SPACING_Y 30
#define BUTTON_TEXTSIZE 3

#define YP A2
#define XM A3
#define YM 8
#define XP 9

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define TS_MINX 130
#define TS_MAXX 905

#define TS_MINY 75
#define TS_MAXY 930

#define STATUS_X 10
#define STATUS_Y 65

#define RED_LED 2
#define GRN_LED 3
#define BLU_LED 4

boolean RED_state = 0;
boolean GRN_state = 0;
boolean BLU_state = 0;

Adafruit_GFX_Button buttons[3];

char buttonlabels[3][5] = {'R', 'G', 'B'};
uint16_t buttoncolors[6] = {RED, GREEN, BLUE};

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup(void){
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

  pinMode(RED_LED, OUTPUT);
  pinMode(GRN_LED, OUTPUT);
  pinMode(BLU_LED, OUTPUT);

  tft.reset();
  identifier = tft.readID();

  tft.begin(identifier);

  Serial.print("TFT size is ");
  Serial.print(tft.width());
  Serial.print("x");
  Serial.print(tft.height());

  tft.setRotation(0);
  tft.fillScreen(BLACK);

  for (uint8_t row = 0; row < 3; row++){
    for (uint8_t col = 0; col < 3; col++){

      buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
        BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), 
        BUTTON_W, BUTTON_H, WHITE, buttoncolors[col + row * 3], WHITE,
        buttonlabels[col + row * 3], BUTTON_TEXTSIZE);

      buttons[col + row * 3].drawButton();

    }
  }

}

void loop(){
  digitalWrite(13, HIGH);
  TSPoint IP = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE){
    p.x = p.x + p.y;
    p.y = p.x - p.y;
    p.x = p.x - p.y;
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
  }

  for (uint8_t b = 0; b < 3; b++){
    if((buttons[b].contains(p.x, p.y) && p.x > 10)){
      Serial.print("Pressing: "); Serial.print(b);
      buttons[b].press(true);

      if(b == 0) RED_state = !RED_state;
      if(b == 1) GRN_state = !GRN_state;
      if(b == 2) BLU_state = !BLU_state;
    }

    if(RED_state == 1) digitalWrite(RED_state, HIGH);
    else digitalWrite(RED_state, LOW);
    if(BLU_state == 1) digitalWrite(BLU_state, HIGH);
    else digitalWrite(BLU_state, LOW);
    if(GRN_state == 1) digitalWrite(GRN_state, HIGH);
    else digitalWrite(GRN_state, LOW); 

  }else{
    buttons[b].press(false);
  }

  for(uint8_t b = 0; b < 3; b++){
    if(buttons[b].justReleased()){
      Serial.print("Released: "); Serial.println(b);
      buttons[b].drawButton();
    }

    if(buttons[b].justPressed()){
      buttons[b].drawButton(true);
      delay(100);
    }
  }
}
























