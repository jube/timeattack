#include "bits/TimeAttack.h"

#include "config.h"

int main() {
  ta::TimeAttack game(ta::TimeAttackDataDirectory);
  game.run();
  return 0;
}
