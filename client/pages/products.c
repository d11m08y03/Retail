#include "products.h"
#include "../components/card.h"
#include "../config.h"

static const int gap_size = 100;
static const int cards_per_row = 3;
static const int total_width = 3 * CARD_WIDTH + 2 * gap_size;
static const int start = (WINDOW_WIDTH - total_width) / 2;

static const int total_row_width =
    cards_per_row * CARD_WIDTH + (cards_per_row - 1) * gap_size;
static const int start_x = (WINDOW_WIDTH - total_row_width) / 2;

void products_page_display() {
  card_display(start, 100, "./extern/night.png", "Balls", "$69.99");
  card_display(start + CARD_WIDTH + gap_size, 100, "./extern/night.png",
               "Balls", "$69.99");
  card_display(start + 2 * CARD_WIDTH + 2 * gap_size, 100, "./extern/night.png",
               "Balls", "$69.99");
}
