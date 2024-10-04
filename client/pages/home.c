#include "home.h"
#include "../extern/raygui.h"

void home_page_display() {
  DrawText("Welcome to Shopaholic!", 250, 50, 30, DARKGRAY);

  // Display the store description
  DrawText("Shopaholic is an online retail platform that enables simple "
           "transactions.",
           50, 100, 20, GRAY);
  DrawText(
      "Anyone can post a product for sale and any person can buy it with ease.",
      50, 130, 20, GRAY);
  DrawText("Our goal is to make online shopping accessible and enjoyable for "
           "everyone!",
           50, 160, 20, GRAY);

  // Draw more information
  DrawText("Key Features:", 50, 210, 25, DARKGREEN);
  DrawText("- Simple product listings", 50, 240, 20, GRAY);
  DrawText("- User-friendly interface", 50, 270, 20, GRAY);
  DrawText("- Secure transactions", 50, 300, 20, GRAY);
  DrawText("- Community feedback system", 50, 330, 20, GRAY);
}
