#ifndef TA_RACE_DATA_H
#define TA_RACE_DATA_H

#include <vector>

#include <gf/Polyline.h>
#include <gf/ResourceManager.h>
#include <gf/TileLayer.h>

#include "RaceTypes.h"
#include "StageLimit.h"

namespace ta {

  struct StageData {
    gf::TileLayer tiles;
    gf::Polyline line;
    StageLimit start;
    StageLimit finish;
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

  struct ExtensionData {
    RaceGround ground;
    StageLimit limit;
    gf::TileLayer tiles;
  };

  struct TimeAttackData {
    TimeAttackData(gf::ResourceManager& resources);

    std::vector<RaceData> races;
    std::vector<TerrainData> terrains;
    std::vector<ExtensionData> extensions;

    std::size_t findRace(RaceDifficulty difficulty, RaceGround ground) const;
    TerrainData *findTerrain(RaceGround ground);
    ExtensionData *findExtension(RaceGround ground, StageLimit limit);
  };

}

#endif // TA_RACE_DATA_H
