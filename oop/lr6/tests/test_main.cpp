#include "../includes/entities.hpp"
#include "../includes/factory.hpp"
#include "../includes/fight.hpp"
#include "../includes/npc.hpp"
#include "../includes/observer.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(NPCFactoryTest, CreateObjects) {
  auto bear = NPCFactory::createNPC(BearType, 10, 20, "Misha");
  ASSERT_NE(bear, nullptr);
  EXPECT_EQ(bear->getType(), BearType);
  EXPECT_EQ(bear->getX(), 10);
  EXPECT_EQ(bear->getY(), 20);
  EXPECT_EQ(bear->getName(), "Misha");

  auto unknown = NPCFactory::createNPC(Unknown, 0, 0, "Nobody");
  EXPECT_EQ(unknown, nullptr);
}

TEST(CombatTest, BearKillsBittern) {
  auto bear = std::make_shared<Bear>(0, 0, "Bear");
  auto bittern = std::make_shared<Bittern>(0, 0, "Bittern");

  FightVisitor visitor(bear, 10);

  bittern->accept(visitor);

  EXPECT_TRUE(bear->isAlive());
  EXPECT_FALSE(bittern->isAlive());
}

TEST(CombatTest, BearIgnoresBear) {
  auto bear1 = std::make_shared<Bear>(0, 0, "Bear1");
  auto bear2 = std::make_shared<Bear>(0, 0, "Bear2");

  FightVisitor visitor(bear1, 10);
  bear2->accept(visitor);

  EXPECT_TRUE(bear1->isAlive());
  EXPECT_TRUE(bear2->isAlive());
}

TEST(CombatTest, DesmanKillsBear) {
  auto desman = std::make_shared<Desman>(0, 0, "Desman");
  auto bear = std::make_shared<Bear>(0, 0, "Bear");

  FightVisitor visitor(desman, 10);
  bear->accept(visitor);

  EXPECT_FALSE(bear->isAlive());
  EXPECT_TRUE(desman->isAlive());
}

TEST(CombatTest, BitternIsPeaceful) {
  auto bittern = std::make_shared<Bittern>(0, 0, "Bittern");
  auto desman = std::make_shared<Desman>(0, 0, "Desman");

  FightVisitor visitor(bittern, 10);
  desman->accept(visitor);

  EXPECT_TRUE(desman->isAlive());
  EXPECT_TRUE(bittern->isAlive());
}

TEST(CombatTest, DistanceCheck) {
  auto bear = std::make_shared<Bear>(0, 0, "Bear");
  auto bittern = std::make_shared<Bittern>(100, 0, "Bittern"); // Далеко

  FightVisitor visitor(bear, 50);
  bittern->accept(visitor);

  EXPECT_TRUE(bittern->isAlive()); // Не достал
}

TEST(ObserverTest, AttachAndNotify) {
  auto bear = std::make_shared<Bear>(0, 0, "Killer");
  auto victim = std::make_shared<Bittern>(0, 0, "Victim");

  auto obs = std::make_shared<TextObserver>();
  bear->attach(obs);

  EXPECT_NO_THROW(bear->notify(victim));
}
