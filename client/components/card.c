#include <raylib.h>
#include <stdbool.h>

#include "../config.h"
#include "../extern/raygui.h"

static bool is_texture_loaded = false;
static Texture2D product_image;

void card_display(
    int x,
    int y,
    const char *image_path,
    const char *name,
    const char *price) {

  Rectangle card_rect = {
      .x = x, .y = y, .width = CARD_WIDTH, .height = CARD_HEIGHT};
  Color transparent_black = {.r = 0, .g = 0, .b = 0, .a = 175};
  Rectangle name_price_rect = {
      card_rect.x, card_rect.y + 200, card_rect.width, 20};

  if (!is_texture_loaded) {
    product_image = LoadTexture(image_path);
    is_texture_loaded = true;
  }

  // Draw product image
  DrawTexturePro(
      product_image,
      (Rectangle){0, 0, card_rect.width, card_rect.height},
      card_rect,
      (Vector2){0, 0},
      0.0f,
      WHITE);

  DrawRectangleRec(name_price_rect, transparent_black);

  // Draw product name and price
  DrawText(name, name_price_rect.x + 10, name_price_rect.y, 20, WHITE);
  DrawText(
      price,
      name_price_rect.x + card_rect.width - MeasureText(price, 20) - 10,
      name_price_rect.y,
      20,
      WHITE);
}
