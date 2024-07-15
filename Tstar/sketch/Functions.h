#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Buttons.h"
#include "Sort.h"

#define RS 12
#define E  13
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define HOME           0
#define MENU           1
#define VIEW_TASKS     2
#define ADD_TASKS      3
#define CHANGE_TIME    5
#define CHANGE_DATE    6
#define RING           7

#define CONTRAST_PIN 9
#define SPEAKER      10

uint8_t Functions_currentPage = HOME;
uint8_t Functions_pointer = 0;
uint8_t Functions_taskPointer = 0;
uint8_t Functions_scrollPage = 0;
uint8_t Functions_contrast = 60;

bool resetRinger = true;
bool mute = false;

String Functions_tasks[6] = {"08:43:20PM", "08:31:30PM", "09:28:20PM", "10:34:30AM", "12:50:45PM", "0"};
String Functions_newTime = "12:00:00AM";
String Functions_newDate = "Jan 01 2024";

LiquidCrystal Functions_LCD(RS, E, D4, D5, D6, D7);
DS3231 clock;
RTCDateTime Functions_dt;
RTCDateTime converter;

void SetTaskToRing();
void RingTone();
void TimeCounter(const uint8_t btn);
int ReturnMaxDays();

void Functions_Init()
{
  //pinMode(SPEAKER, OUTPUT); // <--- Adding this  makes the speaker insanely loud

  analogWrite(CONTRAST_PIN, Functions_contrast);
  Functions_LCD.begin(16, 2);

  clock.begin();
  //clock.setDateTime(__DATE__, __TIME__);
  clock.setDateTime(__DATE__, "10:34:27");

  Buttons_Init();
}

void Functions_Home()
{
  // Get time to ring from the tasks list
  if(resetRinger)
  {
    SetTaskToRing();
    resetRinger = false;
  }

  // If alarm is ringing
  if(clock.isAlarm1())
  {
    Functions_LCD.clear();
    Functions_currentPage = RING;
    resetRinger = true;
  }

  // Button controls for Home page
  Buttons_Update();
  switch(Buttons_ReturnPressedButton())
  {
  // Go to Menu Page
  case RIGHT_BTN:
  {
    Functions_LCD.clear();
    Buttons_ResetReturnedButton();
    Functions_currentPage = MENU;

    break;
  }
  }
}

void Functions_Menu()
{
  // BUtton controls for Menu page
  Buttons_Update();
  switch(Buttons_ReturnPressedButton())
  {
  // Go to Home page
  case RIGHT_BTN:
  {
    Functions_LCD.clear();
    Buttons_ResetReturnedButton();
    Functions_currentPage = HOME;

    break;
  }

   // Scroll up
  case UP_BTN:
  {
    if(Functions_pointer == 1) Functions_pointer = 0;
    else if(Functions_pointer == 0 && Functions_scrollPage == 0) {Functions_scrollPage = 1; Functions_pointer = 1;}
    else if(Functions_pointer == 0 && Functions_scrollPage == 1) {Functions_scrollPage = 0; Functions_pointer = 1;}
    
    Buttons_ResetReturnedButton();
    Functions_LCD.clear();

    break;
  }

  // Scroll down
  case DOWN_BTN:
  {
    if(Functions_pointer == 0) Functions_pointer = 1;
    else if(Functions_pointer == 1 && Functions_scrollPage == 0) {Functions_scrollPage = 1; Functions_pointer = 0;}
    else if(Functions_pointer == 1 && Functions_scrollPage == 1) {Functions_scrollPage = 0; Functions_pointer = 0;}
    
    Buttons_ResetReturnedButton();
    Functions_LCD.clear();

    break;
  }

  // Select one of the menu options
  case SELECT_BTN:
  {
    Buttons_ResetReturnedButton();
    Functions_LCD.clear();

    // View task option selected
    if(Functions_scrollPage == 0 && Functions_pointer == 0)      
    {
      Functions_LCD.clear(); 
      Functions_currentPage = VIEW_TASKS; 
      Functions_pointer = 0; 
      Functions_scrollPage = 0;
    }

    // Add task option selected
    else if(Functions_scrollPage == 0 && Functions_pointer == 1) 
    {
      Functions_LCD.clear(); 
      Functions_currentPage = ADD_TASKS; 
      Functions_pointer = 0; 
      Functions_scrollPage = 0; 
      Functions_newTime = "12:00:00AM";
    }

    // Change time option selected
    else if(Functions_scrollPage == 1 && Functions_pointer == 0) 
    {
      Functions_LCD.clear(); 
      Functions_currentPage = CHANGE_TIME;
      Functions_pointer = 0; 
      Functions_scrollPage = 0;
    }

    // Change date function selected
    else if(Functions_scrollPage == 1 && Functions_pointer == 1) 
    {
      Functions_LCD.clear(); 
      Functions_currentPage = CHANGE_DATE;
      Functions_pointer = 0; 
      Functions_scrollPage = 0; 
      Functions_newTime = "12:00:00AM";
    }
  }
  }
}

bool Functions_ViewTasks()
{
  // If there are no tasks then tell user
  if(Functions_tasks[0] == "0")
  {
    // Notify
    Functions_LCD.setCursor(0, 0);
    Functions_LCD.print("NO TASKS");

    // Button controls
    Buttons_Update();
    switch(Buttons_ReturnPressedButton())
    {
    // Go to Home page
    case RIGHT_BTN:
    {
      Functions_LCD.clear();
      Buttons_ResetReturnedButton();
      Functions_currentPage = HOME;
    }
    }

    return 0;
  }
  // If there are tasks...
  else
  {
    // Button controls
    Buttons_Update();
    switch(Buttons_ReturnPressedButton())
    {
    // Go to Home page
    case RIGHT_BTN:
    {
      Functions_LCD.clear();
      Buttons_ResetReturnedButton();
      Functions_currentPage = HOME;

      Functions_scrollPage = 0;
      Functions_pointer = 0;

      break;
    }

    // Scroll up
    case UP_BTN:
    {
      Buttons_ResetReturnedButton();
      Functions_LCD.clear();

      if(0 == Functions_scrollPage && 0 == Functions_pointer && Functions_tasks[5] != "0") {Functions_pointer = 1; Functions_scrollPage = 2;}                 // task 1 -> task 6
      else if(0 == Functions_scrollPage && 0 == Functions_pointer && Functions_tasks[4] != "0") {Functions_pointer = 0; Functions_scrollPage = 2;}            // task 1 -> task 5
      else if(0 == Functions_scrollPage && 0 == Functions_pointer && Functions_tasks[3] != "0") {Functions_pointer = 1; Functions_scrollPage = 1;}            // task 1 -> task 4
      else if(0 == Functions_scrollPage && 0 == Functions_pointer && Functions_tasks[2] != "0") {Functions_pointer = 0; Functions_scrollPage = 1;}            // task 1 -> task 3
      else if(0 == Functions_scrollPage && 0 == Functions_pointer && Functions_tasks[1] != "0") {Functions_pointer = 1; Functions_scrollPage = 0;}            // task 1 -> task 2
      else if(1 == Functions_scrollPage && 0 == Functions_pointer) {Functions_pointer = 1; Functions_scrollPage = 0;}                                         // task 3 -> task 2
      else if(2 == Functions_scrollPage && 0 == Functions_pointer) {Functions_pointer = 1; Functions_scrollPage = 1;}                                         // task 5 -> task 4
      else if(0 == Functions_scrollPage && 1 == Functions_pointer) Functions_pointer = 0;                                                                     // task 2 -> task 1
      else if(1 == Functions_scrollPage && 1 == Functions_pointer) Functions_pointer = 0;                                                                     // task 4 -> task 3
      else if(2 == Functions_scrollPage && 1 == Functions_pointer) Functions_pointer = 0;                                                                     // task 6 -> task 5

      break;
    }

    // Scroll down
    case DOWN_BTN:
    {
      Buttons_ResetReturnedButton();
      Functions_LCD.clear();

      if(0 == Functions_scrollPage && 0 == Functions_pointer && Functions_tasks[1] != "0") Functions_pointer = 1;                                             // task 1 -> task 2
      else if(1 == Functions_scrollPage && 0 == Functions_pointer && Functions_tasks[3] != "0") Functions_pointer = 1;                                        // task 3 -> task 4
      else if(1 == Functions_scrollPage && 0 == Functions_pointer && Functions_tasks[3] == "0") Functions_scrollPage = 0;                                     // task 3 -> task 1
      else if(2 == Functions_scrollPage && 0 == Functions_pointer && Functions_tasks[5] != "0") Functions_pointer = 1;                                        // task 5 -> task 6
      else if(2 == Functions_scrollPage && 0 == Functions_pointer && Functions_tasks[5] == "0") Functions_scrollPage = 0;                                     // task 5 -> task 1
      else if(0 == Functions_scrollPage && 1 == Functions_pointer && Functions_tasks[2] == "0") {Functions_scrollPage = 0; Functions_pointer = 0;}            // task 2 -> task 1
      else if(0 == Functions_scrollPage && 1 == Functions_pointer && Functions_tasks[2] != "0") {Functions_scrollPage = 1; Functions_pointer = 0;}            // task 2 -> task 3
      else if(1 == Functions_scrollPage && 1 == Functions_pointer && Functions_tasks[4] != "0") {Functions_scrollPage = 2; Functions_pointer = 0;}            // task 4 -> task 5
      else if(2 == Functions_scrollPage && 1 == Functions_pointer) {Functions_scrollPage = 0; Functions_pointer = 0;}                                         // task 6 -> task 1

      break;
    }

    // Delete
    case SELECT_BTN:
    {
      Buttons_ResetReturnedButton();
      Functions_LCD.clear();

      // Delete task 1
      if(0 == Functions_scrollPage && 0 == Functions_pointer) Functions_tasks[0] = "0";

      // Delete task 2
      else if(0 == Functions_scrollPage && 1 == Functions_pointer) 
      {
        Functions_tasks[1] = "0";
        if(Functions_tasks[2] != "0") Functions_pointer = 1;
        else Functions_pointer = 0;
      }

      // Delete task 3
      else if(1 == Functions_scrollPage && 0 == Functions_pointer) 
      {
        Functions_tasks[2] = "0";
        if(Functions_tasks[3] == "0")
        {
          Functions_pointer = 0;
          Functions_scrollPage = 0;
        }
      }

      // Delete task 4
      else if(1 == Functions_scrollPage && 1 == Functions_pointer) 
      {
        Functions_tasks[3] = "0";
        if(Functions_tasks[4] != "0") Functions_pointer = 1;
        else Functions_pointer = 0;
      }

      // Delete task 5
      else if(2 == Functions_scrollPage && 0 == Functions_pointer) 
      {
        Functions_tasks[4] = "0";
        if(Functions_tasks[5] == "0")
        {
          Functions_pointer = 1;
          Functions_scrollPage = 1;
        }
      }

      // Delete task 6
      else if(2 == Functions_scrollPage && 1 == Functions_pointer)
      {
        Functions_tasks[5] = "0";
        Functions_pointer = 0;
      }

      /*
      Rearrange tasks list
      */
      String new_tasks[6];
      int8_t new_Functions_tasks_index = 0;
      for(uint8_t i = 0; i < 6; i++)
      {
        if(Functions_tasks[i] != "0")
        {
          new_tasks[new_Functions_tasks_index] = Functions_tasks[i];
          new_Functions_tasks_index++;
        }
      }
      
      // Fill in the gaps with 0's
      for(uint8_t i = new_Functions_tasks_index; i < 6; i++)
        new_tasks[i] = "0";
      
      // Update the tasks list
      for(uint8_t i = 0; i < 6; i++)
        Functions_tasks[i] = new_tasks[i];

      break;
    }
    }

    return 1;
  }
}

bool Functions_AddTasks()
{
      // If all tasks are set then donot accept any more tasks
      if(Functions_tasks[5] == "0")
      {
        // Button controls
        Buttons_Update();
        switch(Buttons_ReturnPressedButton())
        {
          // Add the new task
          case SELECT_BTN:
          {
            Buttons_ResetReturnedButton();
            Functions_LCD.clear();

            // Iterate throught the for loop and add the task at an available position
            for(int i = 0; i < 6; i++)
            {
              if(Functions_tasks[i] == "0")
              {
                // Add task
                Functions_tasks[i] = Functions_newTime;

                // Redirrect them to home page
                Functions_currentPage = HOME;

                // Reset variables
                Functions_scrollPage = 0;
                Functions_pointer = 0;
                resetRinger = true;

                break;
              }
            }

            break;
          }

          // Count up
          case UP_BTN:
          {
            TimeCounter(UP_BTN);
            break;
          }

          // Count down
          case DOWN_BTN:
          {
            TimeCounter(DOWN_BTN);
            break;
          }

          // Move the pointer
          case RIGHT_BTN:
          {
            TimeCounter(RIGHT_BTN);
            break;
          }
        }

        return 0;
      }
      // If all 6 tasks are taken
      else
      {
        // Notify the user
        Functions_LCD.setCursor(0, 0);
        Functions_LCD.print("YOU CAN ONLY");
        Functions_LCD.setCursor(0, 1);
        Functions_LCD.print("HAVE 6 TASKS");

        // Button controls
        Buttons_Update();
        switch(Buttons_ReturnPressedButton())
        {
          // Go to Home page
          case RIGHT_BTN:
          {
            Buttons_ResetReturnedButton();
            Functions_LCD.clear();
            Functions_currentPage = HOME;

            break;
          }
        }

        return 1;
      }
}


void Functions_ChangeDate()
{
  // Button controls
  Buttons_Update();
  switch(Buttons_ReturnPressedButton())
  {
  // Change the date
  case SELECT_BTN:
  {
    Functions_dt = clock.getDateTime(); 
    clock.setDateTime(Functions_newDate.c_str(), clock.dateFormat("h:i:sA", Functions_dt));

    Functions_LCD.clear();
    Buttons_ResetReturnedButton();
    Functions_newDate = "Jan 01 2024";
    Functions_currentPage = HOME;

    break;
  }

  // Move the pointer
  case RIGHT_BTN:
  {
    if(Functions_pointer != 2) Functions_pointer++;
    else Functions_pointer = 0;

    Functions_LCD.clear();
    Buttons_ResetReturnedButton();

    break;
  }

  // Count up
  case UP_BTN:
  {
    switch(Functions_pointer)
    {
    // Count up month
    case 0:
    {
      String month = String(Functions_newDate[0]) + Functions_newDate[1] + Functions_newDate[2];

      if(month == "Jan") month = "Feb";
      else if(month == "Feb") month = "Mar";
      else if(month == "Mar") month = "Apr";
      else if(month == "Apr") month = "May";
      else if(month == "May") month = "Jun";
      else if(month == "Jun") month = "Jul";
      else if(month == "Jul") month = "Aug";
      else if(month == "Aug") month = "Sep";
      else if(month == "Sep") month = "Oct";
      else if(month == "Oct") month = "Nov";
      else if(month == "Nov") month = "Dec";
      else if(month == "Dec") month = "Jan";

      Functions_newDate[0] = month[0];
      Functions_newDate[1] = month[1];
      Functions_newDate[2] = month[2];

      Functions_LCD.clear();
      Buttons_ResetReturnedButton();

      break;
    }

    // Count up day
    case 1:
    {
      int day = (String(Functions_newDate[4]) + Functions_newDate[5]).toInt();

      if(day != ReturnMaxDays()) day++;
      else day = 1;

      if(day < 10)
      {
        Functions_newDate[4] = '0';
        Functions_newDate[5] = String(day)[0];
      }
      else
      {
        String d = String(day);
        
        Functions_newDate[4] = d[0];
        Functions_newDate[5] = d[1];
      }

      Functions_LCD.clear();
      Buttons_ResetReturnedButton();

      break;
    }

    // Count up year
    case 2:
    {
      int year = (String(Functions_newDate[7]) + Functions_newDate[8] + Functions_newDate[9] + Functions_newDate[10]).toInt();
      year++;

      String y = String(year);

      Functions_newDate[7] = y[0];
      Functions_newDate[8] = y[1];
      Functions_newDate[9] = y[2];
      Functions_newDate[10] = y[3];

      Functions_LCD.clear();
      Buttons_ResetReturnedButton();

      break;
    }
    }

    break;
  }

  // Count down
  case DOWN_BTN:
  {
    switch(Functions_pointer)
    {
    // Count down month
    case 0:
    {
      String month = String(Functions_newDate[0]) + Functions_newDate[1] + Functions_newDate[2];

      if(month == "Jan") month = "Dec";
      else if(month == "Dec") month = "Nov";
      else if(month == "Nov") month = "Oct";
      else if(month == "Oct") month = "Sep";
      else if(month == "Sep") month = "Aug";
      else if(month == "Aug") month = "Jul";
      else if(month == "Jun") month = "May";
      else if(month == "May") month = "Apr";
      else if(month == "Apr") month = "Apr";
      else if(month == "Mar") month = "Feb";
      else if(month == "Feb") month = "Jan";

      Functions_newDate[0] = month[0];
      Functions_newDate[1] = month[1];
      Functions_newDate[2] = month[2];

      Functions_LCD.clear();
      Buttons_ResetReturnedButton();

      break;
    }

    // Count down day
    case 1:
    {
      int day = (String(Functions_newDate[4]) + Functions_newDate[5]).toInt();

      if(day != 1) day--;
      else day = ReturnMaxDays();

      if(day < 10)
      {
        Functions_newDate[4] = '0';
        Functions_newDate[5] = String(day)[0];
      }
      else
      {
        String d = String(day);
        
        Functions_newDate[4] = d[0];
        Functions_newDate[5] = d[1];
      }

      Functions_LCD.clear();
      Buttons_ResetReturnedButton();

      break;
    }

    // Count down year
    case 2:
    {
      int year = (String(Functions_newDate[7]) + Functions_newDate[8] + Functions_newDate[9] + Functions_newDate[10]).toInt();
      year--;

      String y = String(year);

      Functions_newDate[7] = y[0];
      Functions_newDate[8] = y[1];
      Functions_newDate[9] = y[2];
      Functions_newDate[10] = y[3];

      Functions_LCD.clear();
      Buttons_ResetReturnedButton();

      break;
    }
    }

    break;
  }
  }
}

void Functions_ChangeTime()
{
      // Button controls
      Buttons_Update();
      switch(Buttons_ReturnPressedButton())
      {
        // Count up
        case UP_BTN:
        {
          TimeCounter(UP_BTN);
          break;
        }

        // Count down
        case DOWN_BTN:
        {
          TimeCounter(DOWN_BTN);
          break;
        }

        // Move the pointer
        case RIGHT_BTN:
        {
          TimeCounter(RIGHT_BTN);
          break;
        }

        // Change the time and goto Home page
        case SELECT_BTN:
        {
          Functions_dt = clock.getDateTime();

          /*
            Modify the time
          */
          if((String(Functions_newTime[8]) + Functions_newTime[9]) == "PM")
          {
            int hour = (String(Functions_newTime[0]) + Functions_newTime[1]).toInt();
            hour += 12;

            String h = String(hour);

            Functions_newTime[0] = h[0];
            Functions_newTime[1] = h[1];
          }
          else if((String(Functions_newTime[8]) + Functions_newTime[9] == "AM") && ((String(Functions_newTime[0]) + Functions_newTime[1]) == "12"))
          {
            Functions_newTime[0] = '0';
            Functions_newTime[1] = '0';
          }

          // Set the new time
          clock.setDateTime(clock.dateFormat("M j 20y", Functions_dt), Functions_newTime.c_str());

          Functions_currentPage = HOME;
          Functions_LCD.clear();
          Buttons_ResetReturnedButton();
          Functions_newTime = "12:00:00AM";
          Functions_pointer = 0;

          break;
        }
      }
}

void Functions_Ring()
{
  // Button controls
  Buttons_Update();
  switch(Buttons_ReturnPressedButton())
  {
  // Goto Home page
  case RIGHT_BTN:
  {
    Functions_LCD.clear();
    Buttons_ResetReturnedButton();
    Functions_currentPage = HOME;

    break;
  }
  }

  if(!mute)
    RingTone();
}

void SetTaskToRing()
{
  // Get the time to ring
  Functions_dt = clock.getDateTime();
  String timeToRing = Sort_ReturnTimeToRing(Functions_tasks, clock.dateFormat("h:i:sA", Functions_dt));
  
  // Set the alarm
  clock.clearAlarm1();
  clock.setAlarm1(
    0,
    (String(timeToRing[0]) + timeToRing[1]).toInt(),
    (String(timeToRing[3]) + timeToRing[4]).toInt(),
    (String(timeToRing[6]) + timeToRing[7]).toInt(),
    DS3231_MATCH_H_M_S
  );

  // Convert from 24 hour format to AM/PM format
  converter.hour   = (uint8_t)((String(timeToRing[0]) + timeToRing[1]).toInt());
  converter.minute = (uint8_t)((String(timeToRing[3]) + timeToRing[4]).toInt());
  converter.second = (uint8_t)((String(timeToRing[6]) + timeToRing[7]).toInt());

  String mod_timeToRing = clock.dateFormat("h:i:sA", converter);

  // Find the index of the task
  for(int i = 0; i < 6; i++)
  {
    if(mod_timeToRing == Functions_tasks[i])
    {
      Functions_taskPointer = i;
      break;
    }
  }
}

void RingTone()
{
  digitalWrite(SPEAKER, HIGH);
  delay(50);
  digitalWrite(SPEAKER, LOW);
}

// Call when ever some thing needs to be counted
void TimeCounter(const uint8_t btn)
{
  switch(btn)
  {
    // Count up
    case UP_BTN:
    {
      Buttons_ResetReturnedButton();

      // Go through the location of the arrow to check what to increase
      switch(Functions_pointer)
      {
        // Pointing at hours
        case 0:
        {
          // Get the hours
          String h = String(Functions_newTime[0]) + String(Functions_newTime[1]);
          uint8_t hours = h.toInt();

          // Increment the hours
          if(hours != 12) hours++;
          else hours = 1;

          // Write the new string
          h = "";
          if(hours < 10) h = "0" + String(hours);
          else h = String(hours);

          Functions_newTime[0] = h[0];
          Functions_newTime[1] = h[1];

          break;
        }

        // Pointing at minutes
        case 1:
        {
          // Get the minutes
          String m = String(Functions_newTime[3]) + String(Functions_newTime[4]);
          uint8_t minutes = m.toInt();

          // Increment the minutes
          if(minutes != 59) minutes++;
          else minutes = 0;

          // Write the new string
          m = "";
          if(minutes < 10) m = "0" + String(minutes);
          else m = String(minutes);

          Functions_newTime[3] = m[0];
          Functions_newTime[4] = m[1];

          break;
        }

        // Pointing at seconds
        case 2:
        {
          // Get the seconds
          String s = String(Functions_newTime[6]) + String(Functions_newTime[7]);
          uint8_t seconds = s.toInt();

          // Increment the seconds
          if(seconds != 59) seconds++;
          else seconds = 0;

          // Write the new string
          s = "";
          if(seconds < 10) s = "0" + String(seconds);
          else s = String(seconds);

          Functions_newTime[6] = s[0];
          Functions_newTime[7] = s[1];

          break;
        }

        // Pointing at day
        case 3:
        {
          // Get the day
          char day = Functions_newTime[8];

          // Increment the seconds
          if(day == 'P') day = 'A';
          else day = 'P';

          Functions_newTime[8] = day;

          break;
        }
      }

      break;
    }

    // Count down
    case DOWN_BTN:
    {
      Buttons_ResetReturnedButton();  // Reset the button

      // Go through the location of the arrow to check what to increase
      switch(Functions_pointer)
      {
        // Pointing at hours
        case 0:
        {
          // Get the hours
          String h = String(Functions_newTime[0]) + String(Functions_newTime[1]);
          uint8_t hours = h.toInt();

          // Increment the hours
          if(hours != 1) hours--;
          else hours = 12;

          // Write the new string
          h = "";
          if(hours < 10) h = "0" + String(hours);
          else h = String(hours);

          Functions_newTime[0] = h[0];
          Functions_newTime[1] = h[1];

          break;
        }

        // Pointing at minutes
        case 1:
        {
          // Get the minutes
          String m = String(Functions_newTime[3]) + String(Functions_newTime[4]);
          uint8_t minutes = m.toInt();

          // Increment the minutes
          if(minutes != 0) minutes--;
           else minutes = 59;

           // Write the new string
          m = "";
          if(minutes < 10) m = "0" + String(minutes);
           else m = String(minutes);

          Functions_newTime[3] = m[0];
          Functions_newTime[4] = m[1];

          break;
        }

        // Pointing at seconds
        case 2:
        {
          // Get the seconds
          String s = String(Functions_newTime[6]) + String(Functions_newTime[7]);
          uint8_t seconds = s.toInt();

          // Increment the seconds
          if(seconds != 0) seconds--;
          else seconds = 59;

          // Write the new string
          s = "";
          if(seconds < 10) s = "0" + String(seconds);
          else s = String(seconds);

          Functions_newTime[6] = s[0];
          Functions_newTime[7] = s[1];

          break;
        }

        // Pointing at day
        case 3:
        {
          // Get the day
          char day = Functions_newTime[8];

          // Increment the seconds
          if(day == 'P') day = 'A';
          else day = 'P';

          Functions_newTime[8] = day;

          break;
        }
      }

      break;
    }

    case RIGHT_BTN:
    {
      Functions_LCD.clear();
      if(Functions_pointer != 3) Functions_pointer++;
      else Functions_pointer = 0;
      Buttons_ResetReturnedButton();
      break;
    }
  }
}

int ReturnMaxDays()
{
  String month = String(Functions_newDate[0]) + Functions_newDate[1] + Functions_newDate[2];

  /*
    Get the maximum days in the month depending on what month or year it is
  */
  if(month == "Jan" || month == "Mar" || month == "May" || month == "Jul" || month == "Aug" || month == "Oct"|| month == "Dec") return 31;
  else if(month == "Apr" || month == "Jun" || month == "Sep" || month == "Nov") return 30;
  else if(atoi(String((Functions_newDate[7]) + Functions_newDate[8] + Functions_newDate[9] + Functions_newDate[10]).c_str()) % 4 == 0) return 29;
  else return 28;
}
