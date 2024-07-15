#pragma once

#define SELECT_BTN 4
#define RIGHT_BTN  3
#define DOWN_BTN   2
#define UP_BTN     1

#include "Arduino.h"
#include <debounce.h>

// Identifiers: 0 - nothing, 1 - up, 2 - down, 3 - right, 4 - select
uint8_t btnPressed = 0;

uint8_t _up_btn_pin = 11;
uint8_t _down_btn_pin = 2;
uint8_t _select_btn_pin = 8;
uint8_t _right_btn_pin = 3;
//uint8_t _left_btn_pin = 2;

// Handlers
void upButtonHandler(uint8_t btnId, uint8_t btnState) {if(BTN_PRESSED == btnState) btnPressed = 1;}
void downButtonHandler(uint8_t btnId, uint8_t btnState) {if(BTN_PRESSED == btnState) btnPressed = 2;}
void rightButtonHandler(uint8_t btnId, uint8_t btnState) {if(BTN_PRESSED == btnState) btnPressed = 3;}
//void leftButtonHandler(uint8_t btnId, uint8_t btnState) {if(BTN_PRESSED == btnState) btnPressed = 4;}
void selectButtonHandler(uint8_t btnId, uint8_t btnState) {if(BTN_PRESSED == btnState) btnPressed = 4;}

// Handler appenders
Button upButton(0, upButtonHandler);
Button downButton(1, downButtonHandler);
Button rightButton(2, rightButtonHandler);
//Button leftButton(3, leftButtonHandler);
Button selectButton(4, selectButtonHandler);

Buttons_Init()
{
  // Button initializers
  digitalWrite(_up_btn_pin, HIGH);
  digitalWrite(_right_btn_pin, HIGH);
  //digitalWrite(_left_btn_pin, HIGH);
  digitalWrite(_select_btn_pin, HIGH);
  digitalWrite(_down_btn_pin, HIGH);
}

void Buttons_Update()
{
  // Receive updates
  upButton.update(digitalRead(_up_btn_pin));
  downButton.update(digitalRead(_down_btn_pin));
  rightButton.update(digitalRead(_right_btn_pin));
  //leftButton.update(digitalRead(_left_btn_pin));
  selectButton.update(digitalRead(_select_btn_pin));
}

uint8_t Buttons_ReturnPressedButton()
{
  // Return pressed button ID
  return btnPressed;
}

void Buttons_ResetReturnedButton()
{
  // Reset pressed button ID
  btnPressed = 0;
}
