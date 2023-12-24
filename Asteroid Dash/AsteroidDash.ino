/*
  ASTEROID DASH
  Your spaceship that was heading for Mars and missed it's trajectory and is now heading inside the asteroid belt.
  Take control of your spaceship and avoid a collision!
*/

#include <LiquidCrystal.h>

#define CHANGE_POS_BTN 7
#define MISSILE_BTN 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

struct asteroid
{
  int x;
  int y;
  int type;
  int speed;
};

asteroid ast[3];

byte empty[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte spaceship[] = {
  B00000,
  B10000,
  B11100,
  B11111,
  B11111,
  B11100,
  B10000,
  B00000
};

byte asteroid1[] = {
  B00000,
  B00100,
  B00110,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100
};

byte asteroid2[] = {
  B00000,
  B00100,
  B01110,
  B11110,
  B11100,
  B11000,
  B01000,
  B00000
};

byte asteroid3[] = {
  B00000,
  B01100,
  B01110,
  B11111,
  B11111,
  B11110,
  B01100,
  B00000
};

// Current position of the ship 0 for first row 1 for second row
int spaceship_pos = 0;

bool collided = false;
bool temp = 0;

int score = 0; // Increments eveytime space ship gets through an asteroid
int missiles = 20; // Spaceship has 20 missiles

void setup() {
  // Turn off pin 13 if missiles are over
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Set pin 7 and 8 for input
  pinMode(CHANGE_POS_BTN, INPUT);
  pinMode(MISSILE_BTN, INPUT);

  analogWrite(6, 60); // Contrast

  lcd.begin(16, 2);
  lcd.createChar(1, spaceship);
  lcd.createChar(2, asteroid1);
  lcd.createChar(3, asteroid2);
  lcd.createChar(4, asteroid3);
  lcd.createChar(5, empty);

  // Show starting screen
  Init();

  // Generate spaceship
  lcd.home();
  lcd.write(1);

  // Generate asteroid
  CreateAsteroid();
}

void loop() {
  if(collided == false)
  {
    if(digitalRead(CHANGE_POS_BTN) == HIGH)
      MoveSpaceShip();

    if(digitalRead(MISSILE_BTN) == HIGH)
      MissileFired();

    if(missiles == 0)
      digitalWrite(13, LOW);

    collided = !Update();
    delay(1000);
  }
  else
  {
    // Clear the screens
    if(temp == 0)
    {
      lcd.clear();
      temp = 1;
    }

    lcd.setCursor(0, 0);
    lcd.print("GAME OVER!");
    lcd.setCursor(0, 1);
    lcd.print("SCORE = ");
    lcd.setCursor(8, 1);
    lcd.print(score);
  }
}

// Initial screen
void Init()
{
  lcd.setCursor(1, 0);
  lcd.print("Asteroid  Dash");
  delay(2000);
  lcd.clear();
}

// Generate random numbers
int rand(int min, int max)
{
  randomSeed(analogRead(0));
  int num = random(min, max + 1);

  return num;
}

void MoveSpaceShip()
{
  // Remove the space ship from the current location
  lcd.setCursor(0, spaceship_pos);
  lcd.write(5);

  if(spaceship_pos == 0)
  {
    lcd.setCursor(0, 1);
    lcd.write(1);
    spaceship_pos = 1;
  } else {
    lcd.setCursor(0, 0);
    lcd.write(1);
    spaceship_pos = 0;
  }
}

void CreateAsteroid()
{
  ast[0] = {15, rand(0, 1), rand(1, 3), rand(1, 3)};
  ast[1] = {15, rand(0, 1), rand(1, 3), rand(1, 3)};
  ast[2] = {15, rand(0, 1), rand(1, 3), rand(1, 3)};
}

// Draws the new position of the asteroid
// Returns true if everything went well and false if asteroid collides
bool Update()
{
  for(int i = 0; i < 3; i++)
  {
    // Remove asteroid
    lcd.setCursor(ast[i].x, ast[i].y);
    lcd.write(5);

    // Set asteroid new position
    if(ast[i].x <= 0)
    {
      // If asteroid has been passed, face the next asteroid
      ast[i] = {15, rand(0, 1), rand(1, 3), rand(1, 3)};
      score++;
    }
    else
      ast[i].x -= ast[i].speed;

    // Draw the asteroid
    lcd.setCursor(ast[i].x, ast[i].y);
    lcd.write(ast[i].type + 1);

    // Check for collisions
    if(ast[i].x == 0 && ast[i].y == spaceship_pos)
      return false;
  }

  return true;
}

void MissileFired()
{
  if(missiles != 0)
  {
    missiles--;
    for(int i = 0; i < 3; i++)
    {
      // Destroy asteroid if it is in missiles path
      if(ast[i].y == spaceship_pos)
      {
        lcd.setCursor(ast[i].x, ast[i].y);
        lcd.write(5);

        // face the next asteroid
        ast[i] = {15, rand(0, 1), rand(1, 3), rand(1, 3)};
        score++;

        return;
      }
    }
  }
}