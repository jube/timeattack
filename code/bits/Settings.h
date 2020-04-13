#ifndef TA_SETTINGS_H
#define TA_SETTINGS_H

#include <gf/Rect.h>
#include <gf/Vector.h>
#include <gf/VectorOps.h>

namespace ta {

  constexpr float PhysicsScale = 0.02;

  constexpr int GroundExtent = 12;
  constexpr gf::Vector2i GroundSize = gf::vec(GroundExtent, GroundExtent);

  constexpr int TileExtent = 128;
  constexpr gf::Vector2i TileSize = gf::vec(TileExtent, TileExtent);

  constexpr gf::Vector2i TileCount = { 18, 5 };

  constexpr float TargetDistance = 96.0f;

  constexpr gf::Vector2i ViewSize = GroundSize * TileSize;

  constexpr gf::RectF IntroView = gf::RectF::fromCenterSize({ 0.0f, 0.0f }, { 1000.0, 1000.0 });


}

#endif // TA_SETTINGS_H
