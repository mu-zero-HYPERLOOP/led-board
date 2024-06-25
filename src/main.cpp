
#include "firmware/led_board.hpp"
#include "canzero/canzero.h"
#include "defaults.h"

int main() {
    canzero_init();
    can_defaults();
    led_board::begin();


  while (true) {
    led_board::update();

  }

}
