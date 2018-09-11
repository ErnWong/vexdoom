#include <stdlib.h>
#include "doom/doomdef.h"
#include "doom/d_think.h"
#include "doom/p_pspr.h"
#include "doom/doomstat.h"

GameMode_t gamemode = indetermined;
int weapon_recoil;
int default_weapon_recoil;
int player_bobbing;
int default_player_bobbing;
int monsters_remember;
int default_monsters_remember;
int monster_infighting = 1;
int default_monster_infighting = 1;
int monster_friction = 1;
int default_monster_friction = 1;
int monster_backing, default_monster_backing;
int monster_avoid_hazards, default_monster_avoid_hazards;

