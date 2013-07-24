#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>

// Arena
const int arena_width = 800, arena_height = 600;

// Colors
ALLEGRO_COLOR black;

// Keyboard input
ALLEGRO_KEYBOARD_STATE _keyboard_state;
ALLEGRO_KEYBOARD_STATE *keyboard_state = &_keyboard_state;

// Death sound
ALLEGRO_SAMPLE *death_sound = NULL;
ALLEGRO_SAMPLE_ID *death_sound_id = NULL;

// Bad_guy_timer
ALLEGRO_TIMER *bad_guy_timer;

// Hero
double hero_x, hero_y;
double hero_speed = 3;
const int hero_size = 38;
const int hero_half_size = hero_size / 2;
ALLEGRO_BITMAP *hero_bitmap;

// Bad guy
const double bad_guy_starting_x = arena_width / 2,
   bad_guy_starting_y = arena_height / 2;
const double bad_guy_starting_speed = 2;
const double bad_guy_acceleration = 0.002;
const int bad_guy_size = 38;
const int bad_guy_half_size = bad_guy_size / 2;
double bad_guy_x = bad_guy_starting_x,
   bad_guy_y = bad_guy_starting_y;
double bad_guy_speed = bad_guy_starting_speed;
int bad_guy_count = 0;
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

   if (!al_install_audio())
   {
      printf("failed to install audio!\n");
      return -1;
   }

   if (!al_init_acodec_addon())
   {
      printf("failed to install audio codecs!\n");
      return -1;
   }

   if (!al_reserve_samples(1))
   {
      printf("failed to reserve 1 audio sample instance!\n");
      return -1;
   }

   death_sound = al_load_sample("death.wav");
   if (!death_sound)
   {
      printf("failed to load sample death.wav!\n");
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

   hero_x = arena_width / 4;
   hero_y = arena_height / 4;
   hero_bitmap = al_load_bitmap("hero.png");

   bad_guy_x = bad_guy_starting_x;
   bad_guy_y = bad_guy_starting_y;
   bad_guy_color = al_color_name("red");

   while (!al_key_down(keyboard_state, ALLEGRO_KEY_ESCAPE))
   {
      al_get_keyboard_state(keyboard_state);

      while (al_get_timer_count(bad_guy_timer) > bad_guy_count)
      {
         if (al_key_down(keyboard_state, ALLEGRO_KEY_LEFT) && hero_x > hero_half_size)
         {
            hero_x -= hero_speed;
         }
         if (al_key_down(keyboard_state, ALLEGRO_KEY_RIGHT) && hero_x < arena_width - hero_half_size)
         {
            hero_x += hero_speed;
         }
         if (al_key_down(keyboard_state, ALLEGRO_KEY_UP) && hero_y > hero_half_size)
         {
            hero_y -= hero_speed;
         }
         if (al_key_down(keyboard_state, ALLEGRO_KEY_DOWN) && hero_y < arena_height - hero_half_size)
         {
            hero_y += hero_speed;
         }

         // Some trigonometry to move toward the hero
         double bad_guy_angle = atan2(hero_y - bad_guy_y, hero_x - bad_guy_x);
         bad_guy_x += bad_guy_speed * cos(bad_guy_angle);
         bad_guy_y += bad_guy_speed * sin(bad_guy_angle);
         bad_guy_speed += bad_guy_acceleration;

         // Reset bad guy when he hits the hero
         if (abs(hero_x - bad_guy_x) < bad_guy_half_size && abs(hero_y - bad_guy_y) < bad_guy_half_size)
         {
            bad_guy_x = bad_guy_starting_x;
            bad_guy_y = bad_guy_starting_y;
            bad_guy_speed = bad_guy_starting_speed;

            if (death_sound_id)
            {
               al_stop_sample(death_sound_id);
               free(death_sound_id);
            }
            death_sound_id = (ALLEGRO_SAMPLE_ID *)malloc(sizeof(ALLEGRO_SAMPLE_ID));
            if (!al_play_sample(death_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, death_sound_id))
            {
               printf("failed to play sample death.wav!\n");
               return -1;
            }
         }

         al_add_timer_count(bad_guy_timer, -1);
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

