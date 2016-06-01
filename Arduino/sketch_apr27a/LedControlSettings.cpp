#include "LedControlSettings.h"
#include "LedControl.h"

// Creating instance of LedControl
LedControl lc = LedControl(12,11,10,2);  // Pins: DIN,CLK,CS, # of Display connected

#define CYCLE_TIME 300

unsigned long delayTime = CYCLE_TIME;      // Delay between Frames

/**
 * Function preparing screen
 */
void prepare_screen()
{
  lc.shutdown(0,false);     // Wake up displays
  lc.setIntensity(0,5);     // Set intensity levels
  lc.clearDisplay(0);       // Clear Displays
}
