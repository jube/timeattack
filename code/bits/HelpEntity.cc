#include "HelpEntity.h"

#include <gf/Color.h>
#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Text.h>

namespace ta {

  namespace {

    constexpr auto HelpText =
      "* The car follows the cursor when you hold the left button.\n"
      "* If you hit a border, you start the stage again.\n"
      "* Finish all the stages before the end of the time.\n"
      "* Additional keys: F for fullscreen, Space to pause, Escape to quit."
    ;
  }

  HelpEntity::HelpEntity(gf::ResourceManager& resources)
  : m_font(resources.getFont("TovariSans.otf"))
  {
  }

  void HelpEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    unsigned characterSize = coords.getRelativeCharacterSize(0.07f);
    float paragraphWidth = coords.getRelativeSize({ 0.5f, 0.0f }).width;
    auto position = coords.getRelativePoint({ 0.5f, 0.4f });

    gf::Text help(HelpText, m_font, characterSize);
    help.setColor(gf::Color::Black);
    help.setParagraphWidth(paragraphWidth);
    help.setAlignment(gf::Alignment::Left);
    help.setLineSpacing(1.2f);
    help.setPosition(position);
    help.setAnchor(gf::Anchor::Center);
    target.draw(help, states);
  }


}
