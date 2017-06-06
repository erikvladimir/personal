//
//  Deck.hpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <array>
#include <vector>
#include <deque>

#include "Card.hpp"

/**
 * Deck that allows actions such as initialise, reshuffle, push/pop cards and draw.
 */
class Deck
{
private:
    static const std::array<CardName, 13> m_cardNames;
    static const std::array<Suit, 4> m_suits;
    std::deque<Card> m_cards;
protected:
    std::string print() const;
public:
    Deck();
    void suffle();
    void pileCards(const std::vector<Card> &in_cards);
    Card pop();
    void push(Card &card);
    size_t getNumCards() const;
};


#endif /* Deck_hpp */
