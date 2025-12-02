#include "../includes/entities.hpp"
#include <string>

Bear::Bear(int x, int y, std::string name) : NPC(BearType, x, y, name) {}
void Bear::accept(NPCVisitor &visitor) { visitor.visit(*this); }

Bittern::Bittern(int x, int y, std::string name)
    : NPC(BitternType, x, y, name) {}
void Bittern::accept(NPCVisitor &visitor) { visitor.visit(*this); }

Desman::Desman(int x, int y, std::string name) : NPC(DesmanType, x, y, name) {}
void Desman::accept(NPCVisitor &visitor) { visitor.visit(*this); }
