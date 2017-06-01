//
//  Person.hpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//  Copyright © 2017 Erik V. Ortega. All rights reserved.
//

#ifndef Person_hpp
#define Person_hpp

#include <vector>

#include "Card.hpp"

class Person
{
private:
    std::vector<Card> m_cards;
    std::string m_name;
    bool m_showPoints;
public:
    Person(std::string name, bool showPoints = true);
    
    void giveCard(Card card, bool visible = true);
    std::vector<Card> collectCards();
    std::vector<int> getPoints();
    int getMaxPoints();
    
    void draw(uint y = 0, uint x = 0);
    void showPoints(bool show = true);
    void showCards();
    size_t numCards() const;
};


class Player : public Person
{
public:
    Player(std::string name);
};

#endif /* Person_hpp */
