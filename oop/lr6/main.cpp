#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "includes/entities.hpp"
#include "includes/factory.hpp"
#include "includes/fight.hpp"
#include "includes/npc.hpp"
#include "includes/observer.hpp"

int main() {
  std::srand(time(0));
  std::vector<std::shared_ptr<NPC>> npcs;
  auto textObs = std::make_shared<TextObserver>();
  auto fileObs = std::make_shared<FileObserver>();

  while (true) {
    std::cout << "1. add npc\n";
    std::cout << "2. save to file\n";
    std::cout << "3. load from file\n";
    std::cout << "4. print list\n";
    std::cout << "5. start Battle (Visitor)\n";
    std::cout << "0. exit\n";
    std::cout << "option: ";

    int cmd;
    std::cin >> cmd;

    if (cmd == 0)
      break;

    if (cmd == 1) {
      std::cout << "Type (1-Bear, 2-Bittern, 3-Desman): ";
      int type;
      std::cin >> type;
      std::cout << "X (0-500): ";
      int x;
      std::cin >> x;
      std::cout << "Y (0-500): ";
      int y;
      std::cin >> y;
      std::cout << "Name: ";
      std::string name;
      std::cin >> name;

      if (x < 0 || x > 500 || y < 0 || y > 500) {
        std::cout << "Invalid coordinates!\n";
        continue;
      }

      auto npc = NPCFactory::createNPC((NpcType)type, x, y, name);
      if (npc) {
        npc->attach(textObs);
        npc->attach(fileObs);
        npcs.push_back(npc);
      } else {
        std::cout << "Unknown type.\n";
      }
    } else if (cmd == 2) {
      std::string filename;
      std::cout << "Filename: ";
      std::cin >> filename;
      NPCFactory::save(npcs, filename);
    } else if (cmd == 3) {
      std::string filename;
      std::cout << "Filename: ";
      std::cin >> filename;
      npcs = NPCFactory::load(filename);
      for (auto &n : npcs) {
        n->attach(textObs);
        n->attach(fileObs);
      }
    } else if (cmd == 4) {
      std::cout << "--- NPC List ---\n";
      for (auto &n : npcs) {
        n->print();
      }
    } else if (cmd == 5) {
      int distance;
      std::cout << "Battle range: ";
      std::cin >> distance;

      for (auto &attacker : npcs) {
        for (auto &defender : npcs) {
          if (attacker != defender && attacker->isAlive() &&
              defender->isAlive()) {
            FightVisitor visitor(attacker, distance);
            defender->accept(visitor);
          }
        }
      }

      auto newEnd = std::remove_if(
          npcs.begin(), npcs.end(),
          [](const std::shared_ptr<NPC> &n) { return !n->isAlive(); });
      npcs.erase(newEnd, npcs.end());

      std::cout << "Battle ended. Survivors: " << npcs.size() << std::endl;
    }
  }
  return 0;
}
