#include "CreditEntity.h"

#include <gf/Color.h>
#include <gf/Coordinates.h>
#include <gf/RenderTarget.h>
#include <gf/Text.h>

namespace ta {

  namespace {

    constexpr auto CreditText =
      "Coded by Julien Bernard for his daughter Abbygaëlle during the 2020 lockdown for the 'Confinement' game jam.\n"
      "Graphics by Kenney (kenney.nl)"
    ;
  }

  CreditEntity::CreditEntity(gf::ResourceManager& resources)
  : m_font(resources.getFont("TovariSans.otf"))
  {
  }

  void CreditEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
    gf::Coordinates coords(target);

    unsigned characterSize = coords.getRelativeCharacterSize(0.07f);
    float paragraphWidth = coords.getRelativeSize({ 0.6f, 0.0f }).width;
    auto position = coords.getRelativePoint({ 0.5f, 0.4f });

    gf::Text help(CreditText, m_font, characterSize);
    help.setColor(gf::Color::Black);
    help.setParagraphWidth(paragraphWidth);
    help.setAlignment(gf::Alignment::Left);
    help.setLineSpacing(1.2f);
    help.setPosition(position);
    help.setAnchor(gf::Anchor::Center);
    target.draw(help, states);
  }


}
