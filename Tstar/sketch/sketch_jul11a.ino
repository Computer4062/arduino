/*
  Main code file of the T-star program
  Note: references to pointer or Functions_pointer is not a C pointer but a name
        given to the cursor like symbol used in the LCD display
*/

#include "Interface.h"

void setup()
{
  Functions_Init();
}

void loop()
{
  // Page
  switch(Functions_currentPage)
  {
  case HOME: { Interface_Home(); break;}
  case MENU: { Interface_Menu(); break;}
  case RING: { Interface_Ring(); break; }
  case VIEW_TASKS: { Interface_ViewTasks(); break; }
  case ADD_TASKS: { Interface_AddTasks(); break; }
  case CHANGE_TIME: { Interface_ChangeTime(); break; }
  case CHANGE_DATE: { Interface_ChangeDate(); break; }
  }
}