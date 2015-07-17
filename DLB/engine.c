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

void InitSound(Sound sound[])
{
    sound[0].volume = 0;
    sound[1].volume = 0;

    sound[0].sample = al_load_sample("sounds/vento.ogg");
    sound[0].instance = al_create_sample_instance(sound[0].sample);
    al_attach_sample_instance_to_mixer(sound[0].instance, al_get_default_mixer());
    al_set_sample_instance_gain(sound[0].instance, sound[0].volume);

    sound[1].sample = al_load_sample("sounds/musica1.ogg");
    sound[1].instance = al_create_sample_instance(sound[1].sample);
    al_attach_sample_instance_to_mixer(sound[1].instance, al_get_default_mixer());
    al_set_sample_instance_gain(sound[1].instance, sound[1].volume);

    sound[2].sample = al_load_sample("sounds/alma1.ogg");
    sound[2].instance = al_create_sample_instance(sound[1].sample);
    al_attach_sample_instance_to_mixer(sound[2].instance, al_get_default_mixer());
}

void InitKey(Key key[])
{
    key[0].sample[0] = al_load_sample("sounds/passo1.ogg");
    key[0].instance[0] = al_create_sample_instance(key[0].sample[0]);
    al_attach_sample_instance_to_mixer(key[0].instance[0], al_get_default_mixer());

    key[1].sample[0] = al_load_sample("sounds/passo2.ogg");
    key[1].instance[0] = al_create_sample_instance(key[1].sample[0]);
    al_attach_sample_instance_to_mixer(key[1].instance[0], al_get_default_mixer());

    key[1].sample[1] = al_load_sample("sounds/passomadeira1.ogg");
    key[1].instance[1] = al_create_sample_instance(key[1].sample[1]);
    al_attach_sample_instance_to_mixer(key[1].instance[1], al_get_default_mixer());

    key[2].sample[0] = al_load_sample("sounds/passo3.ogg");
    key[2].instance[0] = al_create_sample_instance(key[2].sample[0]);
    al_attach_sample_instance_to_mixer(key[2].instance[0], al_get_default_mixer());

    key[2].sample[1] = al_load_sample("sounds/passomadeira2.ogg");
    key[2].instance[1] = al_create_sample_instance(key[2].sample[1]);
    al_attach_sample_instance_to_mixer(key[2].instance[1], al_get_default_mixer());
}


void InitPlayer(Player &player)
{
    player.lives = 5;
    player.run = 0;
    player.y = 0;
    player.x = 0;
}

void PlayerWalk(Player &player, Sound sound[], Key key[], bool *W, bool *A, bool *S, bool *D)
{
    if(player.y < 2000) //sons de passo na neve
    {
        if(*W)
        {
            al_play_sample_instance(key[0].instance[0]);
            player.y++;
        }

        if(*A)
        {
            al_play_sample_instance(key[2].instance[0]);
            player.x--;
        }

        if(*D)
        {
            al_play_sample_instance(key[2].instance[0]);
            player.x++;
        }

        if(*S)
        {
            al_play_sample_instance(key[1].instance[0]);
            player.y--;
        }
    }

    if(player.y >= 2000) //sons de passo na madeira
    {
        if(*W)
        {
            al_play_sample_instance(key[1].instance[1]);
            player.y++;
        }

        if(*A)
        {
            al_play_sample_instance(key[2].instance[1]);
            player.x--;
        }

        if(*D)
        {
            al_play_sample_instance(key[2].instance[1]);
            player.x++;
        }

        if(*S)
        {
            al_play_sample_instance(key[2].instance[1]);
            player.y--;
        }
    }

}

void Musics(Player &player, Sound sound[], bool *W, bool *S, bool *A, bool *D)
{
    //som do vento
    if(*W)
    {
        al_set_sample_instance_gain(sound[0].instance, sound[0].volume);
        if(sound[0].volume < 1)
            sound[0].volume+=0.001;
    }

    //twist and shout
    //quadrante IV
    if(player.y >= 900 &&
            player.y < 1100 &&
            player.x <= -300 &&
            player.x > -600)
    {
        al_set_sample_instance_gain(sound[1].instance, sound[1].volume);
        if((*S || *D) && sound[1].volume >= 0)
            sound[1].volume-=0.004;
        if((*W || *A) && sound[1].volume < 0.8)
            sound[1].volume+=0.004;
    }

    //quadrante III
    if(player.y >= 900 &&
       player.y < 1100 &&
       player.x <= -600 &&
       player.x > -900)
    {
        al_set_sample_instance_gain(sound[1].instance, sound[1].volume);
        if((*S || *A) && sound[1].volume >= 0)
            sound[1].volume-=0.004;
        if((*W || *D) && sound[1].volume < 0.8)
            sound[1].volume+=0.004;
    }

    //quadrante II
    if(player.y >= 1100 &&
       player.y < 1300 &&
       player.x <= -600 &&
       player.x > -900)
    {
        al_set_sample_instance_gain(sound[1].instance, sound[1].volume);
        if((*W || *A) && sound[1].volume >= 0)
            sound[1].volume-=0.004;
        if((*S || *D) && sound[1].volume < 0.8)
            sound[1].volume+=0.004;
    }

    //quadrante I
    if(player.y >= 1100 &&
       player.y < 1300 &&
       player.x > -600 &&
       player.x <= -300)
    {
        al_set_sample_instance_gain(sound[1].instance, sound[1].volume);
        if((*W || *D) && sound[1].volume >= 0)
            sound[1].volume-=0.004;
        if((*S || *A) && sound[1].volume < 0.8)
            sound[1].volume+=0.004;
    }

    if(player.y > 1300 ||
       player.y < 900 ||
       player.x > -300 ||
       player.x < -900)
    {
        al_set_sample_instance_gain(sound[1].instance, sound[1].volume);
        if((*W || *S || *A || *D) && sound[1].volume > 0)
            sound[1].volume-=0.004;
    }

}

void PlayMusics(Player &player, Sound sound[])
{
    if(player.y >= 2000)
        al_stop_sample_instance(sound[0].instance);
    if(player.y < 2000)
    al_play_sample_instance(sound[0].instance);
    al_play_sample_instance(sound[1].instance);
}


void PlayerRun(Player &player)
{
    player.run++;
}

