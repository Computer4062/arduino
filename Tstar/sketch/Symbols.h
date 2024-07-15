#pragma once

/*
  All the symbols that are going to be used in the
  Task Manager
*/
/*
  Button representations
*/
const byte Symbols_rightArrow[8] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11110,
  B11100,
  B11000,
  B10000
};

const byte Symbols_leftArrow[8] = {
  B00001,
  B00011,
  B00111,
  B01111,
  B01111,
  B00111,
  B00011,
  B00001
};

const byte Symbols_select[8] = {
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B00000
};

/*
  Number representations
*/
const byte Symbols_char1[8] = {
  B11111,
  B00001,
  B01001,
  B01001,
  B01001,
  B01001,
  B00001,
  B11111
};

const byte Symbols_char2[8] = {
  B11111,
  B00001,
  B11101,
  B00101,
  B11101,
  B10001,
  B11101,
  B11111
};

const byte Symbols_char3[8] = {
  B11111,
  B00001,
  B11101,
  B00101,
  B11101,
  B00101,
  B11101,
  B11111
};

const byte Symbols_char4[8] = {
  B11111,
  B00001,
  B00101,
  B01101,
  B11111,
  B00101,
  B00101,
  B11111
};

const byte Symbols_char5[8] = {
  B11111,
  B00001,
  B11101,
  B10001,
  B11101,
  B00101,
  B11101,
  B11111
};

/*
  3 x 2 characters that make up the bell
*/
// Locations: (12, 0)
const byte Symbols_bell1[8] = {
  B00000,
  B00000,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011
};

// Locations: (13, 0)
const byte Symbols_bell2[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

// Locations: (14, 0)
const byte Symbols_bell3[8] = {
  B00000,
  B00000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
};

// Locations: (12, 1)
const byte Symbols_bell4[8] = {
  B00011,
  B00011,
  B00011,
  B00011,
  B11111,
  B11111,
  B00000,
  B00000
};

// Locations: (13, 1)
const byte Symbols_bell5[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01110,
  B01110
};

// Locations: (14, 1)
const byte Symbols_bell6[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11111,
  B11111,
  B00000,
  B00000
};

/*
Markers
*/
const byte Symbols_upArrow[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000
};
