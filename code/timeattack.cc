#include "bits/TimeAttack.h"

#include "config.h"

int main() {
  ta::TimeAttack game(TIMEATTACK_DATADIR);
  game.run();
  return 0;
}
