#include "TilesetInfo.h"

#include <cassert>

#include <gf/Geometry.h>
#include <gf/VectorOps.h>

#include "Settings.h"

namespace ta {

  namespace {

    constexpr int TileLimit = TileExtent - 1;

    constexpr int TileExtent2 = TileExtent / 2;
    constexpr int TileLimit2 = TileExtent2 - 1;

    constexpr int TileTurnLo = static_cast<int>(TileExtent * (2 - gf::Sqrt3));
    constexpr int TileTurnHi = TileExtent - TileTurnLo;

    constexpr int GroundExtent2 = GroundExtent / 2;

    /*
     * tileset description
     */

    // first line
    constexpr int GidLeftRight                        = 0;
    constexpr int GidTopBottom                        = 1;
    constexpr int GidTightTurnTopLeft_WithCorner      = 2;
    constexpr int GidTop                              = 3;
    constexpr int GidTightTurnTopRight_WithCorner     = 4;
    constexpr int GidTightTurnTopLeft                 = 5;
    constexpr int GidTightTurnTopRight                = 6;
    constexpr int GidLargeTurnTopLeft_Center          = 7;
    constexpr int GidLargeTurnTopLeft_Right           = 8;
    constexpr int GidLargeTurnTopRight_Left           = 9;
    constexpr int GidLargeTurnTopRight_Center         = 10;
    constexpr int GidSlantedRight_TopLeft             = 11;
    constexpr int GidSlantedRight_TopCenter           = 12;
    constexpr int GidSlantedRight_TopRight            = 13;
    constexpr int GidSlantedUp_TopLeft                = 14;
    constexpr int GidSlantedUp_TopRight               = 15;
    constexpr int GidSlantedDown_TopLeft              = 16;
    constexpr int GidSlantedDown_TopRight             = 17;
    // second line
    constexpr int GidLeftRight_EndTop                 = 18;
    constexpr int GidTopBottom_EndRight               = 19;
    constexpr int GidLeft                             = 20;
    constexpr int GidBlank                            = 21;
    constexpr int GidRight                            = 22;
    constexpr int GidTightTurnBottomLeft              = 23;
    constexpr int GidTightTurnBottomRight             = 24;
    constexpr int GidLargeTurnTopLeft_Left            = 25;
    constexpr int GidCornerBottomRight                = 26;
    constexpr int GidCornerBottomLeft                 = 27;
    constexpr int GidLargeTurnTopRight_Right          = 28;
    constexpr int GidSlantedRight_BottomLeft          = 29;
    constexpr int GidSlantedRight_BottomCenter        = 30;
    constexpr int GidSlantedRight_BottomRight         = 31;
    constexpr int GidSlantedUp_CenterLeft             = 32;
    constexpr int GidSlantedUp_CenterRight            = 33;
    constexpr int GidSlantedDown_CenterLeft           = 34;
    constexpr int GidSlantedDown_CenterRight          = 35;
    // third line
    constexpr int GidTopBottom_EndLeft                = 36;
    constexpr int GidLeftRight_EndBottom              = 37;
    constexpr int GidTightTurnBottomLeft_WithCorner   = 38;
    constexpr int GidBottom                           = 39;
    constexpr int GidTightTurnBottomRight_WithCorner  = 40;
    constexpr int GidLeftRight_Finish                 = 41;
    constexpr int GidTopBottom_Finish                 = 42;
    constexpr int GidLargeTurnBottomLeft_Left         = 43;
    constexpr int GidCornerTopRight                   = 44;
    constexpr int GidCornerTopLeft                    = 45;
    constexpr int GidLargeTurnBottomRight_Right       = 46;
    constexpr int GidSlantedLeft_TopLeft              = 47;
    constexpr int GidSlantedLeft_TopCenter            = 48;
    constexpr int GidSlantedLeft_TopRight             = 49;
    constexpr int GidSlantedUp_BottomLeft             = 50;
    constexpr int GidSlantedUp_BottomRight            = 51;
    constexpr int GidSlantedDown_BottomLeft           = 52;
    constexpr int GidSlantedDown_BottomRight          = 53;
    // fourth line
    constexpr int GidJunction_Right                   = 54;
    constexpr int GidJunction_Bottom                  = 55;
    constexpr int GidFourCorners                      = 56;
    constexpr int GidTwoCorners_Left                  = 57;
    constexpr int GidTwoCorners_Top                   = 58;
    constexpr int GidDeadEnd_Bottom                   = 59;
    constexpr int GidDeadEnd_Left                     = 60;
    constexpr int GidLargeTurnBottomLeft_Center       = 61;
    constexpr int GidLargeTurnBottomLeft_Right        = 62;
    constexpr int GidLargeTurnBottomRight_Left        = 63;
    constexpr int GidLargeTurnBottomRight_Center      = 64;
    constexpr int GidSlantedLeft_BottomLeft           = 65;
    constexpr int GidSlantedLeft_BottomCenter         = 66;
    constexpr int GidSlantedLeft_BottomRight          = 67;
    constexpr int GidLeft_Finish                      = 68;
    constexpr int GidBlank_FinishHorizontal           = 69;
    constexpr int GidRight_Finish                     = 70;
    constexpr int GidBlank_Pit                        = 71;
    // fifth line
    constexpr int GidJunction_Top                     = 72;
    constexpr int GidJunction_Left                    = 73;
    constexpr int GidTwoCorners_Bottom                = 74;
    constexpr int GidTwoCorners_Right                 = 75;
    constexpr int GidDeadEnd_Right                    = 76;
    constexpr int GidDeadEnd_Top                      = 77;
    constexpr int GidLeftRight_StartUp                = 78;
    constexpr int GidTopBottom_StartRight             = 79;
    constexpr int GidLeftRight_StartDown              = 80;
    constexpr int GidTopBottom_StartLeft              = 81;
    constexpr int GidBlank_StartUp                    = 82;
    constexpr int GidBlank_StartRight                 = 83;
    constexpr int GidBlank_StartDown                  = 84;
    constexpr int GidBlank_StartLeft                  = 85;
    constexpr int GidTop_Finish                       = 86;
    constexpr int GidBlank_FinishVertical             = 87;
    constexpr int GidBottom_Finish                    = 88;
    constexpr int GidBlank_Caution                    = 89;

    /*
     * end of tileset description
     */

    constexpr int RoundPointCount = 8;

  }

  void TilesetInfo::clear() {
    m_segments.clear();
  }

  void TilesetInfo::append(gf::Vector2i base, int gid) {
    gf::SegmentI s;
    gf::Vector2i c; // center

    switch (gid) {
      case GidLeft:
      case GidLeft_Finish:
        s.p0 = base + gf::vec(0,          0);
        s.p1 = base + gf::vec(0,          TileExtent);
        m_segments.push_back(s);
//           gf::Log::debug("Left: [ %i, %i ][ %i, %i ]\n", s.p0.x, s.p0.y, s.p1.x, s.p1.y);
        break;
      case GidRight:
      case GidRight_Finish:
        s.p0 = base + gf::vec(TileLimit,  0);
        s.p1 = base + gf::vec(TileLimit,  TileExtent);
        m_segments.push_back(s);
        break;
      case GidLeftRight:
      case GidLeftRight_EndBottom:
      case GidLeftRight_EndTop:
      case GidLeftRight_Finish:
      case GidLeftRight_StartDown:
      case GidLeftRight_StartUp:
        append(base, GidLeft);
        append(base, GidRight);
        break;
      case GidTop:
      case GidTop_Finish:
        s.p0 = base + gf::vec(0,          0);
        s.p1 = base + gf::vec(TileExtent,   0);
        m_segments.push_back(s);
        break;
      case GidBottom:
      case GidBottom_Finish:
        s.p0 = base + gf::vec(0,          TileLimit);
        s.p1 = base + gf::vec(TileExtent,   TileLimit);
        m_segments.push_back(s);
        break;
      case GidTopBottom:
      case GidTopBottom_EndLeft:
      case GidTopBottom_EndRight:
      case GidTopBottom_Finish:
      case GidTopBottom_StartLeft:
      case GidTopBottom_StartRight:
        append(base, GidTop);
        append(base, GidBottom);
        break;

      case GidCornerTopLeft:
        // nothing
        break;
      case GidCornerTopRight:
        s.p0 = base + gf::vec(TileLimit,  0);
        s.p1 = base + gf::vec(TileExtent,   0);
        m_segments.push_back(s);
        break;
      case GidCornerBottomLeft:
        s.p0 = base + gf::vec(0,          TileLimit);
        s.p1 = base + gf::vec(0,          TileExtent);
        m_segments.push_back(s);
        break;
      case GidCornerBottomRight:
        s.p0 = base + gf::vec(TileExtent,   TileLimit);
        s.p1 = base + gf::vec(TileLimit,  TileLimit);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(TileLimit,  TileLimit);
        s.p1 = base + gf::vec(TileLimit,  TileExtent);
        m_segments.push_back(s);
        break;
      case GidTwoCorners_Top:
        append(base, GidCornerTopLeft);
        append(base, GidCornerTopRight);
        break;
      case GidTwoCorners_Bottom:
        append(base, GidCornerBottomLeft);
        append(base, GidCornerBottomRight);
        break;
      case GidTwoCorners_Left:
        append(base, GidCornerTopLeft);
        append(base, GidCornerBottomLeft);
        break;
      case GidTwoCorners_Right:
        append(base, GidCornerTopRight);
        append(base, GidCornerBottomRight);
        break;
      case GidFourCorners:
        append(base, GidCornerTopLeft);
        append(base, GidCornerTopRight);
        append(base, GidCornerBottomLeft);
        append(base, GidCornerBottomRight);
        break;

      case GidTightTurnTopLeft:
        s.p0 = base + gf::vec(0,          TileExtent);
        s.p1 = base + gf::vec(0,          TileLimit);
        m_segments.push_back(s);

//           gf::Log::debug("TightTurnTopLeft: [ %i, %i ][ %i, %i ]\n", s.p0.x, s.p0.y, s.p1.x, s.p1.y);

        c.x = base.x + TileLimit;
        c.y = base.y + TileLimit;

        for (int i = 0; i < RoundPointCount; ++i) {
          s.p0 = c + TileLimit * gf::unit(- gf::Pi + (i + 0) * gf::Pi2 / RoundPointCount) + 0.5f;
          s.p1 = c + TileLimit * gf::unit(- gf::Pi + (i + 1) * gf::Pi2 / RoundPointCount) + 0.5f;
          m_segments.push_back(s);

//             gf::Log::debug("TightTurnTopLeft: < %i, %i >< %i, %i >\n", s.p0.x, s.p0.y, s.p1.x, s.p1.y);
        }

        s.p0 = base + gf::vec(TileLimit,  0);
        s.p1 = base + gf::vec(TileExtent,   0);
        m_segments.push_back(s);

//           gf::Log::debug("TightTurnTopLeft: [ %i, %i ][ %i, %i ]\n", s.p0.x, s.p0.y, s.p1.x, s.p1.y);
        break;
      case GidTightTurnTopRight:
        c.x = base.x;
        c.y = base.y + TileLimit;

        for (int i = 0; i < RoundPointCount; ++i) {
          s.p0 = c + TileLimit * gf::unit(- gf::Pi2 + (i + 0) * gf::Pi2 / RoundPointCount) + 0.5f;
          s.p1 = c + TileLimit * gf::unit(- gf::Pi2 + (i + 1) * gf::Pi2 / RoundPointCount) + 0.5f;
          m_segments.push_back(s);
        }

        s.p0 = base + gf::vec(TileLimit,  TileLimit);
        s.p1 = base + gf::vec(TileLimit,  TileExtent);
        m_segments.push_back(s);
        break;
      case GidTightTurnBottomLeft:
        s.p0 = base + gf::vec(TileExtent,   TileLimit);
        s.p1 = base + gf::vec(TileLimit,  TileLimit);
        m_segments.push_back(s);

        c.x = base.x + TileLimit;
        c.y = base.y;

        for (int i = 0; i < RoundPointCount; ++i) {
          s.p0 = c + TileLimit * gf::unit(gf::Pi2 + (i + 0) * gf::Pi2 / RoundPointCount) + 0.5f;
          s.p1 = c + TileLimit * gf::unit(gf::Pi2 + (i + 1) * gf::Pi2 / RoundPointCount) + 0.5f;
          m_segments.push_back(s);
        }
        break;
      case GidTightTurnBottomRight:
        c.x = base.x;
        c.y = base.y;

        for (int i = 0; i < RoundPointCount; ++i) {
          s.p0 = c + TileLimit * gf::unit((i + 0) * gf::Pi2 / RoundPointCount) + 0.5f;
          s.p1 = c + TileLimit * gf::unit((i + 1) * gf::Pi2 / RoundPointCount) + 0.5f;
          m_segments.push_back(s);
        }
        break;
      case GidTightTurnTopLeft_WithCorner:
        append(base, GidTightTurnTopLeft);
        append(base, GidCornerBottomRight);
        break;
      case GidTightTurnTopRight_WithCorner:
        append(base, GidTightTurnTopRight);
        append(base, GidCornerBottomLeft);
        break;
      case GidTightTurnBottomLeft_WithCorner:
        append(base, GidTightTurnBottomLeft);
        append(base, GidCornerTopRight);
        break;
      case GidTightTurnBottomRight_WithCorner:
        append(base, GidTightTurnBottomRight);
        append(base, GidCornerTopLeft);
        break;

      case GidLargeTurnTopLeft_Left:
        s.p0 = base + gf::vec(0,          TileExtent);
        s.p1 = base + gf::vec(TileTurnLo, 0);
        m_segments.push_back(s);
        break;
      case GidLargeTurnTopLeft_Center:
        s.p0 = base + gf::vec(TileTurnLo, TileExtent);
        s.p1 = base + gf::vec(TileExtent,   TileTurnLo);
        m_segments.push_back(s);
        break;
      case GidLargeTurnTopLeft_Right:
        s.p0 = base + gf::vec(0,          TileTurnLo);
        s.p1 = base + gf::vec(TileExtent,   0);
        m_segments.push_back(s);
        break;
      case GidLargeTurnTopRight_Left:
        s.p0 = base + gf::vec(0,          0);
        s.p1 = base + gf::vec(TileExtent,   TileTurnLo);
        m_segments.push_back(s);
        break;
      case GidLargeTurnTopRight_Center:
        s.p0 = base + gf::vec(0,          TileTurnLo);
        s.p1 = base + gf::vec(TileTurnHi, TileExtent);
        m_segments.push_back(s);
        break;
      case GidLargeTurnTopRight_Right:
        s.p0 = base + gf::vec(TileTurnHi, 0);
        s.p1 = base + gf::vec(TileLimit,  TileExtent);
        m_segments.push_back(s);
        break;
      case GidLargeTurnBottomLeft_Left:
        s.p0 = base + gf::vec(0,          0);
        s.p1 = base + gf::vec(TileTurnLo, TileExtent);
        m_segments.push_back(s);
        break;
      case GidLargeTurnBottomLeft_Center:
        s.p0 = base + gf::vec(TileTurnLo, 0);
        s.p1 = base + gf::vec(TileExtent,   TileTurnHi);
        m_segments.push_back(s);
        break;
      case GidLargeTurnBottomLeft_Right:
        s.p0 = base + gf::vec(0,          TileTurnHi);
        s.p1 = base + gf::vec(TileExtent,   TileLimit);
        m_segments.push_back(s);
        break;
      case GidLargeTurnBottomRight_Left:
        s.p0 = base + gf::vec(0,          TileLimit);
        s.p1 = base + gf::vec(TileExtent,   TileTurnHi);
        m_segments.push_back(s);
        break;
      case GidLargeTurnBottomRight_Center:
        s.p0 = base + gf::vec(0,          TileTurnHi);
        s.p1 = base + gf::vec(TileTurnHi, 0);
        m_segments.push_back(s);
        break;
      case GidLargeTurnBottomRight_Right:
        s.p0 = base + gf::vec(TileTurnHi, TileExtent);
        s.p1 = base + gf::vec(TileLimit,  0);
        m_segments.push_back(s);
        break;

      case GidSlantedRight_BottomLeft:
        s.p0 = base + gf::vec(0,          TileExtent);
        s.p1 = base + gf::vec(0,          TileLimit);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(0,          TileLimit);
        s.p1 = base + gf::vec(TileLimit2, 0);
        m_segments.push_back(s);
        break;
      case GidSlantedRight_TopLeft:
        s.p0 = base + gf::vec(TileLimit2, TileExtent);
        s.p1 = base + gf::vec(TileLimit,  0);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(TileLimit,  0);
        s.p1 = base + gf::vec(TileExtent,   0);
        m_segments.push_back(s);
        break;
      case GidSlantedRight_TopCenter:
        // nothing
        break;
      case GidSlantedRight_BottomCenter:
        s.p0 = base + gf::vec(TileLimit,  TileExtent);
        s.p1 = base + gf::vec(TileLimit,  TileLimit);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(TileLimit,  TileLimit);
        s.p1 = base + gf::vec(TileExtent,   TileLimit);
        m_segments.push_back(s);
        break;
      case GidSlantedRight_BottomRight:
        s.p0 = base + gf::vec(0,          TileLimit);
        s.p1 = base + gf::vec(TileLimit2, 0);
        m_segments.push_back(s);
        break;
      case GidSlantedRight_TopRight:
        s.p0 = base + gf::vec(TileLimit2, TileExtent);
        s.p1 = base + gf::vec(TileLimit,  0);
        m_segments.push_back(s);
        break;

      case GidSlantedLeft_TopLeft:
        s.p0 = base + gf::vec(0,          0);
        s.p1 = base + gf::vec(TileExtent2,  TileExtent);
        m_segments.push_back(s);
        break;
      case GidSlantedLeft_BottomLeft:
        s.p0 = base + gf::vec(TileExtent2,  0);
        s.p1 = base + gf::vec(TileLimit,  TileLimit);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(TileLimit,  TileLimit);
        s.p1 = base + gf::vec(TileExtent,   TileLimit);
        m_segments.push_back(s);
        break;
      case GidSlantedLeft_BottomCenter:
        s.p0 = base + gf::vec(0,          TileLimit);
        s.p1 = base + gf::vec(0,          TileExtent);
        m_segments.push_back(s);
        break;
      case GidSlantedLeft_TopCenter:
        s.p0 = base + gf::vec(TileLimit,  0);
        s.p1 = base + gf::vec(TileExtent,   0);
        m_segments.push_back(s);
        break;
      case GidSlantedLeft_TopRight:
        s.p0 = base + gf::vec(0,          0);
        s.p1 = base + gf::vec(TileExtent2,  TileExtent);
        m_segments.push_back(s);
        break;
      case GidSlantedLeft_BottomRight:
        s.p0 = base + gf::vec(TileExtent2,  0);
        s.p1 = base + gf::vec(TileLimit,  TileLimit);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(TileLimit,  TileLimit);
        s.p1 = base + gf::vec(TileLimit,  TileExtent);
        m_segments.push_back(s);
        break;

      case GidSlantedUp_CenterLeft:
        // nothing
        break;
      case GidSlantedUp_TopLeft:
        s.p0 = base + gf::vec(0,          TileExtent);
        s.p1 = base + gf::vec(0,          TileLimit);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(0,          TileLimit);
        s.p1 = base + gf::vec(TileExtent,   TileExtent2);
        m_segments.push_back(s);
        break;
      case GidSlantedUp_TopRight:
        s.p0 = base + gf::vec(0,          TileExtent2);
        s.p1 = base + gf::vec(TileLimit,  0);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(TileLimit,  0);
        s.p1 = base + gf::vec(TileExtent,   0);
        m_segments.push_back(s);
        break;
      case GidSlantedUp_BottomLeft:
        s.p0 = base + gf::vec(0,          TileLimit);
        s.p1 = base + gf::vec(TileExtent,   TileLimit2);
        m_segments.push_back(s);
        break;
      case GidSlantedUp_BottomRight:
        s.p0 = base + gf::vec(0,          TileLimit2);
        s.p1 = base + gf::vec(TileLimit,  0);
        m_segments.push_back(s);
        break;
      case GidSlantedUp_CenterRight:
        s.p0 = base + gf::vec(TileLimit,  TileExtent);
        s.p1 = base + gf::vec(TileLimit,  TileLimit);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(TileLimit,  TileLimit);
        s.p1 = base + gf::vec(TileExtent,   TileLimit);
        m_segments.push_back(s);
        break;

      case GidSlantedDown_TopLeft:
        s.p0 = base + gf::vec(0,          0);
        s.p1 = base + gf::vec(TileExtent,   TileLimit2);
        m_segments.push_back(s);
        break;
      case GidSlantedDown_TopRight:
        s.p0 = base + gf::vec(0,          TileLimit2);
        s.p1 = base + gf::vec(TileLimit,  TileLimit);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(TileLimit,  TileLimit);
        s.p1 = base + gf::vec(TileLimit,  TileExtent);
        m_segments.push_back(s);
        break;
      case GidSlantedDown_CenterRight:
        s.p0 = base + gf::vec(TileLimit,  0);
        s.p1 = base + gf::vec(TileExtent,   0);
        m_segments.push_back(s);
        break;
      case GidSlantedDown_CenterLeft:
        s.p0 = base + gf::vec(0,          TileLimit);
        s.p1 = base + gf::vec(0,          TileExtent);
        m_segments.push_back(s);
        break;
      case GidSlantedDown_BottomLeft:
        s.p0 = base + gf::vec(0,          0);
        s.p1 = base + gf::vec(TileExtent,   TileExtent2);
        m_segments.push_back(s);
        break;
      case GidSlantedDown_BottomRight:
        s.p0 = base + gf::vec(0,          TileExtent2);
        s.p1 = base + gf::vec(TileLimit,  TileLimit);
        m_segments.push_back(s);
        s.p0 = base + gf::vec(TileLimit,  TileLimit);
        s.p1 = base + gf::vec(TileExtent,   TileLimit);
        m_segments.push_back(s);
        break;

      case GidBlank:
      case GidBlank_Caution:
      case GidBlank_FinishHorizontal:
      case GidBlank_FinishVertical:
      case GidBlank_Pit:
      case GidBlank_StartUp:
      case GidBlank_StartDown:
      case GidBlank_StartLeft:
      case GidBlank_StartRight:
        // nothing
        break;
      default:
        gf::Log::error("Unknown gid: %i\n", gid);
        assert(false);
        break;
    }
  }

  void TilesetInfo::appendLimit(StageLimit limit) {
    gf::SegmentI s;

    switch (limit) {
      case StageLimit::BottomLeft:
        s.p0 = gf::vec(0, GroundExtent * TileExtent);
        s.p1 = s.p0 + gf::dirx(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::BottomCenter:
        s.p0 = gf::vec((GroundExtent2 - 1) * TileExtent, GroundExtent * TileExtent);
        s.p1 = s.p0 + gf::dirx(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::BottomRight:
        s.p0 = gf::vec(GroundExtent * TileExtent - 1, GroundExtent * TileExtent);
        s.p1 = s.p0 - gf::dirx(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::TopLeft:
        s.p0 = gf::vec(0, 0);
        s.p1 = s.p0 + gf::dirx(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::TopCenter:
        s.p0 = gf::vec((GroundExtent2 - 1) * TileExtent, 0);
        s.p1 = s.p0 + gf::dirx(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::TopRight:
        s.p0 = gf::vec(GroundExtent * TileExtent - 1, 0);
        s.p1 = s.p0 - gf::dirx(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::LeftBottom:
        s.p0 = gf::vec(0, GroundExtent * TileExtent - 1);
        s.p1 = s.p0 - gf::diry(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::LeftCenter:
        s.p0 = gf::vec(0, (GroundExtent2 - 1) * TileExtent);
        s.p1 = s.p0 + gf::diry(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::LeftTop:
        s.p0 = gf::vec(0, 0);
        s.p1 = s.p0 + gf::diry(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::RightBottom:
        s.p0 = gf::vec(GroundExtent * TileExtent, GroundExtent * TileExtent - 1);
        s.p1 = s.p0 - gf::diry(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::RightCenter:
        s.p0 = gf::vec(GroundExtent * TileExtent, (GroundExtent2 - 1) * TileExtent);
        s.p1 = s.p0 + gf::diry(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
      case StageLimit::RightTop:
        s.p0 = gf::vec(GroundExtent * TileExtent, 0);
        s.p1 = s.p0 + gf::diry(TileExtent + TileLimit);
        m_segments.push_back(s);
        break;
    }
  }

  gf::Polyline TilesetInfo::computeLine() const {
    auto lines = gf::buildLines(m_segments);
    assert(lines.size() == 1);
    return std::move(lines[0]);
  }

}


