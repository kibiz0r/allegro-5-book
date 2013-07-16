#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

// Arena
int arena_width = 800, arena_height = 600;

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

   al_flip_display();

   al_rest(2); // pause for 2 seconds before exiting
 
   return 0;
}

