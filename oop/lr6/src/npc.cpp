#include "../includes/npc.hpp"
#include <memory>

NPC::NPC(NpcType t, int _x, int _y, std::string _name)
    : type(t), x(_x), y(_y), name(_name), alive(true) {}

void NPC::attach(std::shared_ptr<IFightObserver> observer) {
  observers.push_back(observer);
}

void NPC::notify(const std::shared_ptr<NPC> &victim) {
  for (auto &o : observers) {
    o->onKill(shared_from_this(), victim);
  }
}

void NPC::print() {
  std::cout << type << " " << name << " " << x << " " << y << std::endl;
}

bool NPC::isAlive() const { return alive; }
void NPC::kill() { alive = false; }
int NPC::getX() const { return x; }
int NPC::getY() const { return y; }
std::string NPC::getName() const { return name; }
NpcType NPC::getType() const { return type; }
