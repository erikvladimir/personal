//
//  UnitTests.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 02/06/2017.
//

#include <stdio.h>
#include <assert.h>
#include <algorithm>

#include "VisualGame.hpp"

#define EXPECT_EQ(A,B)    if ((A)!=(B)) { \
                            std::cout<<"Failure: "<<__FUNCTION__<<":"<<__LINE__<<" "<<#A<<"("<<A<<") != "<<#B<<" ("<<B<<")"; \
                            assert(false); \
                          }

void TEST_CHECK_WINNER()
{
    EXPECT_EQ(Game::RoundWinner::DEALER, Game::checkWinner(22,22));
    EXPECT_EQ(Game::RoundWinner::TIE,    Game::checkWinner(19,19));
    EXPECT_EQ(Game::RoundWinner::TIE,    Game::checkWinner(21,21));
    EXPECT_EQ(Game::RoundWinner::DEALER, Game::checkWinner(22,19));
    EXPECT_EQ(Game::RoundWinner::DEALER, Game::checkWinner(20,21));
    EXPECT_EQ(Game::RoundWinner::PLAYER, Game::checkWinner(20,22));
    EXPECT_EQ(Game::RoundWinner::PLAYER, Game::checkWinner(20,18));
    EXPECT_EQ(Game::RoundWinner::PLAYER, Game::checkWinner(21,20));
}

void TEST_COMPUTE_POINTS()
{
    // we will mostly check the max value to simplify the process
    auto getMax = [](std::vector<int> v) -> int { return *std::max_element(v.begin(), v.end()); };
    // min value can also be used to check some specific cases
    auto getMin = [](std::vector<int> v) -> int { return *std::min_element(v.begin(), v.end()); };
    
    // empty case
    EXPECT_EQ(0, getMax(Person::computePoints(std::vector<Card>{ } )));
    
    // one card
    EXPECT_EQ(2, getMax(Person::computePoints(std::vector<Card>{ {HEARTS, C2} } )));
    
    // two cards
    EXPECT_EQ(11, getMax(Person::computePoints(std::vector<Card>{ {HEARTS, C2}, {DIAMONDS, C9} } )));
    EXPECT_EQ(18, getMax(Person::computePoints(std::vector<Card>{ {HEARTS, C9}, {DIAMONDS, C9} } )));
    EXPECT_EQ(12, getMax(Person::computePoints(std::vector<Card>{ {HEARTS, C2}, {DIAMONDS, KING} } )));
    EXPECT_EQ(20, getMax(Person::computePoints(std::vector<Card>{ {HEARTS, JACK}, {DIAMONDS, KING} } )));
    
    // ACE as 11
    EXPECT_EQ(13, getMax(Person::computePoints(std::vector<Card>{ {HEARTS, C2}, {SPADES, ACE} } )));
    
    // ACE as 1
    EXPECT_EQ(17, getMax(Person::computePoints(std::vector<Card>{ {HEARTS, C8}, {HEARTS, C8}, {SPADES, ACE} } )));
    
    // Two ACEs
    auto hand1 = Person::computePoints(std::vector<Card>{ {HEARTS, ACE}, {SPADES, ACE} });
    EXPECT_EQ(2u, hand1.size());
    EXPECT_EQ(2, getMin(hand1));
    EXPECT_EQ(12, getMax(hand1));
    
    // Three ACEs
    auto hand2 = Person::computePoints(std::vector<Card>{ {HEARTS, ACE}, {SPADES, ACE}, {DIAMONDS, ACE} });
    EXPECT_EQ(2u, hand2.size());
    EXPECT_EQ(3, getMin(hand2));
    EXPECT_EQ(13, getMax(hand2));

    // Two ACEs and more cards
    auto hand3 = Person::computePoints(std::vector<Card>{ {HEARTS, ACE}, {HEARTS, C2}, {DIAMONDS, C2}, {SPADES, ACE} });
    EXPECT_EQ(2u, hand3.size());
    EXPECT_EQ(6, getMin(hand3));
    EXPECT_EQ(16, getMax(hand3));
}


void RunTests()
{
    std::cout<<"[>>>START] "<<__FUNCTION__<<std::endl;
    
    TEST_CHECK_WINNER();
    
    TEST_COMPUTE_POINTS();
    
    std::cout<<"[<<<END]   "<<__FUNCTION__<<std::endl;

}
