#ifndef __ENGINE_H_INCLUDED
#define __ENGINE_H_INCLUDED


void InitSound(struct Sound sound[]);
void InitKey(struct Key key[]);
void InitPlayer(struct Player &player);

void PlayerWalk(Player &player, Sound sound[], Key key[], bool *W, bool *A, bool *S, bool *D);
void PlayerRun(Player &player);

void Musics(Player &player, Sound sound[], bool *W, bool *S, bool *A, bool *D);
void PlayMusics(Player &player, Sound sound[]);

#endif
