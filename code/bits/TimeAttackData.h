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

  struct RaceData {
    std::vector<StageData> stages;
  };

  struct TimeAttackData {
    TimeAttackData(gf::ResourceManager& resources);

    std::vector<RaceData> races;
    std::vector<gf::TileLayer> grounds;
  };

}

#endif // TA_RACE_DATA_H
