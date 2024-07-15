#pragma once

#include <Arduino.h>
#include <DS3231.h>
#include "Symbols.h"
#include "Functions.h"

String menuOptions[5] = {"VIEW TASKS", "ADD TASKS", "CHANGE TIME", "CHANGE DATE"};

void Interface_Home()
{
  Functions_dt = clock.getDateTime();

  // Time
  Functions_LCD.setCursor(0, 0);
  Functions_LCD.print(String("   ") + clock.dateFormat("h:i:sA", Functions_dt));

  // Date
  Functions_LCD.setCursor(0, 1);
  Functions_LCD.print(clock.dateFormat("j | M | 20y", Functions_dt));

  Functions_Home();
}

void Interface_Menu()
{
  Functions_LCD.createChar(0, Symbols_leftArrow);
  Functions_LCD.createChar(1, Symbols_char1);
  Functions_LCD.createChar(2, Symbols_char2);
  Functions_LCD.createChar(3, Symbols_char3);
  Functions_LCD.createChar(4, Symbols_char4);
  Functions_LCD.createChar(5, Symbols_char5);

  // Pointers
  Functions_LCD.setCursor(15, Functions_pointer);
  Functions_LCD.write(byte(0));

  Functions_LCD.setCursor(14, Functions_pointer);
  Functions_LCD.write(byte(0));

  // Menu options
  switch(Functions_scrollPage)
  {
  // Display View and Add
  case 0:
  {
    Functions_LCD.setCursor(0, 0);
    Functions_LCD.write(1);
    Functions_LCD.setCursor(1, 0);
    Functions_LCD.print(menuOptions[0]);

    Functions_LCD.setCursor(0, 1);
    Functions_LCD.write(2);
    Functions_LCD.setCursor(1, 1);
    Functions_LCD.print(menuOptions[1]);

    break;
  }

  // Display change time and change date
  case 1:
  {
    Functions_LCD.setCursor(0, 0);
    Functions_LCD.write(3);
    Functions_LCD.setCursor(1, 0);
    Functions_LCD.print(menuOptions[2]);

    Functions_LCD.setCursor(0, 1);
    Functions_LCD.write(4);
    Functions_LCD.setCursor(1, 1);
    Functions_LCD.print(menuOptions[3]);

    break;
  }
  }

  Functions_Menu();
}

void Interface_ViewTasks()
{
  if(Functions_ViewTasks() == 1)
  {
    Functions_LCD.createChar(0, Symbols_leftArrow);

    // pointers
    Functions_LCD.setCursor(15, Functions_pointer);
    Functions_LCD.write(byte(0));

    Functions_LCD.setCursor(14, Functions_pointer);
    Functions_LCD.write(byte(0));

    /*
      Get the specific tasks to render
    */
    int index_1, index_2;
    String time_1, time_2;
    switch(Functions_scrollPage)
    {

    // Load task 1 and 2
    case 0:
    {
      index_1 = 0;
      time_1 = Functions_tasks[0];

      if(Functions_tasks[1] != "0")
      {
        index_2 = 1;
        time_2 = Functions_tasks[1];
      }
      else
        index_2  = -1;

      break;
    }

    // Load task 3 and 4
    case 1:
    {
      index_1 = 2;
      time_1 = Functions_tasks[2];

      if(Functions_tasks[3] != "0")
      {
        index_2 = 3;
        time_2 = Functions_tasks[3];
      }
      else
        index_2 = -1;

      break;
    }

    // Load task 5 and 6
    case 2:
    {
      index_1 = 4;
      time_1 = Functions_tasks[4];

      if(Functions_tasks[5] != "0")
      {
        index_2 = 5;
        time_2 = Functions_tasks[5];
      }
      else
        index_2 = -1;

      break;
    }
    }

    /*
      Render the loaded tasks
    */
    Functions_LCD.setCursor(0, 0);
    Functions_LCD.print("T" + String(index_1) + " " + time_1);

    if(index_2 != -1)
    {
      Functions_LCD.setCursor(0, 1);
      Functions_LCD.print("T" + String(index_2) + " " + time_2);
    }
  }
  else
  {
    // Remove the pointers
    Functions_LCD.setCursor(15, Functions_pointer);
    Functions_LCD.print(" ");

    Functions_LCD.setCursor(14, Functions_pointer);
    Functions_LCD.print(" ");
  }
}

void Interface_AddTasks()
{
  // If tasks can be added 0 will be returned
  if(Functions_AddTasks() == 0)
  {
    Functions_LCD.createChar(0, Symbols_upArrow);

    // pointers
    switch(Functions_pointer)
    {
      // point to hours
      case 0:
      {
        Functions_LCD.setCursor(3, 1);
        Functions_LCD.write(byte(0));
        Functions_LCD.setCursor(4, 1);
        Functions_LCD.write(byte(0));

        break;
      }

      // point to minutes
      case 1:
      {
        Functions_LCD.setCursor(6, 1);
        Functions_LCD.write(byte(0));
        Functions_LCD.setCursor(7, 1);
        Functions_LCD.write(byte(0));

        break;
      }

      // point to seconds
      case 2:
      {
        Functions_LCD.setCursor(9, 1);
        Functions_LCD.write(byte(0));
        Functions_LCD.setCursor(10, 1);
        Functions_LCD.write(byte(0));

        break;
      }

      // point to AM/PM
      case 3:
      {
        Functions_LCD.setCursor(11, 1);
        Functions_LCD.write(byte(0));
        Functions_LCD.setCursor(12, 1);
        Functions_LCD.write(byte(0));

        break;
      }
    }

    /*
     Display data like task number and task time
    */
    Functions_LCD.setCursor(0, 0);

    uint8_t index = 0;
    for(int i = 0; i < 6; i++)
    {
      if(Functions_tasks[i] == "0")
      {
        index = i;
        break;
      }
    }

    Functions_LCD.print("T" + String(index) + " " + Functions_newTime + "  ");
  }
}

void Interface_ChangeTime()
{
  Functions_LCD.createChar(0, Symbols_upArrow);

  // Time
  Functions_LCD.setCursor(0, 0);
  Functions_LCD.print("   " + Functions_newTime);

  // pointers
  switch(Functions_pointer)
  {
    case 0:
    {
      Functions_LCD.setCursor(3, 1);
      Functions_LCD.write(byte(0));
      Functions_LCD.setCursor(4, 1);
      Functions_LCD.write(byte(0));

      break;
    }

    case 1:
    {
      Functions_LCD.setCursor(6, 1);
      Functions_LCD.write(byte(0));
      Functions_LCD.setCursor(7, 1);
      Functions_LCD.write(byte(0));

      break;
    }

    case 2:
    {
      Functions_LCD.setCursor(9, 1);
      Functions_LCD.write(byte(0));
      Functions_LCD.setCursor(10, 1);
      Functions_LCD.write(byte(0));

      break;
    }

    case 3:
    {
      Functions_LCD.setCursor(11, 1);
      Functions_LCD.write(byte(0));
      Functions_LCD.setCursor(12, 1);
      Functions_LCD.write(byte(0));

      break;
    }
  }

  Functions_ChangeTime();
}

void Interface_ChangeDate()
{
  Functions_LCD.createChar(0, Symbols_upArrow);

  // Date
  Functions_LCD.setCursor(0, 0);
  Functions_LCD.print("  " + Functions_newDate);

  // pointers
  switch(Functions_pointer)
  {
  case 0:
  {
    Functions_LCD.setCursor(2, 1);
    Functions_LCD.write(byte(0));
    Functions_LCD.setCursor(3, 1);
    Functions_LCD.write(byte(0));
    Functions_LCD.setCursor(4, 1);
    Functions_LCD.write(byte(0));

    break;
  }
  case 1:
  {
    Functions_LCD.setCursor(6, 1);
    Functions_LCD.write(byte(0));
    Functions_LCD.setCursor(7, 1);
    Functions_LCD.write(byte(0));

    break;
  }
  case 2:
  {
    Functions_LCD.setCursor(9, 1);
    Functions_LCD.write(byte(0));
    Functions_LCD.setCursor(10, 1);
    Functions_LCD.write(byte(0));
    Functions_LCD.setCursor(11, 1);
    Functions_LCD.write(byte(0));
    Functions_LCD.setCursor(12, 1);
    Functions_LCD.write(byte(0));

    break;
  }
  }

  Functions_ChangeDate();
}

void Interface_Ring()
{
  Functions_LCD.createChar(0, Symbols_bell1);
  Functions_LCD.createChar(1, Symbols_bell2);
  Functions_LCD.createChar(2, Symbols_bell3);
  Functions_LCD.createChar(3, Symbols_bell4);
  Functions_LCD.createChar(4, Symbols_bell5);
  Functions_LCD.createChar(5, Symbols_bell6);

  // Time
  Functions_LCD.setCursor(0, 0);
  Functions_LCD.print(Functions_tasks[Functions_taskPointer] + "   ");

  // Task number and state of alarm
  Functions_LCD.setCursor(0, 1);
  Functions_LCD.print("T" + String(Functions_taskPointer) + "  RINGING  ");

  // Bell Symbol
  Functions_LCD.setCursor(13, 0);
  Functions_LCD.write(byte(0));
  Functions_LCD.setCursor(14, 0);
  Functions_LCD.write(byte(1));
  Functions_LCD.setCursor(15, 0);
  Functions_LCD.write(byte(2));
  Functions_LCD.setCursor(13, 1);
  Functions_LCD.write(byte(3));
  Functions_LCD.setCursor(14, 1);
  Functions_LCD.write(byte(4));
  Functions_LCD.setCursor(15, 1);
  Functions_LCD.write(byte(5));

  Functions_Ring();
}
