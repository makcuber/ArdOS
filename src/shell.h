/*
<<<File Info>>>
Description: Open Source Arduino shell interface via serial communications

Developer: Jonathan Brunath

Date Created: 4/8/10/2015
Updated: 7/11/12/2016
Updated: 1/12/12/2016
Updated: 2/13/12/2016
Updated: 3/19/4/2017
*/

#include "Arduino.h"
#include "tables.h"

//
//Variable Definitions
//

bool debugEnabled = true; //toggles debugging output over serial communications

//command processing variables
String cmdS; //String to store incoming command
String valS; //String to store first command parameter
String val2S; //String to store first command parameter
String val3S; //String to store first command parameter
char seperator = ','; //character to use to differentiate between the command and parameters in an incoming serial String (command)
char delimiter = '\n'; //character to use to signify the end of an incoming serial String (command)
bool cmdsEnabled = true; //boolean to store weather commands are enabled and will be processed or not
int baudRate = 9600; //integer to store the baud rate to use for serial communications (similar to transfer speed)
int runMode = 0; //defines which mode to run the system in

//menu variables
int consoleWidth = 40; //defines the default number of characters in the width of serial communications output console
int consoleHeight = 80; //defines the default number of characters in the height of serial communications output console
char lineBreakCharacter = '-'; //defines the default character to print when printing a line break to denote different sections of a texted based menu over serial communications
int currentMenu = 0; //denotes which menu is currently selected
char refreshMenuChar = 'r';
char returnToLastMenuChar = 'b';

//Print text to the serial console (used for debugging)
void debug(String output) {
  //verify that serial communications are configured
  if (Serial) {
    //Write text to serial console if debuging is enabled and serial communications are configured
    if ((debugEnabled) && (Serial)) {
      Serial.println(output);
    }
  }
}

//
//Serial Control functions
//

//Start or stop serial port
void serialControl(bool state) {
  if (state) {
    Serial.begin(baudRate);
  } else {
    Serial.end();
  }
}
//Start or stop serial port if commands are enabled
void serialControl() {
  serialControl(cmdsEnabled);
}

//
//User Interface Control Functions
//

//print a line of characters to denote seperate sections of a texted based menu over serial communications
void printLineBreak(char character, int width) {
  //verify that serial communications are configured
  if (Serial) {
    //repeat the following code the number of times as sepcified in the "width" parameter
    for (int i = 0; i < width; i++) {
      Serial.print(character); //print the specified character over serial communications without starting a newline after printing
    }
    Serial.print('\n'); //end the line by sending a return carriage character
  }
}
//print a line of characters to denote seperate sections of a texted based menu over serial communications
//using the default console width and default linebreak character
void printLineBreak() {
  printLineBreak(lineBreakCharacter, consoleWidth); //pass lineBreakCharacter and default consoleWidth to printLineBreak function
}
//print a bunch of blank lines over serial communications to clear the console screen of old output
void clearConsole() {
  //verify that serial communications are configured
  if (Serial) {
    //print a blank line "consoleHeight" number of times
    for (int i = 0; i < consoleHeight; i++) {
      Serial.println(); //print a blank line over serial communications
    }
  }
}
//print a text based title header for a menu over serial communications
void printHeader(String title) {
  clearConsole(); //clear old output from the serial console
  printLineBreak(); //print a line of characters to denote top of the title header
  Serial.println(title); //print the title text over serial communications
  printLineBreak(); //print a line of characters to denote bottom of the title header
}
//print a text based menu over serial communications
void showMenu(int menuID) {
  //figure out which menu to print
  switch (menuID) {
    case 0:
      //print the menu that corosponds with menu #0 (Help Menu)
      //print a title header
      printHeader("Main Menu");
      //print commands and descriptions
      Serial.println(String(refreshMenuChar) + " = Show current menu"); //print first command
      Serial.println(); //print a blank line
      Serial.println("1 = System Controls"); //print second command
      //print a line at bottom of the menu to show denote the end of the menu
      printLineBreak();
      break;
    case 1:
      //print the menu that corosponds with menu #1 (System Control Menu)
      //print a title header
      printHeader("System Control Menu");
      //print commands and descriptions
      Serial.println(String(refreshMenuChar) + " = Show current menu"); //print first command
      Serial.println(String(returnToLastMenuChar) + " = Return to Main Menu"); //print second command
      Serial.println(); //print a blank line

      Serial.println("1 = Set run mode (modeID)"); //print third command
      Serial.println("2 = Print available run modes"); //print fourth command
      Serial.println("3 = Set console width (width)"); //print fifth command
      Serial.println("4 = Set console height (height)"); //print sixth command
      Serial.println("5 = toggle debug mode"); //print seventh command

      //print a line at bottom of the menu to show denote the end of the menu
      printLineBreak();
      break;
    default:
      break;
  }
}
//Switch between menus
void switchMenus(int menuID) {
  currentMenu = menuID;
  showMenu(currentMenu);
}

//
//Command Processing
//

void mainMenu() {
  char cmd = cmdS.charAt(0); //convert command to an integer
  //int val = valS.toInt(); //convert first command parameter to an integer
  //int val2 = val2S.toInt(); //convert second command parameter to an integer
  if (cmdS != "-1") {
    //debug("Command Char: " + String(cmd));
    //debug("Val int: " + String(val));
    //debug("Val2 int: " + String(val2));
  }
  //call function that matches the command
  if (cmd == refreshMenuChar) {
    //call function that corosponds to command #0
    showMenu(currentMenu); //display help menu over the serial communications
  } else if (cmd == '1') {
    //call function that corosponds to command #1
    switchMenus(1);
  } else if (cmd == '2') {
    //call function that corosponds to command #2
    switchMenus(2);
  } else if (cmd == '3') {
    //call function that corosponds to command #3
    switchMenus(3);
  } else if (cmd == '4') {
    //call function that corosponds to command #4
    switchMenus(4);
  } else {
    if (cmdS != "-1") {
      //debug("Invalid Command");
    }
  }
}

//Process commands for System menu
void sysMenu() {
  char cmd = cmdS.charAt(0); //convert command to an integer
  int val = valS.toInt(); //convert first command parameter to an integer
  //int val2 = val2S.toInt(); //convert second command parameter to an integer

  //call function that matches the command
  if (cmd == refreshMenuChar) {
    //call function that corosponds to command #0
    showMenu(4); //display help menu over the serial communications

  } else if (cmd == returnToLastMenuChar) {
    //call function that corosponds to command #1
    switchMenus(0);

  } else if (cmd == '1') {
    //call function that corosponds to command #2
    //Set run mode (modeID)
    runMode = val;
    Serial.println("Run Mode = " + String(runMode));

  } else if (cmd == '2') {
    //call function that corosponds to command #3
    //Print available run modes


    tableObj t(2);
    t.titles->addData("ID #");
    t.titles->addData("Name");
    t.addRow("0", "Serial Commands only");
    delete &t;

  } else if (cmd == '3') {
    if (val > 0) {
      consoleWidth = val;
      Serial.println("Console Width = " + String(consoleWidth));
    }
  } else if (cmd == '4') {
    //call function that corosponds to command #6
    //Set console height (height)
    if (val > 0) {
      consoleHeight = val;
      Serial.println("Console Height = " + String(consoleHeight));
    }
  } else if (cmd == '5') {
    //call function that corosponds to command #7
    //toggle debug mode
    debugEnabled = !debugEnabled;
    if (debugEnabled) {
      Serial.println("Debug enabled");
    } else {
      Serial.println("Debug disabled");
    }
  }
}
//process commands from the serial port
void processCmds() {
  /*
  NOTICE: the way commands are current parsed can be made much more efficent. The
  code will be updated if the need arises and time allows for it.
  */

  //read incoming command with parameters if serial port is available(active)
  while (Serial.available()) {
    //debug("Reading command...");

    cmdS = Serial.readStringUntil(seperator); //read command
    valS = Serial.readStringUntil(seperator); //read first command parameter
    val2S = Serial.readStringUntil(seperator); //read second command parameter
    val3S = Serial.readStringUntil(delimiter); //read third command parameter

    debug("Command: " + cmdS);
    debug("Val: " + valS);
    debug("Val2: " + val2S);
    debug("Val3: " + val3S);
    debug("Current Menu: " + String(currentMenu));
    debug("");

  }

  switch (currentMenu) {
    case 0:
      mainMenu();
      break;
    case 1:
      sysMenu();
      break;
    default:
      //code placed here will run each time the loop function is called (every cpu cycle)
      break;
  }

  //reset command and parameters for next cycle
  cmdS = "-1";
  valS = "-1";
  val2S = "-1";
  val3S = "-1";
}
