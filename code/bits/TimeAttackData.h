#ifndef TA_RACE_DATA_H
#define TA_RACE_DATA_H

#include <vector>

#include <gf/Polyline.h>
#include <gf/ResourceManager.h>
#include <gf/TileLayer.h>

#include "StageLimit.h"

namespace ta {

  struct StageData {
    gf::TileLayer tiles;
    gf::Polyline line;
    StageLimit start;
    StageLimit finish;
  };

  enum class RaceDifficulty {
    Easy,
    Medium,
    Hard,
    Challenging,
  };

  enum class RaceGround {
    Sand,
    Dirt,
    Asphalt,
  };

  struct RaceData {
    std::vector<StageData> stages;
    RaceDifficulty difficulty;
    RaceGround ground;
  };

  struct TerrainData {
    RaceGround ground;
    gf::TileLayer tiles;
  };

  struct TimeAttackData {
    TimeAttackData(gf::ResourceManager& resources);

    std::vector<RaceData> races;
    std::vector<TerrainData> terrains;

    const RaceData *findRace(RaceDifficulty difficulty, RaceGround ground) const;
    TerrainData *findTerrain(RaceGround ground);
  };

}

#endif // TA_RACE_DATA_H
