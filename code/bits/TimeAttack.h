#ifndef TA_TIME_ATTACK_H
#define TA_TIME_ATTACK_H

#include <gf/Random.h>
#include <gf/ResourceManager.h>
#include <gf/SegueEffects.h>
#include <gf/SceneManager.h>
#include <gf/TextureAtlas.h>

#include "CarChoiceScene.h"
#include "CountdownScene.h"
#include "CreditScene.h"
#include "FinishScene.h"
#include "HelpScene.h"
#include "MenuScene.h"
#include "PauseScene.h"
#include "RaceChoiceScene.h"
#include "ResultScene.h"
#include "StageScene.h"
#include "TimeAttackData.h"
#include "TimeAttackState.h"

namespace ta {

  struct TimeAttack : public gf::SceneManager {
    TimeAttack(gf::Path searchDirectory);

    // resources
    gf::Random random;
    gf::ResourceManager resources;
    gf::TextureAtlas atlas;

    // state and data
    TimeAttackData data;
    TimeAttackState state;

    // scenes
    MenuScene menu;
    CarChoiceScene carChoice;
    RaceChoiceScene raceChoice;
    HelpScene help;
    CreditScene credit;

    CountdownScene countdown;
    StageScene stage;
    FinishScene finish;
    ResultScene result;
    PauseScene pause;

    // segues
    gf::FadeSegueEffect fade;
    gf::ZoomBlurSegueEffect zoomBlur;
    gf::CheckerboardSegueEffect checkerboard;

    void startIntro();

    void setupRace(std::size_t raceIndex);
    void startRace();
  };

}

#endif // TA_TIME_ATTACK_H
