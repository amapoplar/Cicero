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
     7, 0, 6, 0, 7, 0, 7, 0, 7,
     0, 6, 0, 0, 0, 0, 0, 6, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     1, 2, 3, 4, 5, 4, 3, 2, 1
    };
    Game::Game()
    {
        m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(2211, 2438), "Chinese Chess!");
        tBoard.loadFromFile("images/chessboard.png");
        sBoard.setTexture(tBoard);
        for (int i = 0; i < 90; i++)
        {
            if (board[i])
            {
                int name = (board[i] - 1) % 7;
                int redQ = (board[i] - 1) / 7;
                Chess newChess((ChessName)name, redQ);
                tChess.loadFromFile("images/chess.png");
                newChess.getSprite()->setTexture(tChess);
                newChess.getSprite()->setTextureRect(sf::IntRect(size * newChess.Tx, size * newChess.Ty, size, size));
                newChess.setPos(i%9, i/9);
                sChess.push_back(newChess);
            }

        }

    }

    void Game::Show() {
        sf::Sprite* _sprite = nullptr;
        while (m_Window->isOpen())
        {
            sf::Event event;
            
            while (m_Window ->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_Window->close();
            }

            //_sprite = Update(event,_sprite);
     

            m_Window->draw(this->sBoard);
            for (std::vector<Chess>::iterator it =sChess.begin();it!=sChess.end();it++)
            {
               m_Window->draw(*(it->getSprite()));
            }
            m_Window->display();
            m_Window->clear();
        }
    }

    sf::Sprite* Game::Update(sf::Event event, sf::Sprite* _sprite)
    {
        /*
        bool MoveQ = false;
        int chessPos;
        sf::Vector2i pos = sf::Mouse::getPosition(*m_Window);
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.key.code == sf::Mouse::Left)
            {
                for (std::vector<sf::Sprite>::iterator it = sChess.begin(); it != sChess.end(); it++)
                {

                    if (it->getGlobalBounds().contains(pos.x, pos.y))
                    {
                        MoveQ = true;
                        return &(*it);
                    }
                }
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.key.code == sf::Mouse::Left)
            {
                int posx = pos.x / size;
                int posy = pos.y / size;
                std::cout << posx << " " << posy << std::endl;
                if (MoveQ)
                {
                    _sprite->setPosition(sf::Vector2f(size * posx, size * posy));
                    return  nullptr;
                }
                MoveQ = false;
            }
        }


        */
        return nullptr;
    }
  
}

