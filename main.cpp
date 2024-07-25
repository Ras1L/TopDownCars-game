#include "app.hpp"

int main(){

    try 
    {
        Application app;
        app.run();
    } 
    catch (std::exception& e)
    {
        printf("\nEXCEPTION: ", e.what(), "%c \n", '\n');
    }

    // sf::RenderWindow window(sf::VideoMode(640, 480), "SFML APP");

    // sf::CircleShape shape;
    // shape.setRadius(40.f);
    // shape.setPosition(100.f, 100.f);
    // shape.setFillColor(sf::Color::Yellow);

    // while (window.isOpen()){
    //     sf::Event event;
    //     while (window.pollEvent(event)){
    //         if (event.type == sf::Event::Closed){
    //             window.close();
    //         }
    //     }

    //     window.clear();
    //     window.draw(shape);
    //     window.display();
    // }

    return 0;
}