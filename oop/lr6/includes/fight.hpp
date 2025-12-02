#pragma once
#include "npc.hpp"
#include "visitor.hpp"
#include <memory>

class FightVisitor : public NPCVisitor {
  std::shared_ptr<NPC> attacker;
  int fightRange;
  bool isInRange(NPC &defender);

public:
  FightVisitor(std::shared_ptr<NPC> att, int range);

  void visit(Bear &defender) override;
  void visit(Bittern &defender) override;
  void visit(Desman &defender) override;
};
