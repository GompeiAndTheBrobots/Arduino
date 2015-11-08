#pragma once
/** \brief
 *  functions here control the robot as a whole.
 *  leds, bluetooth, arm, and line sensor, and music are immediate components.
 *  */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "BTClient.h"

class Robot {
  public:

    /** \brief lsingle accesor */
    static Robot *getInstance();

    /** \brief lsetup servos and stuff. called by main setup */
    void setup();

    bool carryingSpentRod();
    bool carryingNewRod();

    /** \brief print to 0,0 on lcd */
    void debugPrint(char *str);
    void debugPrint(int i);
    void debugPrint2(char *str);
    void debugPrint2(int i);

    /** \brief the object for reading and sending bluetooth message */
    BTClient btClient;

    /** \brief lcd to debug */
    LiquidCrystal lcd;

    /** \brief flag for blinking LEDs based on radiaiton
     * to turn off LEDs, set this to false
     */
    bool radiating = false;
    bool highRadiating = false;

    bool paused = false;

  private:

    /** \brief there's only one robot, so use private constructor and instance*/
    Robot();
    static Robot *instance;

    const static int spentRodPin = 23,
          newRodPin = 24;
};
