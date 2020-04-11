#ifndef TA_TIMER_ENTITY_H
#define TA_TIMER_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>

namespace ta {
  class TimerModel;

  class TimerEntity : public gf::Entity {
  public:
    TimerEntity(gf::ResourceManager& resources, TimerModel& model);

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Font& m_font;
    TimerModel& m_model;
  };

}

#endif // TA_TIMER_ENTITY_H
