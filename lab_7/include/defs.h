#pragma once

#include <string>
#include <shared_mutex>

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;
const int NPC_COUNT = 50;
const int GAME_DURATION_SEC = 30;

enum class NpcType { Dragon, Toad, Bull };
std::string type_to_string(NpcType t);