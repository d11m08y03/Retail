#include <raylib.h>
#include <stdlib.h>

#include "components/navbar.h"
#include "config.h"
#include "extern/raygui.h"
#include "pages/home.h"
#include "pages/pages.h"
#include "pages/products.h"

int main(void) {
  SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    int current_page = navbar_display();

    switch (current_page) {
    case PAGES_HOME:
      home_page_display();
      break;
    case PAGE_PRODUCTS:
      products_page_display();
      break;
    default:
      break;
    }

    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
