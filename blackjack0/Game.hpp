//
//  Game.hpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#ifndef Game_hpp
#define Game_hpp

#include "Deck.hpp"
#include "Person.hpp"

/**
 * Contains all necessary data (Players, Deck, Scores),
 * and runs the game to a defined logic (using a simple state machine)
 * This is an abstract class, and the visual part should be implemented \
 * in a derived one (such as VisualGame).
 */
class Game
{
private:
    
    void initialiseRound();
    void dealerPlays();
    void checkGame();
    virtual void draw() = 0;
    
protected:
    
    enum GameState {PLAY, DEALER_HAND, WAIT};
    
    struct GameScores
    {
        uint player;
        uint dealer;
        uint ties;
    } m_scores;
    
    GameState m_state;
    Deck m_deck;
    Person m_player;
    Person m_dealer;
    size_t m_roundCount;
    std::string m_status_msg;
    
public:
    enum RoundWinner {PLAYER, DEALER, TIE};
    static RoundWinner checkWinner(int points_player, int points_dealer);
    
    Game();
    virtual ~Game() {}
    void gameLoop();
};

#endif /* Game_hpp */
