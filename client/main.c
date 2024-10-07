#include <raylib.h>
#include <stdlib.h>

#include "components/navbar.h"
#include "config.h"
#include "extern/raygui.h"
#include "pages/pages.h"
#include "pages/products.h"

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    int current_page = navbar_display();

    switch (current_page) {
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
