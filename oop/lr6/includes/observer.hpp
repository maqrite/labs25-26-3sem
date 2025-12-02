#pragma once
#include <fstream>
#include <memory>

class NPC;

class IFightObserver {
public:
  virtual void onKill(const std::shared_ptr<NPC> &attacker,
                      const std::shared_ptr<NPC> &victim) = 0;
  virtual ~IFightObserver() = default;
};

class TextObserver : public IFightObserver {
public:
  void onKill(const std::shared_ptr<NPC> &attacker,
              const std::shared_ptr<NPC> &victim) override;
};

class FileObserver : public IFightObserver {
  std::ofstream fileStream;

public:
  FileObserver();
  ~FileObserver();
  void onKill(const std::shared_ptr<NPC> &attacker,
              const std::shared_ptr<NPC> &victim) override;
};
