#pragma once

class Bear;
class Bittern;
class Desman;

class NPCVisitor {
public:
  virtual void visit(Bear &bear) = 0;
  virtual void visit(Bittern &bittern) = 0;
  virtual void visit(Desman &desman) = 0;
  virtual ~NPCVisitor() = default;
};
