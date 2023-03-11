#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <sstream>
#include <time.h>


//verify if cursor is over button
bool iscursorHover(sf::FloatRect cookie, sf::Vector2f mp)
{
    if (cookie.contains(mp))
    {
        return true;
    }
    return false;
}


int main()
{
    int nr=1,multiply=1,spiridusi=0;

    //define clock
    sf::Clock clock;
    sf::Time micro = sf::microseconds( 10000 );
    sf::Time milli = sf::milliseconds( 10 );
    sf::Time second = sf::seconds( 0.01f );
    srand(time(0));

    sf::RenderWindow window;
    window.create(sf::VideoMode(1000, 800),"Cookieclicker");

    //define font
    sf::Font font;
    font.loadFromFile("ARIAL.TTF");

    //define text
    sf::Text text;
    text.setCharacterSize(25);
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setPosition(700,700);
    sf::Text text1;
    text1.setCharacterSize(25);
    text1.setFont(font);
    text1.setFillColor(sf::Color::Black);
    text1.setPosition(600,200);
    text1.setString("50 prajiturele pentru \n o prajiturica in plus \n pe click");
    sf::Text text2;
    text2.setCharacterSize(25);
    text2.setFont(font);
    text2.setFillColor(sf::Color::Black);
    text2.setPosition(600,500);
    text2.setString("200 prajiturele pentru \n un spiridus ce ofera \n o prajitura la fiecare 3 secunde");

    //create button_cookie
    sf::Texture texture;
    if(!texture.loadFromFile("button1.png"))
    {
        return 1;
    }
    sf::Sprite cookie;
    cookie.setPosition(sf::Vector2f(50, 50));
    cookie.setTexture(texture);

    //create button_cursor
    sf::Texture texture1;
    if(!texture1.loadFromFile("cursor.jpg"))
    {
        return 1;
    }
    sf::Sprite cursor;
    cursor.setPosition(sf::Vector2f(600, 50));
    cursor.setScale(0.1,0.1);
    cursor.setTexture(texture1);

    //create button_spiridus
    sf::Texture texture2;
    if(!texture2.loadFromFile("spiridus.jpg"))
    {
        return 1;
    }
    sf::Sprite spiridus;
    spiridus.setPosition(sf::Vector2f(600, 300));
    spiridus.setScale(0.4,0.4);
    spiridus.setTexture(texture2);

    //cursor coordinates

    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;

    //the app

    while(window.isOpen())
    {
        sf::Event event;
        sf::Time elapsed = clock.getElapsedTime( );

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(iscursorHover(cookie.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            {
                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {
                    nr+=multiply;
                }
            }
            if(iscursorHover(cursor.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            {
                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {
                    if(nr>50)
                    {
                        multiply++;
                        nr-=50;
                    }
                }
            }
            if(iscursorHover(spiridus.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            {
                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {
                    if(nr>200)
                    {
                        spiridusi++;
                        nr-=200;
                    }
                }
            }




        }
        float t=int(elapsed.asSeconds())+0.0004;

        if(spiridusi!=0 && int(elapsed.asSeconds())%3==0 && elapsed.asSeconds()<t)
        {
            nr=nr+spiridusi;
        }
        window.clear(sf::Color::White);

        std::stringstream ss;
        ss << "Prajiturele: "<<nr<<"\n"<<"Timp: "<<int(elapsed.asSeconds( ));
        text.setString(ss.str());
        window.draw(text);
        window.draw(text1);
        window.draw(text2);
        window.draw(spiridus);
        window.draw(cookie);
        window.draw(cursor);
        window.display();

    }

    return 0;
}
