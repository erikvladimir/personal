//
//  Person.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#include "VisualGame.hpp"
#include "Person.hpp"

template<typename T> std::string vectorToString(std::vector<T> elements)
{
    std::string result;
    for (auto e : elements)
    {
        result = result + ((result.size()>0)?" or ":"") + std::to_string(e);
    }
    return result;
}

Person::Person(std::string name, bool showPoints):
    m_name(name),
    m_showPoints(showPoints)
{
}

void Person::giveCard(Card card, bool visible)
{
    card.setVisible(visible);
    m_cards.push_back(card);
}

std::vector<Card> Person::collectCards()
{
    std::vector<Card> collected_cards;
    std::copy(m_cards.begin(), m_cards.end(), std::back_inserter(collected_cards));
    m_cards.clear();
    return collected_cards;
}

std::vector<int> Person::computePoints(std::vector<Card> cards)
{
    std::vector<int> results= {0};
    
    // add non-ACEs
    for (auto card : cards)
    {
        int value = card.value();
        
        if (value == CardName::ACE) continue;
        
        results[0] += value;
    }
    
    // add ACEs, first as ones, and if possible as 11s
    for (auto card : cards)
    {
        for (auto &res : results)
        {
            if (card.value() == CardName::ACE)
            {
                // if 11 does not overflow
                if (res <= 10)
                {
                    results.push_back(res + 11);
                }
                res += 1 ;
            }
        }
    }
    
    return results;

}

std::vector<int> Person::getPoints() const
{
    return Person::computePoints(m_cards);
}

int Person::getMaxPoints() const
{
    auto points = getPoints();
    if (points.size() == 0) return 0;
    return *std::max_element(points.begin(), points.end());
}

size_t Person::getNumPoints() const
{
    auto points = getPoints();
    return points.size();
}

void Person:: draw(uint y, uint x)
{
    // draw name and points
    constexpr int points_color = 7;
    VisualGame::showText(y+1, x, 0, m_name.c_str());
    if (m_showPoints)
    {
        VisualGame::showText(y+2, x, points_color, " %s pts.", vectorToString<int>(getPoints()).c_str());
    }
    else
    {
        VisualGame::showText(y+2, x, points_color, " ? pts.");
    }
    
    // draw cards
    constexpr uint card_offset = 10u;
    uint offset = 16;
    for (auto card : m_cards )
    {
        card.draw(y, x + offset);
        offset += card_offset;
    }
}

void Person::showPoints(bool show)
{
    m_showPoints = show;
}

void Person::showCards()
{
    for (auto &card : m_cards)
    {
        card.setVisible(true);
    }
}

size_t Person::numCards() const
{
    return m_cards.size();
}

