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

extern const int WIDTH = 800;
extern const int HEIGHT = 600;
extern const int FPS = 60;

void InitSound(Sound &sound)
{
    sound.sample[0] = al_load_sample("sounds/musica1.ogg");
    sound.instance[0] = al_create_sample_instance(sound.sample[0]);
    al_attach_sample_instance_to_mixer(sound.instance[0], al_get_default_mixer());
}


void InitPlayer(Player &player)
{
    player.lives = 5;
    player.run = 0;

    player.passo[0] = al_load_sample("sounds/passo1.ogg");
    player.passo_instance[0] = al_create_sample_instance(player.passo[0]);
    al_attach_sample_instance_to_mixer(player.passo_instance[0], al_get_default_mixer());

    player.passo[1] = al_load_sample("sounds/passo2.ogg");
    player.passo_instance[1] = al_create_sample_instance(player.passo[1]);
    al_attach_sample_instance_to_mixer(player.passo_instance[1], al_get_default_mixer());

    player.passo[2] = al_load_sample("sounds/passo3.ogg");
    player.passo_instance[2] = al_create_sample_instance(player.passo[2]);
    al_attach_sample_instance_to_mixer(player.passo_instance[2], al_get_default_mixer());
};

void PlayerRun(Player &player)
{
    player.run++;
};

