//
//  Deck.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//


#include <cstdlib>
#include <array>

#include <time.h>
#include <assert.h>
#include <stdlib.h>

#include "Deck.hpp"

const std::array<CardName, 13> Deck::m_cardNames = {ACE, C2, C3, C4, C5, C6, C7, C8, C9, C10, JACK, QUEEN, KING};
const std::array<Suit, 4> Deck::m_suits = {HEARTS, DIAMONDS, CLUBS, SPADES};

std::string Deck::print() const
{
    std::string r;
    for (auto card : m_cards){
        r += card.print() + std::string(" , ");
    }
    r += std::string("\n");
    return r;
}

void Deck::pileCards(const std::vector<Card> &in_cards)
{
    //m_cards.emplace_back(in_cards.begin(), 1);//in_cards.size());
    std::copy(in_cards.begin(), in_cards.end(), m_cards.end());
}

Deck::Deck()
{
    for (auto s : m_suits)
    {
        for (auto n : m_cardNames)
        {
            Card card (s, n);
            m_cards.push_back(card);
        }
    }
    assert( 52 == m_cards.size());
}

void Deck::suffle()
{
    // Fisher–Yates shuffle agorithm
    std::srand (time(0));
    const size_t n = m_cards.size();
    for (size_t i = n-1; i >= 1; i--)
    {
        size_t j = size_t(std::rand() % i );
        std::cout << j << " ";
        std::swap(m_cards[i], m_cards[j]);
    }
}

Card Deck::pop()
{
    Card & card = m_cards.front();
    m_cards.pop_front();
    return card;
}

void Deck::push(Card &card)
{
    m_cards.push_back(card);
}
