#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

// Arena
int arena_width = 640, arena_height = 480;

// Hero
int hero_x, hero_y;
int hero_size = 10;
ALLEGRO_COLOR hero_color;

// Bad guy
int bad_guy_x, bad_guy_y;
int bad_guy_size = 10;
ALLEGRO_COLOR bad_guy_color;

int main(int argc, char **argv)
{
   if (!al_init())
   {
      printf("failed to initialize allegro!\n");
      return -1;
   }
 
   ALLEGRO_DISPLAY *display = al_create_display(arena_width, arena_height);
   if (!display)
   {
      printf("failed to create display!\n");
      return -1;
   }

   hero_x = arena_width / 2;
   hero_y = arena_height / 2;
   hero_color = al_map_rgb(0, 0, 255);

   bad_guy_x = arena_width / 4;
   bad_guy_y = arena_height / 4;
   bad_guy_color = al_map_rgb(255, 0, 0);

   al_draw_filled_rectangle(hero_x - hero_size, hero_y - hero_size, hero_x + hero_size, hero_y + hero_size, hero_color);
   al_draw_filled_circle(bad_guy_x - bad_guy_size, bad_guy_y - bad_guy_size, bad_guy_size, bad_guy_color);
   al_flip_display();

   al_rest(3);
 
   return 0;
}

