/**
 * @file card_menu.h
 * @ingroup GameMenusCards
 */
//! \todo Document this file.

#ifndef COCKATRICE_CARD_MENU_H
#define COCKATRICE_CARD_MENU_H

#include <QList>
#include <QMenu>
#include <QPair>
#include <QPointer>
#include <QString>
#include <libcockatrice/utility/card_ref.h>
#include <qtmetamacros.h>

class CardItem;
class PlayerGraphicsItem;
class PlayerLogic;
class QAction;
struct CardRef;

class CardMenu : public QMenu
{
    Q_OBJECT

signals:
    void cardInfoRequested(const CardRef &cardRef);

public:
    explicit CardMenu(PlayerGraphicsItem *player, CardItem *card, bool shortcutsActive);
    void removePlayer(PlayerLogic *playerToRemove);
    void createTableMenu(bool canModifyCard);
    void createStackMenu(bool canModifyCard);
    void createGraveyardOrExileMenu(bool canModifyCard);
    void createHandOrCustomZoneMenu(bool canModifyCard);
    void createZonelessMenu(bool canModifyCard);

    QMenu *mCardCounters;

    QAction *aPlay, *aPlayFacedown;
    QAction *aRevealToAll;
    QAction *aHide;
    QAction *aClone;
    QAction *aSelectAll, *aSelectRow, *aSelectColumn;
    QAction *aDrawArrow;
    QAction *aTap, *aDoesntUntap;
    QAction *aFlip, *aPeek;
    QAction *aAttach, *aUnattach;
    QAction *aSetAnnotation;
    QAction *aReduceLifeByPower;

    QList<QAction *> aAddCounter, aSetCounter, aRemoveCounter;

private:
    PlayerGraphicsItem *player;
    // QPointer so a card deleted while the popup is open (opponent moves it to
    // another zone -> deleteLater) nulls out instead of dangling. All trigger-time
    // uses go through PlayerActions null checks or `if (card)`, restoring the
    // old activeCard-cleared-in-prepareDelete() no-op behavior.
    QPointer<CardItem> card;
    QList<QPair<QString, int>> playersInfo;
    bool shortcutsActive;

    void addRelatedCardActions();
    void attachCard();
    void drawArrow();
    void retranslateUi();
    void initContextualPlayersMenu(QMenu *menu, QAction *allPlayersAction);
    void setShortcutsActive();
    void addRelatedCardView();
};

#endif // COCKATRICE_CARD_MENU_H
