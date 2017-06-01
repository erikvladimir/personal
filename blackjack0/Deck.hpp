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

class Deck
{
private:
    static const std::array<CardName, 13> m_cardNames;
    static const std::array<Suit, 4> m_suits;
    std::deque<Card> m_cards;
public:
    Deck();
    void suffle();
    std::string print() const;
    void pileCards(const std::vector<Card> &in_cards);
    Card pop();
    void push(Card &card);
};


#endif /* Deck_hpp */
