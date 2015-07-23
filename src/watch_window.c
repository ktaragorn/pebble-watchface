#include <pebble.h>
#include "watch_window.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_roboto_bold_subset_49;
static GFont s_res_gothic_14;
static GFont s_res_roboto_condensed_21;
static BitmapLayer *s_bitmaplayer_1;
static TextLayer *s_timetext;
static TextLayer *s_ampm;
static TextLayer *s_datemonth;
static TextLayer *s_nextevent;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, 1);
  #endif
  
  s_res_roboto_bold_subset_49 = fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(0, 0, 144, 106));
  bitmap_layer_set_background_color(s_bitmaplayer_1, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
  
  // s_timetext
  s_timetext = text_layer_create(GRect(3, 12, 125, 49));
  text_layer_set_background_color(s_timetext, GColorClear);
  text_layer_set_text_color(s_timetext, GColorWhite);
  text_layer_set_text(s_timetext, "00:00");
  text_layer_set_text_alignment(s_timetext, GTextAlignmentCenter);
  text_layer_set_font(s_timetext, s_res_roboto_bold_subset_49);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_timetext);
  
  // s_ampm
  s_ampm = text_layer_create(GRect(128, 43, 26, 20));
  text_layer_set_background_color(s_ampm, GColorClear);
  text_layer_set_text_color(s_ampm, GColorWhite);
  text_layer_set_text(s_ampm, "pm");
  text_layer_set_font(s_ampm, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_ampm);
  
  // s_datemonth
  s_datemonth = text_layer_create(GRect(1, 71, 143, 24));
  text_layer_set_background_color(s_datemonth, GColorClear);
  text_layer_set_text_color(s_datemonth, GColorWhite);
  text_layer_set_text(s_datemonth, "Wed, 25 Mar");
  text_layer_set_text_alignment(s_datemonth, GTextAlignmentCenter);
  text_layer_set_font(s_datemonth, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_datemonth);
  
  // s_nextevent
  s_nextevent = text_layer_create(GRect(3, 110, 138, 55));
  text_layer_set_text(s_nextevent, "Next Event HERE");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_nextevent);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_1);
  text_layer_destroy(s_timetext);
  text_layer_destroy(s_ampm);
  text_layer_destroy(s_datemonth);
  text_layer_destroy(s_nextevent);
}
// END AUTO-GENERATED UI CODE

static void update_time(struct tm *tick_time){  
  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Use 12 hour format
  strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(s_timetext, buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(tick_time);
}

static void setup_time_display(){
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  //display the right time at the start
  update_time(tick_time);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_watch_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
    
  setup_time_display();
}

void hide_watch_window(void) {
  window_stack_remove(s_window, true);
}
