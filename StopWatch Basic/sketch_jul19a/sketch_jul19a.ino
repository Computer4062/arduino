#include <LiquidCrystal.h> 

#define RS 12
#define E  11
#define D4 5
#define D5 4
#define D6 3
#define D7 2  

#define A  10 // Backlight
#define v0 6  // Contrast

#define SWITCH 7

unsigned long startTime;
unsigned long currentTime;
unsigned long elapsedTime;

bool isRunning = false;
bool start     = false;   // Start StopWatch

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup()
{
  lcd.begin(16, 2); // Initialize LCD Display
  pinMode(A, OUTPUT);    // Initiialize backlight

  digitalWrite(A, HIGH); // Turn on backlight
  analogWrite(v0, 100);  // Value of contrast

  lcd.clear();

  pinMode(SWITCH, INPUT);

  lcd.print("STOP WATCH");       // Print stop watch for 1 second
  delay(1000);
  lcd.clear();
}

void loop()
{

  if(digitalRead(SWITCH) == LOW){
    if(!isRunning){                  // isRunning checks weather startTime has been recorded
      startTime = millis();
      isRunning = true;
    }else{
      isRunning = false;
    }

    start = true;    // Start the stop watch
  }else{
    start = false;   // Stop the stop watch
  }

  if(isRunning && start){                    // If isRunning has been calculated and start is true
    elapsedTime = millis() - startTime;      // Elapsed time is the final recorded time
    lcd.setCursor(0, 0);                      
    lcd.print(elapsedTime);                  // Print time

  }else {
    lcd.setCursor(0, 1);                     // Switch was released
    lcd.print("= ");
    lcd.print(elapsedTime);
  }
}