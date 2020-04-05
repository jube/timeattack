#ifndef COUNTDOWN_ENTITY_H
#define COUNTDOWN_ENTITY_H

#include <gf/Entity.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>

namespace ta {
  struct TimeAttack;

  class CountdownEntity : public gf::Entity {
  public:
    CountdownEntity(gf::ResourceManager& resources);

    void reset();
    bool isFinished() const;

    void update(gf::Time time) override;
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;

  private:
    gf::Font& m_font;
    gf::Time m_elapsed;
  };

}

#endif // COUNTDOWN_ENTITY_H
