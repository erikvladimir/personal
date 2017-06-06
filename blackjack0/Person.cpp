//
//  Person.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#include <algorithm>
#include <set>

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

/**
 * This function returns all valid sums of points from a given hand.
 * In case of ACEs, it will return more than one possible result.
 * Note: this implementation a bit complex, if we we weren't printing all possible sums we chould simplify significantly the counting process. Only the maximum vaue of the results is relevant for the game logic. However showing all possible sums is a visual aid for the user.
 */
std::vector<int> Person::computePoints(std::vector<Card> cards)
{
    std::vector<int> results {0};  // to store all possible valid sums (<=21)
    std::set<int> values {0};  // to avoid duplicates
    
    // add base values (ACEs are counted as 1)
    for (auto card : cards)
    {
        results[0] += card.value();;
    }
    values.insert(results[0]);
    
    // add ACEs, first as ones, and if possible as 11s
    for (auto card : cards)
    {
        if (card.value() == CardName::ACE)
        {
            const size_t num = results.size();
            for (size_t i=0; i<num; i++)
            {
                // only add 10 since 1 was already added on previous loop
                int new_result = results[i] + 10;
                
                // if 11 does not overflow
                if (new_result <= 21 &&
                    values.find(new_result) == values.end())  // check value was not repeated
                {
                    values.insert(new_result);
                    results.push_back(new_result);
                }
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
    constexpr uint max_cards_visual = 6;
    uint num_printed = 0;
    for (auto card : m_cards )
    {
        card.draw(y, x + offset);
        offset += card_offset;

        //avoid printing too many cards
        num_printed++;
        if(num_printed >= max_cards_visual)
        {
            // print 3 points to indicate there are more cards in the hand
            // the user will still have the number of points as a reference
            VisualGame::showText(y+2, x+offset-3, 0, "...");
            break;
        }
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

