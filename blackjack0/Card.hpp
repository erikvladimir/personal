//
//  Card.hpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#ifndef Card_hpp
#define Card_hpp

#include <iostream>

enum Suit {HEARTS, DIAMONDS, CLUBS, SPADES};

enum CardName {ACE = 1, C2 = 2, C3 = 3, C4 = 4, C5 = 5, C6 = 6, C7 = 7, C8 = 8, C9 = 9, C10 = 10, JACK = 11, QUEEN = 12, KING = 13};

/**
 * Card including data and drawing methods
 */
class Card
{
private:
    Suit m_suit;
    CardName m_name;
    bool m_visible;
    
public:
    Card (Suit, CardName);
    std::string print() const;
    uint16_t value() const;
    void setVisible(bool visible = true);
    void draw(uint y = 0, uint x = 0) const;
};

#endif /* Card_hpp */
