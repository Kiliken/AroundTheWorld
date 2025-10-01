#include "utils.cpp"

int main(){
    

    // WINDOW
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Around The World");
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    // MAIN LOOP
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        // win lose condition
        

        // RENDERING
        window.clear();
        window.display();
    }
}