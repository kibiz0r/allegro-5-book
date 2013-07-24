#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <math.h>

// Arena
int arena_width = 800, arena_height = 600;

// Colors
ALLEGRO_COLOR black;

// Keyboard input
ALLEGRO_KEYBOARD_STATE _keyboard_state;
ALLEGRO_KEYBOARD_STATE *keyboard_state = &_keyboard_state;

// bad_guy_timer
ALLEGRO_TIMER *bad_guy_timer;

// Hero
double hero_x, hero_y;
double hero_speed = 3;
const int hero_size = 38;
const int hero_half_size = hero_size / 2;
ALLEGRO_BITMAP *hero_bitmap;

// Bad guy
double bad_guy_x, bad_guy_y;
const double bad_guy_starting_speed = 2;
double bad_guy_speed = bad_guy_starting_speed;
double bad_guy_acceleration = 0.002;
int bad_guy_count = 0;
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

   if (!al_install_keyboard())
   {
      printf("failed to install keyboard!\n");
      return -1;
   }

   bad_guy_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(100));
   if (!bad_guy_timer)
   {
      printf("failed to create timer!\n");
      return -1;
   }
   al_start_timer(bad_guy_timer);

   black = al_color_name("black");

   hero_x = arena_width / 2;
   hero_y = arena_height / 2;
   hero_bitmap = al_load_bitmap("hero.png");

   bad_guy_x = arena_width / 4;
   bad_guy_y = arena_height / 4;
   bad_guy_color = al_color_name("red");

   while (!al_key_down(keyboard_state, ALLEGRO_KEY_ESCAPE))
   {
      al_get_keyboard_state(keyboard_state);

      if (al_key_down(keyboard_state, ALLEGRO_KEY_LEFT))
      {
         hero_x--;
      }
      if (al_key_down(keyboard_state, ALLEGRO_KEY_RIGHT))
      {
         hero_x++;
      }
      if (al_key_down(keyboard_state, ALLEGRO_KEY_UP))
      {
         hero_y--;
      }
      if (al_key_down(keyboard_state, ALLEGRO_KEY_DOWN))
      {
         hero_y++;
      }

      al_clear_to_color(black);

      al_draw_bitmap(hero_bitmap,
         hero_x - hero_half_size,
         hero_y - hero_half_size,
         0);
      al_draw_filled_circle(bad_guy_x,
         bad_guy_y,
         bad_guy_half_size,
         bad_guy_color);

      al_flip_display();
   }
 
   return 0;
}

