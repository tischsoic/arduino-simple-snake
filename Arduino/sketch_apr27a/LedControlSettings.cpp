#include "LedControlSettings.h"
#include "LedControl.h"

LedControl lc=LedControl(12,11,10,2);  // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime=100;  // Delay between Frames

void prepare_screen()
{
  lc.shutdown(0,false);  // Wake up displays
  lc.setIntensity(0,5);  // Set intensity levels
  lc.clearDisplay(0);  // Clear Displays
}
