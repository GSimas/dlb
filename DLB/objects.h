#ifndef __objects_h
#define __objects_h

struct Key
{
    ALLEGRO_SAMPLE *sample[5];
    ALLEGRO_SAMPLE_INSTANCE *instance[5];
    ALLEGRO_SAMPLE_ID *sampleid[5];
};

struct Sound
{
    float volume;

    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *instance;
    ALLEGRO_SAMPLE_ID *sampleid;
};

struct Player
{
    int lives;
    int run;
    int y;
    int x;

    ALLEGRO_SAMPLE *passo[5];
    ALLEGRO_SAMPLE_INSTANCE *passo_instance[5];
};

#endif
