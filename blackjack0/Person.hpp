//
//  Person.hpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#ifndef Person_hpp
#define Person_hpp

#include <vector>

#include "Card.hpp"

/**
 * Represents the Dealer or the Player and all associated data 
 * (cards, points) and allows taking actions (take/return cards, draw).
 */
class Person
{
private:
    std::vector<Card> m_cards;
    std::string m_name;
    bool m_showPoints;

public:
    static std::vector<int> computePoints(std::vector<Card> cards);
    
    Person(std::string name = "person", bool showPoints = true);
    
    void giveCard(Card card, bool visible = true);
    std::vector<Card> collectCards();
    std::vector<int> getPoints() const;
    int getMaxPoints() const;
    size_t getNumPoints() const;
    
    void draw(uint y = 0, uint x = 0);
    void showPoints(bool show = true);
    bool getShowPoints() const;
    void showCards();
    size_t numCards() const;

};


#endif /* Person_hpp */
