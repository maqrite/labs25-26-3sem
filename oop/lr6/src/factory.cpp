#include "../includes/factory.hpp"
#include "../includes/entities.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

std::shared_ptr<NPC> NPCFactory::createNPC(NpcType type, int x, int y,
                                           const std::string &name) {
  switch (type) {
  case BearType:
    return std::make_shared<Bear>(x, y, name);
  case BitternType:
    return std::make_shared<Bittern>(x, y, name);
  case DesmanType:
    return std::make_shared<Desman>(x, y, name);
  default:
    return nullptr;
  }
}

void NPCFactory::save(const std::vector<std::shared_ptr<NPC>> &npcs,
                      const std::string &filename) {
  std::ofstream fs(filename);
  if (!fs.is_open()) {
    std::cerr << "saving file error" << std::endl;
    return;
  }

  fs << npcs.size() << std::endl;
  for (const auto &npc : npcs) {
    fs << npc->getType() << " " << npc->getName() << " " << npc->getX() << " "
       << npc->getY() << std::endl;
  }

  fs.close();
  std::cout << "Saved to " << filename << std::endl;
}

std::vector<std::shared_ptr<NPC>>
NPCFactory::load(const std::string &filename) {
  std::vector<std::shared_ptr<NPC>> result;
  std::ifstream fs(filename);

  if (!fs.is_open()) {
    std::cerr << "load file error" << std::endl;
    return result;
  }

  int count;
  fs >> count;

  for (int i = 0; i < count; ++i) {
    int typeInt;
    std::string name;
    int x, y;

    fs >> typeInt >> name >> x >> y;

    auto npc = createNPC((NpcType)typeInt, x, y, name);

    if (npc) {
      result.push_back(npc);
    }
  }

  fs.close();

  return result;
}
