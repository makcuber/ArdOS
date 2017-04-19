/*
<<<File Info>>>
Description: Open Source Arduino shell interface via serial communications

Developer: Jonathan Brunath

Date Created: 2/13/12/2016
Updated: 3/19/4/2017
*/

#include "Arduino.h"
#include "shell.h"

//initialize system settings and start basic processes
void setup() {
  //cmdsEnabled=false;
  serialControl(); //enable serial port if commands are enabled

  //if commands are enabled show the main menu on startup
  if (cmdsEnabled) {
    showMenu(0);
  }
  runMode=0;
}

//repeat the following code block for each cycle of the cpu
void loop() {
  //process incoming commands from serial port if enabled
  if (cmdsEnabled) {
    processCmds();
  }

  //determine which mode to run the system in
  switch(runMode) {
    case '0':
      //PUT YOUR RUNTIME CODE HERE
      break;
    default:
      //LEAVE THIS BLANK, THIS IS THE STOP STATE WHEN NOTHING RUNS
      break;
  }
}
