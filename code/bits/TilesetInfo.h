#ifndef TA_TILESET_INFO_H
#define TA_TILESET_INFO_H

#include <vector>

#include <gf/GeometryTypes.h>
#include <gf/Polyline.h>
#include <gf/Vector.h>

#include "StageLimit.h"

namespace ta {

  class TilesetInfo {
  public:
    void clear();
    void append(gf::Vector2i base, int gid);
    void appendLimit(StageLimit limit);
    gf::Polyline computeLine() const;
  private:
    std::vector<gf::SegmentI> m_segments;
  };

}


#endif // TA_TILESET_INFO_H
