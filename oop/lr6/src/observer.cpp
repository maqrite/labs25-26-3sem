#include "../includes/observer.hpp"
#include "../includes/npc.hpp"
#include <iostream>
#include <memory>

void TextObserver::onKill(const std::shared_ptr<NPC> &attacker,
                          const std::shared_ptr<NPC> &victim) {
  std::cout << attacker->getName() << "killed" << victim->getName()
            << std::endl;
}

FileObserver::FileObserver() { fileStream.open("log.txt"); }

FileObserver::~FileObserver() {
  if (fileStream.is_open()) {
    fileStream.close();
  }
}

void FileObserver::onKill(const std::shared_ptr<NPC> &attacker,
                          const std::shared_ptr<NPC> &victim) {
  if (fileStream.is_open()) {
    fileStream << attacker->getName() << "killed" << victim->getName()
               << std::endl;
  }
}
