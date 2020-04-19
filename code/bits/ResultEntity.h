#ifndef TA_RESULT_ENTITY_H
#define TA_RESULT_ENTITY_H

#include <gf/Entity.h>
#include <gf/ResourceManager.h>

namespace ta {

  struct TimeAttackData;
  struct TimeAttackState;

  class ResultEntity : public gf::Entity {
  public:
    ResultEntity(gf::ResourceManager& resources, const TimeAttackData& data, const TimeAttackState& state);

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Font& m_font;
    const TimeAttackData& m_data;
    const TimeAttackState& m_state;
  };
}


#endif // TA_RESULT_ENTITY_H
