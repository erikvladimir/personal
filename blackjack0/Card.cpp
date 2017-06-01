//
//  Card.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#include "Card.hpp"

#include <unordered_map>
#include <assert.h>

#include <curses.h>

static std::unordered_map<int, std::string> suit_string = {
    {HEARTS, "\u2665"}, {DIAMONDS, "\u2666"},
    {CLUBS, "\u2663"}, {SPADES, "\u2660"} };
static std::unordered_map<int, std::string> name_string = {
    {ACE, "\u2660"}, {JACK, "\u2605"},
    {QUEEN, "\u2655"}, {KING, "\u2654"} };

Card::Card (Suit suit, CardName name):
    m_suit(suit),
    m_name(name),
    m_visible(true)
{}

uint16_t Card::value() const
{
    if (m_name >= CardName::JACK && m_name <= CardName::KING)
        return CardName::C10;
    return uint16_t(m_name);
}

std::string Card::print() const
{

    std::string r;
    
    if (!m_visible) return std::string("[?,?]");
    
    r = std::string("[");
    if (name_string.find(m_name) != name_string.end())
        r = r + name_string[m_name];
    else
        r = r + std::to_string(m_name);
    r = r + std::string(",") + suit_string[m_suit] + std::string("]");
    return r;
}

void Card::setVisible(bool visible)
{
    m_visible = visible;
}

void Card::draw(uint y, uint x) const
{
    int color_pair = 10;
    if (m_visible && (m_suit == HEARTS || m_suit == DIAMONDS))
        color_pair = 11;
    
    constexpr uint columns = 7;
    constexpr uint lines = 5;
    attron(COLOR_PAIR(m_visible?color_pair:4));
    for (uint i=0; i<lines; i++)
    {
        move(y+i, x);
        for (uint i=0; i<columns; i++)
        {
            printw(m_visible?" ":"\u28A7");
        }
    }
    attroff(COLOR_PAIR(m_visible?color_pair:4));
    
    if (!m_visible) return;
    
    attron(COLOR_PAIR(color_pair));
    move(y, x+5);
    printw(suit_string[m_suit].c_str());
    
    move(y+2, x+3);
    std::string r;
    if (name_string.find(m_name) != name_string.end())
        r = name_string[m_name];
    else
        r = std::to_string(m_name);
    printw(r.c_str());
    
    attroff(COLOR_PAIR(color_pair));
}
