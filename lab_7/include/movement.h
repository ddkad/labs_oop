#pragma once

#include <atomic>

class BattleManager;

void movement_thread_func(BattleManager& battle_mgr, std::atomic<bool>& running);