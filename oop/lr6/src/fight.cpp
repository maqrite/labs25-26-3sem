#include "../includes/fight.hpp"
#include "../includes/entities.hpp"
#include <cmath>
#include <memory>

FightVisitor::FightVisitor(std::shared_ptr<NPC> att, int range)
    : attacker(att), fightRange(range) {}

bool FightVisitor::isInRange(NPC &defender) {
  if (attacker->getName() == defender.getName()) {
    return false;
  }

  int dx = attacker->getX() - defender.getX();
  int dy = attacker->getY() - defender.getY();

  return (std::sqrt(dx * dx + dy * dy) <= fightRange);
}

void FightVisitor::visit(Bear &defender) {
  if (!isInRange(defender)) {
    return;
  }

  if (attacker->getType() == BearType) {
    return;
  }

  if (attacker->getType() == BitternType) {
    return;
  }

  if (attacker->getType() == DesmanType) {
    defender.kill();
    attacker->notify(std::make_shared<Bear>(defender));
  }
}

void FightVisitor::visit(Bittern &defender) {
  if (!isInRange(defender)) {
    return;
  }

  if (attacker->getType() == BearType) {
    defender.kill();
    attacker->notify(std::make_shared<Bittern>(defender));
  }
}

void FightVisitor::visit(Desman &defender) {
  if (!isInRange(defender)) {
    return;
  }

  if (attacker->getType() == BearType) {
    defender.kill();
    attacker->notify(std::make_shared<Desman>(defender));
  }
}
