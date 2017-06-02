//
//  UnitTests.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 02/06/2017.
//

#include <stdio.h>
#include <assert.h>

#include "VisualGame.hpp"

#define EXPECT_EQ(A,B)    if ((A)!=(B)) { \
                            std::cout<<"Failure: "<<#A<<"("<<A<<") != "<<#B<<" ("<<B<<")"; \
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

void RunTests()
{
    std::cout<<"[>>>START] "<<__FUNCTION__<<std::endl;
    
    TEST_CHECK_WINNER();
    
    std::cout<<"[<<<END]   "<<__FUNCTION__<<std::endl;

}
