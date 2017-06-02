//
//  VisualGame.hpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#ifndef VisualGame_hpp
#define VisualGame_hpp

#include <stdio.h>

#include "Game.hpp"
#include "Person.hpp"

/**
 * This class contains all the code for the visual output.
 * The logic is still in parent class Game.
 */
class VisualGame : public Game
{

private:
    void drawScores() const;
    void drawRoundMenu() const;
    void draw(uint y, uint x, Person person) const;
    static VisualGame * single_instance;
    VisualGame();
    
protected:
    void showMessageBox(uint y, uint x, uint lines, uint columns, std::string message);
    virtual void draw();

public:
    virtual ~VisualGame();
    
    static void showText(uint y, uint x, uint color, const char* format, ...);
    static void DrawRectangle(uint y, uint x, uint lines, uint columns);
    
    // Singleton Design Pattern
    static VisualGame& getInstance()
    {
        static VisualGame    instance;
        return instance;
    }
    VisualGame(VisualGame const&) = delete;
    void operator=(VisualGame const&) = delete;
};


#endif /* VisualGame_hpp */
