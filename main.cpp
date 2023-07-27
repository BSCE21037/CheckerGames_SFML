#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

// class Player{
// private:


// public:


// };

int size = 56; //size of board
Sprite f[32]; //sprite array
int board[8][8] = {-1,-2,-3,-4,-5,-3,-2,-1,
                    -6,-6,-6,-6,-6,-6,-6,-6
                    ,0,0,0,0,0,0,0,0
                    ,0,0,0,0,0,0,0,0
                    ,0,0,0,0,0,0,0,0
                    ,0,0,0,0,0,0,0,0
                    ,6,6,6,6,6,6,6,6
                    ,1,2,3,4,5,3,2,1}; //board array


void loadPosition(){
    int k = 0;
    for(int i = 0; i < 8; i++){//loop through board array
        for(int j = 0; j < 8; j++){ //loop through board array
            int n = board[i][j];        //set n to board array
            if(!n) continue;            //if n is not 0 continue
            int x = abs(n) - 1;         //set x to absolute value of n minus 1
            int y = n > 0 ? 1 : 0;      //set y to n greater than  1 : 
            f[k].setTextureRect(IntRect(56 * x, 56 * y, 56, 56));   //set texture rect
            f[k].setPosition(56 * j, 56 * i);                       //set position
                    //explana
            // pieces[k].setTextureRect(IntRect(size * x, size * y, size, size));
            // pieces[k].setPosition(size * j, size * i);
            k++;

        }
    }
}

int main()                //main function
{
    RenderWindow window(sf::VideoMode(600, 600), "Checkers", Style::Close | Style::Titlebar);  //create window with size 600x600, title TicTacToe, and close and titlebar buttons on window 
    window.setFramerateLimit(60);   //set framerate limit to 60

    Texture red,board;        //create textures

    if(!red.loadFromFile("red.png")) //if texture is not loaded
    {
        cout << "Error loading texture" << endl; //print error message
    }
    if(!board.loadFromFile("chess_board.png")) //if texture is not loaded
    {
        cout << "Error loading texture" << endl; //print error message
    }
    
    // red.setSmooth(true); //set texture to smooth


    Sprite r;          //create sprite
    
    r.setTexture(red); //set texture to sprite
    
    r.setScale(0.04, 0.04); //set scale of sprite



    Sprite b;          //create sprite
    b.setTexture(board); //set texture to sprite
    b.setScale(0.25, 0.25); //set scale of sprite

    for(int i = 0; i < 32; i++)
    {
        f[i].setTexture(red); //set texture to sprite
        f[i].setScale(0.04, 0.04); //set scale of sprite
    }

    loadPosition();

    bool Move = false; //bool for move detection

    float x = 0; //float for x position
    float y = 0; //float for y position

    while (window.isOpen()) //while window is open
    {

        Vector2i mousePos = Mouse::getPosition(window); //get mouse position
        Event event;        //create event
        while (window.pollEvent(event)) //while window is polling for event
        {
			switch (event.type) //switch statement for event type
			{
                case Event::MouseButtonPressed: //if mouse button is pressed
                    if(event.mouseButton.button == Mouse::Left)
                    {
                        if(r.getGlobalBounds().contains(mousePos.x, mousePos.y)) //if mouse position is inside sprite
                        {
                            Move = true; //set move to true
                            x = mousePos.x - r.getPosition().x; //set x to mouse position minus sprite position
                            y = mousePos.y - r.getPosition().y; //set y to mouse position minus sprite position

                        }
                        
                    }
                    break;

                case Event::MouseButtonReleased: //if mouse button is released
                    if(event.mouseButton.button == Mouse::Left)
                    {
                        Move = false; //set move to false
                    }
                    break;

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
            if(Move) //if move is true
            {
                r.setPosition(mousePos.x - x, mousePos.y - y); //set sprite position to mouse position minus x and y
            }

        }
        window.clear(Color::White); //clear window with white color
        window.draw(b);        //draw sprite
        for(int i=0;i<32;i++){ window.draw(f[i]);       } //draw sprite
        window.display();           //display window
    }

    return 0;                   
} 