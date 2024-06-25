
#include "firmware/led_board.hpp"
#include "canzero/canzero.h"
#include "defaults.h"
#include "fsm/fsm.hpp"
#include "usb_serial.h"

int main() {
  canzero_init();
  can_defaults();
  led_board::begin();
  fsm::begin();


  while (true) {
    led_board::update();
    fsm::update();


  }

}
