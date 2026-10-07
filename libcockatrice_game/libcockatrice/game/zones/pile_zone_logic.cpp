#include "pile_zone_logic.h"

#include "../board/card_list.h"
#include "../board/card_state.h"

class PlayerLogic;
class QObject;

PileZoneLogic::PileZoneLogic(PlayerLogic *_player,
                             const QString &_name,
                             bool _hasCardAttr,
                             bool _isShufflable,
                             bool _contentsKnown,
                             QObject *parent)
    : CardZoneLogic(_player, _name, _hasCardAttr, _isShufflable, _contentsKnown, parent)
{
}

void PileZoneLogic::addCardImpl(CardState *card, int x, int /*y*/)
{
    connect(card, &CardState::cardPixmapUpdated, this, &PileZoneLogic::callUpdate);
    // if x is negative set it to add at end
    if (x < 0 || x >= cards.size()) {
        x = cards.size();
    }
    cards.insert(x, card);
    // Keep cards hidden and at the pile origin in the logic path as well: custom zones created in
    // PlayerLogic::setupZones have no PileZone graphics item, so PileZone::onCardAdded never runs for them.
    // For piles with a view this is a harmless duplicate of the view's hide.
    card->setPos(0, 0);
    card->setVisible(false);
    if (!contentsKnown()) {
        card->setCardRef({});
        card->setId(-1);
        // If we obscure a previously revealed card, its name has to be forgotten
        if (cards.size() > x + 1) {
            cards.at(x + 1)->setCardRef({});
        }
    }
    card->resetState(false);
}