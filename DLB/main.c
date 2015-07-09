#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "engine.h"
#include "objects.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int FPS = 60;
enum KEYS {ESC, W, A, S, D, SPACE};
bool keys[6] = {false, false, false, false, false, false};


int main(void)
{

    bool done = false;
    bool redraw = true;

    struct Player player;
    struct Sound sound;

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    ALLEGRO_SAMPLE *vento = NULL;
    ALLEGRO_SAMPLE_INSTANCE *vento1 = NULL;

    //Allegro Initializations

    if(!al_init())
    {
        al_show_native_message_box(NULL, NULL, NULL, "falha ao inicializar allegro", NULL, 0);
        return -1;
    };

    al_install_keyboard();

    al_install_audio();
    if(!al_install_audio())
    {
        printf("Falha ao inicializar audio");
        return -1;
    };

    al_init_acodec_addon();
    if(!al_init_acodec_addon())
    {
        printf("Falha ao inicializar acodec addon");
        return -1;
    };

    al_reserve_samples(4);
    if(!al_reserve_samples(4))
    {
        printf("Falha ao reservar samples");
        return -1;
    };

    ALLEGRO_MONITOR_INFO info;
    int res_x, res_y;
    al_get_monitor_info(0, &info);
    res_x = info.x2 - info.x1;
    res_y = info.y2 - info.y1;

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    display = al_create_display(res_x, res_y);

    if(!display)
    {
        al_show_native_message_box(NULL, NULL, NULL, "falha ao inicializar display", NULL, 0);
        return -1;
    }

    float red_x = res_x / (float) WIDTH;
    float red_y = res_y / (float) HEIGHT;

    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_scale_transform(&transform, red_x, red_y);
    al_use_transform(&transform);

    ////////////////////////////////////////////////////////////////////////////////

    vento = al_load_sample("sounds/vento.ogg");
    vento1 = al_create_sample_instance(vento);
    al_attach_sample_instance_to_mixer(vento1, al_get_default_mixer());
    al_set_sample_instance_gain(vento1, 0);
    al_play_sample_instance(vento1);

    //Game Initializations
    InitPlayer(player);
    InitSound(sound);

    ////////////////////////////////////////////////////////////////////////////////

    //Allegro registers

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();

    ////////////////////////////////////////////////////////////////////////////////

    float i=0;

    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            done = true;

        else if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;

            if(keys[W])
            {
                al_play_sample_instance(player.passo_instance[0]);
                al_set_sample_instance_gain(vento1, i);
                i+=0.001;
            }
            if(keys[A])
                al_play_sample_instance(player.passo_instance[2]);
            if(keys[D])
                al_play_sample_instance(player.passo_instance[2]);
            if(keys[S])
            {
                al_play_sample_instance(player.passo_instance[1]);
                al_set_sample_instance_gain(vento1, i);
                i-=0.001;
            }
        }

        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_W:
                keys[W] = true;
                break;
            case ALLEGRO_KEY_A:
                keys[A] = true;
                break;
            case ALLEGRO_KEY_S:
                keys[S] = true;
                break;
            case ALLEGRO_KEY_D:
                keys[D] = true;
                break;
            }
        }

        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_W:
                keys[W] = false;
                break;
            case ALLEGRO_KEY_A:
                keys[A] = false;
                break;
            case ALLEGRO_KEY_S:
                keys[S] = false;
                break;
            case ALLEGRO_KEY_D:
                keys[D] = false;
                break;
            }
        }
    }

    //Allegro destruction
    al_destroy_display(display);
    al_destroy_sample(vento);
    al_destroy_sample_instance(vento1);
    al_destroy_sample_instance(player.passo_instance[0]);
    al_destroy_sample_instance(player.passo_instance[1]);
    al_destroy_sample_instance(player.passo_instance[2]);

    ////////////////////////////////////////////////////////////////////////////////

    return 0;
}
