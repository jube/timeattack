#ifndef TA_STAGE_LIMIT_H
#define TA_STAGE_LIMIT_H

#include <string>

#include <gf/Vector.h>

namespace ta {

  enum class StageLimit {
    BottomLeft,
    BottomCenter,
    BottomRight,
    TopLeft,
    TopCenter,
    TopRight,
    LeftBottom,
    LeftCenter,
    LeftTop,
    RightBottom,
    RightCenter,
    RightTop,
  };

  StageLimit getStageLimitFromString(const std::string& str);

  gf::Vector2i getInitialPosition(StageLimit limit);
  float getInitialAngle(StageLimit limit);

  gf::Vector2i getTarget(StageLimit limit);

}

#endif // TA_STAGE_LIMIT_H
