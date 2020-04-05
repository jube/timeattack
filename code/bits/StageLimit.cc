#include "StageLimit.h"

#include <cassert>

#include <gf/Id.h>

#include "Settings.h"

using namespace gf::literals;

namespace ta {

  namespace {

    constexpr int GroundLimit = GroundExtent - 1;
    constexpr int TileOffset = 2 * TileExtent / 3;

  }

  StageLimit getStageLimitFromString(const std::string& str) {
    switch (gf::hash(str)) {
      case "BL"_id:
        return StageLimit::BottomLeft;
      case "BR"_id:
        return StageLimit::BottomRight;
      case "TL"_id:
        return StageLimit::TopLeft;
      case "TR"_id:
        return StageLimit::TopRight;
      case "LB"_id:
        return StageLimit::LeftBottom;
      case "LT"_id:
        return StageLimit::LeftTop;
      case "RB"_id:
        return StageLimit::RightBottom;
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
    switch (limit) {
      case StageLimit::BottomLeft:
        return gf::vec(TileExtent, GroundLimit * TileExtent) + gf::diry(TileOffset);
      case StageLimit::LeftBottom:
        return gf::vec(TileExtent, GroundLimit * TileExtent) - gf::dirx(TileOffset);
      case StageLimit::BottomRight:
        return gf::vec(GroundLimit * TileExtent, GroundLimit * TileExtent) + gf::diry(TileOffset);
      case StageLimit::RightBottom:
        return gf::vec(GroundLimit * TileExtent, GroundLimit * TileExtent) + gf::dirx(TileOffset);
      case StageLimit::TopLeft:
        return gf::vec(TileExtent, TileExtent) - gf::diry(TileOffset);
      case StageLimit::LeftTop:
        return gf::vec(TileExtent, TileExtent) - gf::dirx(TileOffset);
      case StageLimit::TopRight:
        return gf::vec(GroundLimit * TileExtent, TileExtent) - gf::diry(TileOffset);
      case StageLimit::RightTop:
        return gf::vec(GroundLimit * TileExtent, TileExtent) + gf::dirx(TileOffset);
    }

    assert(false);
    return { 0, 0 };
  }

}
