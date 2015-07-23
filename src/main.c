#include <pebble.h>
#include "watch_window.h"

int main(void) {
  show_watch_window();
  app_event_loop();
  hide_watch_window();
}
