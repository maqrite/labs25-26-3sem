#pragma once
#include "npc.hpp"
#include <memory>
#include <string>
#include <vector>

class NPCFactory {
public:
  static std::shared_ptr<NPC> createNPC(NpcType type, int x, int y,
                                        const std::string &name);
  static void save(const std::vector<std::shared_ptr<NPC>> &npcs,
                   const std::string &filename);
  static std::vector<std::shared_ptr<NPC>> load(const std::string &filename);
};
