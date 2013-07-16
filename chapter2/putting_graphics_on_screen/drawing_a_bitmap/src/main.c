#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>

// Arena
int arena_width = 800, arena_height = 600;

// Colors
ALLEGRO_COLOR black;

// Hero
int hero_x, hero_y;
const int hero_size = 38;
const int hero_half_size = hero_size / 2;
ALLEGRO_BITMAP *hero_bitmap;

// Bad guy
int bad_guy_x, bad_guy_y;
const int bad_guy_size = 38;
const int bad_guy_half_size = bad_guy_size / 2;
ALLEGRO_COLOR bad_guy_color;

int main(int argc, char **argv)
{
   if (!al_init())
   {
      printf("failed to initialize allegro!\n");
      return -1;
   }

   if (!al_init_image_addon())
   {
      printf("failed to initialize image I/O addon!\n");
      return -1;
   }

   if (!al_init_primitives_addon())
   {
      printf("failed to initialize primitives addon!\n");
      return -1;
   }
 
   ALLEGRO_DISPLAY *display = al_create_display(arena_width, arena_height);
   if (!display)
   {
      printf("failed to create display!\n");
      return -1;
   }

   black = al_color_name("black");

   hero_x = arena_width / 2;
   hero_y = arena_height / 2;
   hero_bitmap = al_load_bitmap("hero.png");

   bad_guy_x = arena_width / 4;
   bad_guy_y = arena_height / 4;
   bad_guy_color = al_color_name("red");

   al_draw_bitmap(hero_bitmap,
      hero_x - hero_half_size,
      hero_y - hero_half_size,
      0);
   al_draw_filled_circle(bad_guy_x - bad_guy_half_size,
      bad_guy_y - bad_guy_half_size,
      bad_guy_half_size,
      bad_guy_color);
   al_flip_display();

   al_rest(2); // pause for 2 seconds before exiting
 
   return 0;
}

