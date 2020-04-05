#include "CountdownEntity.h"

#include <cassert>

#include <gf/Color.h>
#include <gf/RenderTarget.h>
#include <gf/Text.h>

#include "Settings.h"

namespace ta {

  namespace {
    constexpr gf::Time CountdownWarmup = gf::milliseconds(1000);
    constexpr gf::Time CountdownEnd = gf::milliseconds(4000);
  }

  CountdownEntity::CountdownEntity(gf::ResourceManager& resources)
  : m_font(resources.getFont("TovariSans.otf"))
  , m_elapsed(gf::Time::zero())
  {
  }

  void CountdownEntity::reset() {
    m_elapsed = gf::Time::zero();
  }

  bool CountdownEntity::isFinished() const {
    return m_elapsed > CountdownEnd;
  }

  void CountdownEntity::update(gf::Time time) {
    m_elapsed += time;
  }

  void CountdownEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    if (m_elapsed <= CountdownWarmup) {
      return;
    }

    gf::Time remaining = CountdownEnd - m_elapsed;

    int time = remaining.asMilliseconds() / 1000 + 1;
    assert(1 <= time && time <= 3);
    float scale = 0.5f + 0.5f * (time - remaining.asSeconds());

    unsigned characterSize = 128;

    gf::Text text(std::to_string(time), m_font, characterSize);
    text.setColor(gf::Color::Yellow);
    text.setOutlineColor(gf::Color::Black);
    text.setOutlineThickness(characterSize * 0.05f);
    text.setPosition(ViewSize / 2);
    text.setAnchor(gf::Anchor::Center);
    text.setScale(scale * 4);
    target.draw(text, states);
  }

}

