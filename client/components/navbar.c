#include <stdlib.h>

#include "../config.h"
#include "../extern/raygui.h"
#include "navbar.h"

#define TAB_COUNT 2
#define TAB_WIDTH 125
#define TAB_HEIGHT 42
#define TAB_SPACING 10

static const char *tabs_left[] = {"Home", "Products"};
static const char *tabs_right[] = {"About", "Contact"};
static const char *title = "Shopaholic";
static int current_tab = 0;

int navbar_display() {
  // Left navbar items
  for (size_t i = 0; i < TAB_COUNT; i++) {
    int tab_x = 10 + i * (TAB_WIDTH + TAB_SPACING);
    int tab_y = 10;
    if (GuiButton(
            (Rectangle){tab_x, tab_y, TAB_WIDTH, TAB_HEIGHT}, tabs_left[i])) {
      current_tab = i;
    }
  }

  // Title in the middle
  DrawText(
      title, (WINDOW_WIDTH / 2) - MeasureText(title, 35) / 2, 15, 35, BLACK);

  // Right navbar items
  for (size_t i = 0; i < TAB_COUNT; i++) {
    int tab_x = WINDOW_WIDTH - ((i + 1) * (TAB_WIDTH + TAB_SPACING));
    int tab_y = 10;
    if (GuiButton(
            (Rectangle){tab_x, tab_y, TAB_WIDTH, TAB_HEIGHT}, tabs_right[i])) {
      current_tab = i + 2;
    }
  }

  if (current_tab == 0) {
    DrawText("Welcome to Home", 200, 70, 20, GRAY);
  } else if (current_tab == 1) {
    DrawText("Product List", 200, 70, 20, GRAY);
  } else if (current_tab == 2) {
    DrawText("About Us", 200, 70, 20, GRAY);
  } else if (current_tab == 3) {
    DrawText("Contact Information", 200, 70, 20, GRAY);
  }

  return current_tab;
}
