#pragma once
#include <Arduino.h>

//https://gist.github.com/christophewang/ad056af4b3ab0ceebacf
void quickSort(long* array, int low, int high)
{
  long i = low;
  long j = high;
  long pivot = array[(i + j) / 2];
  long temp;

  while (i <= j)
  {
    while (array[i] < pivot)
      i++;
    while (array[j] > pivot)
      j--;
    if (i <= j)
    {
      temp = array[i];
      array[i] = array[j];
      array[j] = temp;
      i++;
      j--;
    }
  }
  if (j > low)
    quickSort(array, low, j);
  if (i < high)
    quickSort(array, i, high);
}

// Modify time value from 12 hour format to 24 hour format
String ModifyTime(String time)
{
  // Get the current hour
  String hour;
  hour += time[0];
  hour += time[1];

  // If AM leave it along unless it is 12:00AM in which case turn it to 00AM
  if (('A' == time[8]) && (hour == "12"))
  {
    time[0] = '0';
    time[1] = '0';
  }
  // If PM then add 12 to the hours value
  else if ('P' == time[8] && hour != "12")
  {
    // Convert string to int and increment
    int h = atoi(hour.c_str());
    h += 12;

    // Convert int back to string and append it
    String h_str = String(h);
    time[0] = h_str[0];
    time[1] = h_str[1];
  }

  // Remove the AM / PM letters
  time = time.substring(0, 8);

  return time;
}

String Sort_ReturnTimeToRing(String* tasks, String current_time)
{
  // Modify the time
  String modified_current_time = ModifyTime(current_time);

  // Modify the tasks
  String modified_tasks[7];
  for (int i = 0; i < 6; i++)
  {
    if (tasks[i] != "0")
      modified_tasks[i] = ModifyTime(tasks[i]);
    else
      modified_tasks[i] = "0";
  }
  modified_tasks[6] = "0";

  // Add the current time as well into the modified_tasks list
  for (int i = 0; i < 7; i++)
  {
    if (modified_tasks[i] == "0")
    {
      modified_tasks[i] = modified_current_time;
      break;
    }
  }

  // Sort the modified tasks list
  long cat_times_list[7];
  int rec = 0; // Record the number of items added
  for (int i = 0; i < 7; i++)
  {
    if (modified_tasks[i])
    {
      String newstr = "";
      for (int j = 0; j < 8; j++)
      {
        if (modified_tasks[i][j] != ':')
          newstr += modified_tasks[i][j];
      }

      cat_times_list[i] = atol(newstr.c_str());
      rec++;
    }
  }

  // Fill the rest of the spaces with -1 to indicate empty spaces
  for (int i = rec; i < 7; i++)
  {
    cat_times_list[i] = -1;
  }

  quickSort(cat_times_list, 0, 6);
  // Turn the sorted integers back into strings
  String new_modified_tasks[7];
  for (int i = 6; i >= 0; i--)
  {
    if (cat_times_list[i] != -1)
    {
      // Convert the int to string
      String temp = String(cat_times_list[i]);

      // Modify the string again
      if (temp.length() != 6)
      {
        for (int i = temp.length(); i < 6; i++)
        {
          temp = "0" + temp;
        }
      }

      new_modified_tasks[i] = temp;
    }
    else
    {
      new_modified_tasks[i] = "0";
    }
  }

  // Add the colons in the time format
  for (int i = 6; i >= 0; i--)
  {
    if (new_modified_tasks[i] != "0")
    {
      String temp = new_modified_tasks[i];
      new_modified_tasks[i] = "";
      for (int j = 0; j < 6; j++)
      {
        new_modified_tasks[i] += temp[j];

        if (j == 1 || j == 3)
          new_modified_tasks[i] += ":";
      }
    }
    else
      break;
  }

  // Choose the one closest to the current time
  String timeToRing;
  for (int i = 0; i < 7; i++)
  {
    if (modified_current_time == new_modified_tasks[i])
    {
      if (i == 6)
      {
        for (int j = 0; j < 7; j++)
        {
          if (new_modified_tasks[j] != "0")
          {
            timeToRing = new_modified_tasks[j];
            break;
          }
        }

        break;
      }
      else
      {
        timeToRing = new_modified_tasks[i + 1];
        break;
      }
    }
  }

  return timeToRing;
}
