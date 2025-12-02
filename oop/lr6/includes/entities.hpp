#pragma once
#include "npc.hpp"
#include "visitor.hpp"
#include <string>

class Bear : public NPC {
public:
  Bear(int x, int y, std::string name);
  void accept(NPCVisitor &visitor) override;
};

class Bittern : public NPC {
public:
  Bittern(int x, int y, std::string name);
  void accept(NPCVisitor &visitor) override;
};

class Desman : public NPC {
public:
  Desman(int x, int y, std::string name);
  void accept(NPCVisitor &visitor) override;
};
