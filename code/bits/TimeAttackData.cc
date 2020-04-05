#include "TimeAttackData.h"

#include <gf/Tmx.h>
#include <gf/TmxOps.h>

#include "Settings.h"
#include "TilesetInfo.h"

namespace ta {

  namespace {
    struct GroundVisitor : public gf::TmxVisitor {
      GroundVisitor(std::vector<gf::TileLayer>& tiles, gf::ResourceManager& resources)
      : m_tiles(tiles)
      , m_resources(resources)
      {
      }

      void visitTileLayer(const gf::TmxLayers& map, const gf::TmxTileLayer& layer) override {
        gf::Log::info("Layer: '%s'\n", layer.name.c_str());
        m_tiles.emplace_back(gf::makeTileLayer(map, layer, m_resources));
      }

    private:
      std::vector<gf::TileLayer>& m_tiles;
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
      GroundVisitor visitor(grounds, resources);
      gf::TmxLayers layers;
      layers.loadFromFile(resources.getAbsolutePath("ground.tmx"));
      layers.visitLayers(visitor);
    }
  }

}
