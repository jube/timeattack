#include "StageLimit.h"

#include <cassert>

#include <gf/Id.h>

#include "Settings.h"

using namespace gf::literals;

namespace ta {

  namespace {

    constexpr int GroundLimit = GroundExtent - 1;
    constexpr int TileOffset = 2 * TileExtent / 3;
    constexpr int GroundExtent2 = GroundExtent / 2;

  }

  StageLimit getStageLimitFromString(const std::string& str) {
    switch (gf::hash(str)) {
      case "BL"_id:
        return StageLimit::BottomLeft;
      case "BC"_id:
        return StageLimit::BottomCenter;
      case "BR"_id:
        return StageLimit::BottomRight;
      case "TL"_id:
        return StageLimit::TopLeft;
      case "TC"_id:
        return StageLimit::TopCenter;
      case "TR"_id:
        return StageLimit::TopRight;
      case "LB"_id:
        return StageLimit::LeftBottom;
      case "LC"_id:
        return StageLimit::LeftCenter;
      case "LT"_id:
        return StageLimit::LeftTop;
      case "RB"_id:
        return StageLimit::RightBottom;
      case "RC"_id:
        return StageLimit::RightCenter;
      case "RT"_id:
        return StageLimit::RightTop;
      default:
        assert(false);
        break;
    }

    return StageLimit::BottomLeft;
  }

  gf::Vector2i getInitialPosition(StageLimit limit) {
    switch (limit) {
      case StageLimit::BottomLeft:
      case StageLimit::LeftBottom:
        return gf::vec(TileExtent, GroundLimit * TileExtent);
      case StageLimit::BottomRight:
      case StageLimit::RightBottom:
        return gf::vec(GroundLimit * TileExtent, GroundLimit * TileExtent);
      case StageLimit::TopLeft:
      case StageLimit::LeftTop:
        return gf::vec(TileExtent, TileExtent);
      case StageLimit::TopRight:
      case StageLimit::RightTop:
        return gf::vec(GroundLimit * TileExtent, TileExtent);
      case StageLimit::TopCenter:
        return gf::vec(GroundExtent2 * TileExtent, TileExtent);
      case StageLimit::BottomCenter:
        return gf::vec(GroundExtent2 * TileExtent, GroundLimit * TileExtent);
      case StageLimit::LeftCenter:
        return gf::vec(TileExtent, GroundExtent2 * TileExtent);
      case StageLimit::RightCenter:
        return gf::vec(GroundLimit * TileExtent, GroundExtent2 * TileExtent);
    }

    assert(false);
    return { 0, 0 };
  }

  float getInitialAngle(StageLimit limit) {
    switch (limit) {
      case StageLimit::BottomLeft:
      case StageLimit::BottomCenter:
      case StageLimit::BottomRight:
        return -gf::Pi2;
      case StageLimit::TopLeft:
      case StageLimit::TopCenter:
      case StageLimit::TopRight:
        return gf::Pi2;
      case StageLimit::LeftBottom:
      case StageLimit::LeftCenter:
      case StageLimit::LeftTop:
        return 0.0f;
      case StageLimit::RightBottom:
      case StageLimit::RightCenter:
      case StageLimit::RightTop:
        return gf::Pi;
    }

    assert(false);
    return 0.0f;
  }

  gf::Vector2i getTarget(StageLimit limit) {
    gf::Vector2i base = getInitialPosition(limit);

    switch (limit) {
      case StageLimit::TopLeft:
      case StageLimit::TopCenter:
      case StageLimit::TopRight:
        return base - gf::diry(TileOffset);
      case StageLimit::BottomLeft:
      case StageLimit::BottomCenter:
      case StageLimit::BottomRight:
        return base + gf::diry(TileOffset);
      case StageLimit::LeftTop:
      case StageLimit::LeftCenter:
      case StageLimit::LeftBottom:
        return base - gf::dirx(TileOffset);
      case StageLimit::RightTop:
      case StageLimit::RightCenter:
      case StageLimit::RightBottom:
        return base + gf::dirx(TileOffset);
    }

    assert(false);
    return { 0, 0 };
  }

}
