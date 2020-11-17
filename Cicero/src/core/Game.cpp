#include "cicpch.h"
#include "Game.h"
#include<map>
#include"Chess.h"
namespace Cicero {
    int board[90] = {
     8, 9,10,11,12,11,10, 9, 8,
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     0,13, 0, 0, 0, 0, 0,13, 0,
    14, 0,14, 0,14, 0,14, 0,14,
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     7, 0, 7, 0, 7, 0, 7, 0, 7,
     0, 6, 0, 0, 0, 0, 0, 6, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     1, 2, 3, 4, 5, 4, 3, 2, 1
    };
    const double s = 0.4;
    const int WIDTH = 2211*s;
    const int HEIGHT = 2438 * s;
    Game::Game()
        :sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Chinese Chess!")
    {
        tBoard.loadFromFile("images/chessboard.png");
        sBoard.setTexture(tBoard);
        sBoard.setScale(sf::Vector2f(s, s));
        for (int i = 0; i < 90; i++)
        {
            if (board[i])
            {
                Chess* newChess = new Chess((ChessName)((board[i]-1)%7),(MoveWho)((board[i] - 1)/7), s);
                newChess->setPos(i%9, i/9);
                Chesses.push_back(newChess);
            }
        }
        size *= s;
    }

    void Game::Show()
    {
        while (true)
        {
            sf::Event event;
            while (this->pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    this->close();
            }
            // Clear screen
            // Draw the sprite
            Update(event);
            this->draw(sBoard);
            int i = 0;
            for (std::vector<Chess*>::iterator it = Chesses.begin(); it!=Chesses.end(); it++)
            {
                this->draw(*((*it)->getSprite()));
                i++;
            }
            //std::cout << i << std::endl;
            this->display();
            
        }
    }

    void Game::Update(sf::Event event)
    {
        newpos = sf::Mouse::getPosition(*this);
        //std::string msg = who ? "black now" : "red now";
        //std::cout<<msg <<std::endl;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.key.code==sf::Mouse::Left)
            {
                for (std::vector<Chess*>::iterator it = Chesses.begin(); it != Chesses.end(); it++)
                {
                    sf::Sprite* sp = (*it)->getSprite();
                    if (sp->getGlobalBounds().contains(sf::Vector2f((double)newpos.x, (double)newpos.y)))
                    {
                        movingChess = (*it);
                        movingChess->setPos(1000, 1000);
                        oldpos = sf::Vector2i(newpos.x / size, newpos.y / size);
                    }   
                }
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.key.code == sf::Mouse::Left)
            {
                newpos = sf::Mouse::getPosition(*this);
                
                if (leaglQ())
                {
                    movingChess->setPos(newpos.x / size, newpos.y / size);
                    who = (MoveWho)(!who);
                    this->clear();
                    //movingChess = nullptr;
                }
                else{
                    movingChess->setPos(oldpos.x, oldpos.y);
                    this->clear();
                    //movingChess = nullptr;
                }
            }
        }

    }

    bool Game::leaglQ()
    {
        if ((movingChess->redQ)==who)
        {
            for (std::vector<Chess*>::iterator it = Chesses.begin(); it != Chesses.end(); it++)
            {
                std::cout << (*it)->x << " " << (*it)->y << std::endl;
                std::cout << (*it)->redQ << " " << (*it)->name << std::endl;
                std::cout << (newpos.x / size) << " " << (newpos.y / size) << std::endl;
                std::cout << ((*it)->x == (newpos.x / size)) <<" " << ((*it)->y == (newpos.y / size) )<< std::endl;
                std::cout << "\n";
                if ((*it)->x==(newpos.x/size)&&(*it)->y==(newpos.y/size))
                {
                    Chesses.erase(it);
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }
}



