#include <raylib.h>
#include <stdlib.h>

#include "config.h"
#include "components/navbar.h"
#include "raygui.h"

int main(void) {
  //SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
  SetTargetFPS(60);

  Texture2D productImage = LoadTexture("./external/test.png");
  const char *productName = "Sample Product";
  const char *productPrice = "$19.99";
  const char *productDescription =
      "This is a sample product description that gives a brief overview.";
  Rectangle cardRect = {100, 100, 375, 275};
  Color transparentWhite = {255, 255, 255, 128};
  Rectangle imageRect = {
      cardRect.x, cardRect.y, cardRect.width, cardRect.height};
  Rectangle namePriceRect = {cardRect.x, cardRect.y + 200, cardRect.width, 20};
  Rectangle descriptionRect = {
      cardRect.x, cardRect.y + 140, cardRect.width, 50};

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    navbar_display();
    DrawRectangleRec(cardRect, LIGHTGRAY);

    // Draw product image
    DrawTexturePro(
        productImage,
        (Rectangle){0, 0, productImage.width, productImage.height},
        imageRect,
        (Vector2){0, 0},
        0.0f,
        WHITE);

    DrawRectangle(
        namePriceRect.x,
        namePriceRect.y - 5,
        namePriceRect.width,
        namePriceRect.height + descriptionRect.height + 10,
        transparentWhite);

    // Draw product name and price
    DrawText(productName, namePriceRect.x + 10, namePriceRect.y, 20, BLACK);
    DrawText(
        productPrice,
        namePriceRect.x + cardRect.width - MeasureText(productPrice, 20) - 10,
        namePriceRect.y,
        20,
        DARKGREEN);

    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
