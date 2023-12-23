/*
THE EXPLORERS GUIDE TO CIVILIZATION

Features:
1. Location
2. Raw Location
3. Date
4. Time
5. Speed
6. Altitude
7. Course Degree
8. Info
*/

#define RX 7
#define TX 8
#define MODE_BTN 9
#define UNIT_BTN 10

#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LiquidCrystal.h>

// Satellite logo parts
byte solarwing[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000
};

byte body[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte dish1[] = {
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B11111,
  B00000,
  B00000
};

byte dish2[] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11111,
  B00000,
  B00000
};

SoftwareSerial ss(RX, TX);
TinyGPSPlus    gps;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int current_mode = 8;
int unit = 0;

/*
// Functions declares
void Initialize();            // Start the LCD ,also called when sattelite connection not found
void UpdateMode(bool change); // Call functions according to change_mode variable

bool IsSatelliteConnected();  // Returns true if connection found -> Connection not found, call Initialize()
void Location();              // Finds location in longitudes and latitudes
void rawLocation();           // Finds raw longitudes and latitudes
void Date();                  // Finds current date
void Time();                  // Finds current time
void Speed();                 // Finds current speed
void Altitude();              // Finds current altitude
void CourseDegree();          // Tells the dirrection
void Info();                  // Shows which satellites are connected
*/

// Functions writtern
void setup()
{
  Serial.begin(9600);

  // Initialize LCD display and characters
  lcd.begin(16, 2);
  lcd.createChar(1, solarwing);
  lcd.createChar(2, body);
  lcd.createChar(3, dish1);
  lcd.createChar(4, dish2);

  // Adjust lcd contrast
  analogWrite(6, 60);

  // Start loading screen
  Initialize();
  Serial.println("INIT started");

  // Initialize buttons
  pinMode(MODE_BTN, INPUT);
  pinMode(UNIT_BTN, INPUT);
  pinMode(10, OUTPUT); // current supply for GPS module

  // Initialize Software Serial
  ss.begin(9600);

  Serial.println("SEARCHING");
  while(!IsSatelliteConnected())
  {
    Initialize();
  }
  Serial.println("FOUND");

  // Go to first mode
  UpdateMode(true, false);
}

bool mode_state;
bool unit_state;

void loop()
{
    // Update things in the current mode
    UpdateMode(false, false);

    // If mode pressed change the mode
    mode_state = digitalRead(MODE_BTN);
    if(mode_state == HIGH)
    {
      delay(2000);
      UpdateMode(true, false);
    }
    
    // If unit pressed increase the unit by 1
    unit_state = digitalRead(UNIT_BTN);
    if(unit_state == HIGH)
    {
      delay(1000);
      if(unit == 4) unit = 0;
      else unit++;
      UpdateMode(false, true);
    }
}

void Initialize()
{
  lcd.setCursor(7, 0);
  lcd.write(1);
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.setCursor(9, 0);
  lcd.write(2);
  lcd.setCursor(10, 0);
  lcd.write(2);
  lcd.setCursor(11, 0);
  lcd.write(1);
  lcd.setCursor(12, 0);
  lcd.write(1);
  lcd.setCursor(9, 1);
  lcd.write(3);
  lcd.setCursor(10, 1);
  lcd.write(4);

  lcd.home();
  lcd.print("EGC");

  lcd.setCursor(0, 1);
  lcd.blink();

  delay(1000);
  lcd.noBlink();
}

bool IsSatelliteConnected()
{
  if(ss.available())
  {
    Serial.println("FOUND");
    return true;
  }
  else
    return false;

  // Re-check every second
  delay(1000);
}

template<typename T>
void Display(int x, int y, T value)
{
  lcd.setCursor(x, y);
  lcd.print(value);
}

void UpdateMode(bool mode_change, bool unit_change)
{
  if(ss.available())  gps.encode(ss.read());
  else
  {
    lcd.clear();
    lcd.home();
    lcd.print("no data");
    return;
  }

  if(mode_change)
  {
    lcd.clear();
    if(current_mode == 8)    current_mode = 1;
    else current_mode++;
  }

  if(unit_change)
  {
    if(current_mode == 5)
    {
      lcd.clear();
      Speed();
    }
    else if(current_mode == 6)
    {
      lcd.clear();
      Altitude();
    }
  }


  switch(current_mode)
  {
    case 1:
      if(mode_change)
      {
        Display(0, 0, "Location");
        delay(2000);
        lcd.clear();
        Location();
      }

      if(gps.location.isUpdated())
      {
        lcd.clear();
        Location();
      }

      break;


    case 2:
      if(mode_change)
      {
        Display(0, 0, "Raw Location");
        delay(2000);
        lcd.clear();
        rawLocation();
      }

      if(gps.location.isUpdated())
      {
        lcd.clear();
        rawLocation();
      }

      break;

    case 3:
      if(mode_change)
      {
        Display(0, 0, "Date");
        delay(2000);
        lcd.clear();
        Date();
      }

      if(gps.date.isUpdated())
      {
        lcd.clear();
        Date();
      }

      break;

    case 4:
      if(mode_change)
      {
        Display(0, 0, "Time");
        delay(2000);
        lcd.clear();
        Time();
      }

      if(gps.time.isUpdated())
      {
        lcd.clear();
        Time();
      }

      break;

    case 5:
      if(mode_change)
      {
        Display(0, 0, "Speed");
        delay(2000);
        lcd.clear();
        Speed();
      }

      if(gps.speed.isUpdated())
      {
        lcd.clear();
        Speed();
      }

      break;

    case 6:
      if(mode_change)
      {
        Display(0, 0, "Altitude");
        delay(2000);
        lcd.clear();
        Altitude();
      }

      if(gps.altitude.isUpdated())
      {
        lcd.clear();
        Altitude();
      }

      break;

    case 7:
      if(mode_change)
      {
        Display(0, 0, "Compass");
        delay(2000);
        lcd.clear();
        CourseDegree();
      }

      if(gps.course.isUpdated())
      {
        lcd.clear();
        CourseDegree();
      }

      break;

    case 8:
      if(mode_change)
      {
        Display(0, 0, "Satllite Info");
        delay(2000);
        lcd.clear();
        Info();
      }

      if(gps.satellites.isUpdated())
      {
        lcd.clear();
        Info();
      }

      break;

    default:
      lcd.clear();
      Display(0, 0, "ERROR");
      delay(1000);
      break;
  }
}

void Location()
{
  // Display longitude and latitude
  Display(0, 0, gps.location.lat());
  Display(0, 1, gps.location.lng());
}

void rawLocation()
{
  // Display raw longitudinal and latitude
  Display(0, 0, gps.location.rawLat().negative ? "-" : "+");
  Display(0, 1, gps.location.rawLat().deg);
}

void Date()
{
  // Display year, month, day
  Display(0, 0, gps.date.year());
  Display(4, 0, "/");
  Display(5, 0, gps.date.month());
  Display(7, 0, "/");
  Display(8, 1, gps.date.day());
}

void Time()
{
  // Display hour, min, second, centisecond
  Display(0, 0, gps.time.hour());
  Display(2, 0, ",");
  Display(3, 0, gps.time.minute());
  Display(5, 0, ",");
  Display(6, 0, gps.time.second());
  Display(8, 0, ",");
  Display(9, 1, gps.time.centisecond());
}

void Speed()
{
  switch(unit)
  {
    case 0:
      Display(0, 0, "100/knot");
      Display(0, 1, gps.speed.value());
      break;

    case 1:
      Display(0, 0, "knots/h");
      Display(0, 1, gps.speed.knots());
      break;

    case 2:
      Display(0, 0, "mph");
      Display(0, 1, gps.speed.mph());
      break;

    case 3:
      Display(0, 0, "m/s");
      Display(0, 1, gps.speed.mps());
      break;

    case 4:
      Display(0, 0, "kmph");
      Display(0, 1, gps.speed.kmph());
      break;

    default:
      Display(0, 0, "ERROR!");
      break;
  }
}

void Altitude()
{
  switch(unit)
  {
    case 0:
      Display(0, 0, "cm");
      Display(0, 1, gps.altitude.value());
      break;

    case 1:
      Display(0, 0, "meters");
      Display(0, 1, gps.altitude.meters());
      break;

    case 2:
      Display(0, 0, "miles");
      Display(0, 1, gps.altitude.miles());
      break;

    case 3:
      Display(0, 0, "km");
      Display(0, 1, gps.altitude.kilometers());
      break;

    case 4:
      Display(0, 0, "feet");
      Display(0, 1, gps.altitude.feet());
      break;

    default:
      Display(0, 0, "ERROR!");
      break;
  }
}

void CourseDegree()
{
  Display(0, 0, gps.course.deg());
}

void Info()
{
  Display(0, 0, "No. of fixes:");
  Display(0, 1, gps.satellites.value());
}