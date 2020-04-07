#include "TimeAttackData.h"

#include <gf/Id.h>
#include <gf/Tmx.h>
#include <gf/TmxOps.h>

#include "Settings.h"
#include "TilesetInfo.h"

using namespace gf::literals;

namespace ta {

  namespace {
    RaceDifficulty getDifficultyFromString(const std::string& str) {
      switch (gf::hash(str)) {
        case "easy"_id:
          return RaceDifficulty::Easy;
        case "medium"_id:
          return RaceDifficulty::Medium;
        case "hard"_id:
          return RaceDifficulty::Hard;
        case "challenging"_id:
          return RaceDifficulty::Challenging;
      }

      gf::Log::error("Unknown difficulty: '%s'\n", str.c_str());
      return RaceDifficulty::Easy;
    }

    RaceGround getGroundFromString(const std::string& str) {
      switch (gf::hash(str)) {
        case "sand"_id:
          return RaceGround::Sand;
        case "dirt"_id:
          return RaceGround::Dirt;
        case "asphalt"_id:
          return RaceGround::Asphalt;
      }

      gf::Log::error("Unknown ground: '%s'\n", str.c_str());
      return RaceGround::Sand;
    }

    struct TerrainVisitor : public gf::TmxVisitor {
      TerrainVisitor(std::vector<TerrainData>& terrains, gf::ResourceManager& resources)
      : m_terrains(terrains)
      , m_resources(resources)
      {
      }

      void visitTileLayer(const gf::TmxLayers& map, const gf::TmxTileLayer& layer) override {
        gf::Log::info("Layer: '%s'\n", layer.name.c_str());

        TerrainData terrain;

        // ground

        std::string ground = layer.properties.getStringProperty("ground", "");

        if (ground.empty()) {
          gf::Log::error("Missing 'ground' in a tile layer: '%s'\n", layer.name.c_str());
          return;
        }

        terrain.ground = getGroundFromString(ground);

        // tiles

        terrain.tiles = gf::makeTileLayer(map, layer, m_resources);

        m_terrains.emplace_back(std::move(terrain));
      }

    private:
      std::vector<TerrainData>& m_terrains;
      gf::ResourceManager& m_resources;
    };


    struct TimeAttackTmxVisitor : public gf::TmxVisitor {
      TimeAttackTmxVisitor(std::vector<RaceData>& races, gf::ResourceManager& resources)
      : m_races(races)
      , m_resources(resources)
      , m_current(nullptr)
      {
      }

      void visitGroupLayer(const gf::TmxLayers& map, const gf::TmxGroupLayer& layer) override {
        gf::Log::info("Group: '%s'\n", layer.name.c_str());

        RaceData race;
        m_current = &race;

        // difficulty

        std::string difficulty = layer.properties.getStringProperty("difficulty", "");

        if (difficulty.empty()) {
          gf::Log::error("Missing 'difficulty' in a group layer: '%s'\n", layer.name.c_str());
          return;
        }

        race.difficulty = getDifficultyFromString(difficulty);

        // ground

        std::string ground = layer.properties.getStringProperty("ground", "");

        if (ground.empty()) {
          gf::Log::error("Missing 'ground' in a group layer: '%s'\n", layer.name.c_str());
          return;
        }

        race.ground = getGroundFromString(ground);

        // stages

        for (auto& ptr : layer.layers) {
          ptr->accept(map, *this);
        }

        if (!race.stages.empty()) {
          std::reverse(race.stages.begin(), race.stages.end());
          m_races.emplace_back(std::move(race));
        }

        m_current = nullptr;
      }

      void visitTileLayer(const gf::TmxLayers& map, const gf::TmxTileLayer& layer) override {
        gf::Log::info("Layer: '%s'\n", layer.name.c_str());

        if (m_current == nullptr) {
          gf::Log::warning("Layer '%s' is not in a group!\n", layer.name.c_str());
          return;
        }

        StageData stage;

        // start

        std::string start = layer.properties.getStringProperty("start", "");

        if (start.empty()) {
          gf::Log::error("Missing 'start' in a tile layer: '%s'\n", layer.name.c_str());
          return;
        }

        stage.start = getStageLimitFromString(start);

        // finish

        std::string finish = layer.properties.getStringProperty("finish", "");

        if (finish.empty()) {
          gf::Log::error("Missing 'finish' in a tile layer: '%s'\n", layer.name.c_str());
          return;
        }

        stage.finish = getStageLimitFromString(finish);

        // tiles

        stage.tiles = gf::makeTileLayer(map, layer, m_resources);

        // line

        TilesetInfo info;

        info.appendLimit(stage.start);
        info.appendLimit(stage.finish);

        auto size = stage.tiles.getMapSize();

        for (int j = 0; j < size.height; ++j) {
          for (int i = 0; i < size.width; ++i) {
            int gid = stage.tiles.getTile({ i, j });

            if (gid != gf::TileLayer::NoTile) {
              gf::Vector2i base = TileSize * gf::vec(i, j);
              info.append(base, gid);
            }
          }
        }

        stage.line = info.computeLine();
        m_current->stages.push_back(std::move(stage));
      }

    private:
      std::vector<RaceData>& m_races;
      gf::ResourceManager& m_resources;
      RaceData *m_current;
    };

  }

  TimeAttackData::TimeAttackData(gf::ResourceManager& resources)
  {
    {
      TimeAttackTmxVisitor visitor(races, resources);
      gf::TmxLayers layers;
      layers.loadFromFile(resources.getAbsolutePath("data.tmx"));
      layers.visitLayers(visitor);
      std::reverse(races.begin(), races.end());
    }

    {
      TerrainVisitor visitor(terrains, resources);
      gf::TmxLayers layers;
      layers.loadFromFile(resources.getAbsolutePath("ground.tmx"));
      layers.visitLayers(visitor);
    }
  }

  const RaceData *TimeAttackData::findRace(RaceDifficulty difficulty, RaceGround ground) const {
    for (auto& race : races) {
      if (race.difficulty == difficulty && race.ground == ground) {
        return &race;
      }
    }

    return nullptr;
  }

  TerrainData *TimeAttackData::findTerrain(RaceGround ground) {
    for (auto& terrain : terrains) {
      if (terrain.ground == ground) {
        return &terrain;
      }
    }

    return nullptr;
  }

}
