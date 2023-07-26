#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// class Player{
// private:


// public:


// };

int main()                //main function
{
    RenderWindow window(sf::VideoMode(600, 600), "Checkers", Style::Close | Style::Titlebar);  //create window with size 600x600, title TicTacToe, and close and titlebar buttons on window 
    window.setFramerateLimit(60);   //set framerate limit to 60

    Texture red;        //create texture

    if(!red.loadFromFile("red.png")) //if texture is not loaded
    {
        cout << "Error loading texture" << endl; //print error message
    }
    
    red.setSmooth(true); //set texture to smooth


    Sprite r;          //create sprite
    
    r.setTexture(red); //set texture to sprite
    
    r.setScale(0.05, 0.05); //set scale of sprite

    while (window.isOpen()) //while window is open
    {
        Event event;        //create event
        while (window.pollEvent(event)) //while window is polling for event
        {
			switch (event.type) //switch statement for event type
			{
//                 case Event::MouseButtonReleased:


//                     if(event.mouseButton.button == Mouse::Left)
//                     {
//                         
//                     }
//                     break;



                case Event::KeyPressed: //if key is pressed
                    if(event.key.code == Keyboard::Escape) //if key is escape
                    {
                        window.close(); //close window
                    }
                    break; //break

			        case Event::Closed: //if window is closed
                    window.close();     //close window
                    break;                  //break

			}

        }
        window.clear(Color::White); //clear window with white color
        window.draw(r);        //draw sprite
        window.display();           //display window
    }

    return 0;                   
} 