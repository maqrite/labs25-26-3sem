#pragma once
#include "observer.hpp"
#include "visitor.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum NpcType {
  Unknown = 0,
  BearType = 1,
  BitternType = 2,
  DesmanType = 3,
};

class NPC : public std::enable_shared_from_this<NPC> {
protected:
  NpcType type;
  std::string name;
  int x, y;
  std::vector<std::shared_ptr<IFightObserver>> observers;
  bool alive;

public:
  NPC(NpcType t, int _x, int _y, std::string _name);
  virtual ~NPC() = default;

  void attach(std::shared_ptr<IFightObserver> observer);
  void notify(const std::shared_ptr<NPC> &victim);

  virtual void accept(NPCVisitor &visitor) = 0;
  virtual void print();

  bool isAlive() const;
  void kill();
  int getX() const;
  int getY() const;
  std::string getName() const;
  NpcType getType() const;
};
