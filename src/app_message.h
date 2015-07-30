#include <pebble.h>

enum {
  TIME = 0,
  EVENT = 1
};

static void inbox_received_callback(DictionaryIterator *iterator, void *context) 
  APP_LOG(APP_LOG_LEVEL_INFO, "App Message received by watch!");
   // Read first item
  Tuple *t = dict_read_first(iterator);
  
  // Store incoming information
  static char time[8];
  static char event[32];

  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
    case TIME:
      snprintf(time, sizeof(time), "%s", t->value->cstring);
      break;
    case EVENT:
      snprintf(event, sizeof(event), "%s", t->value->cstring);
      break;
    default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }
    update_calendar(time,event);
    // Look for next item
    t = dict_read_next(iterator);
  }
}

static void send_app_message(){  
  // Begin dictionary
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  // Add a key-value pair
  dict_write_uint8(iter, 0, 0);

  // Send the message!
  app_message_outbox_send();
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void setup_app_message(){
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}
