#include <SFML/Graphics.hpp>    //SFML main library(s?)
#include <iostream>
#include <fstream>  //For opening external files, aka .png, .jpg, .txt //Note: not used (pq eto taca¿)
#include <vector>   //Dynamic arrays
#include <time.h>   //For "delay(miliseconds);" //not working as it should >:/

// <Debug mode> --------------------------------------------------------------------------
#define DEBUG 1
#if DEBUG
    #define println(x)    std::cout << x << std::endl;
    #define print(x)      std::cout << x ;
#else
    #define println(x)
    #define print(x)
#endif

// < Easier syntax > ----------------------------------------------------------------------
#define add(x) push_back(x)
#define PI 3.14159265359

// < War crime > -------------------------------------------------------------------------
using namespace sf;
using namespace std;

//-------------------------------------------------------------------------

class Entity {
private:
    sf::Texture texture;
    sf::IntRect img;
    sf::Vector2i startPos;
    sf::Vector2i spriteSize;
    sf::Sprite   sprite;
public:
    void addTexture(sf::Texture _texture,sf::IntRect pixelMap,sf::Vector2i _spriteSize) {
        this->img = pixelMap;
        this->spriteSize = _spriteSize;   
        this->texture = _texture;
        //Sprite spritei(_texture,this->spriteSize);
    }

    void move(int x,int y) {
        sprite.move(sprite.getPosition().x+x,sprite.getPosition().y+y);
    }
    //textura+tamañotextura

};
//-------------------------------------------------------------------------
/*class File {
public:
    std::string fileName;
    sf::Vector2i getFileSize() {
        ofstream file;
        file.open(fileName);

        file.close();
    }
};*/

//-------------------------------------------------------------------------

//         | X || Y | 
int   matrix[20][20];
const sf::Vector2f matrixSize  = sf::Vector2f(sizeof matrix / sizeof matrix[0], sizeof matrix[0] / sizeof(int));
const sf::Vector2f displaySize = sf::Vector2f(1000,1000);
const sf::Vector2f tileSize    = sf::Vector2f(displaySize.x / matrixSize.x, displaySize.y / matrixSize.y);
const int FPS = 20;

//-------------------------------------------------------------------------

void delay(int miliseconds) {
    clock_t end_time = clock() + miliseconds * CLOCKS_PER_SEC / 1000;
    while (clock() < end_time) {}
}

bool click() {
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

sf::Vector2f mousePosition() { 
    return sf::Vector2f(sf::Mouse::getPosition());    
}

std::vector<sf::VertexArray> helpMatrixMath(sf::Color color) {
    int totalIterations  = ((matrixSize.y + matrixSize.y)/1)+1;
    int posY = 0, posX = 0;

    std::vector<sf::VertexArray> lines;
    sf::VertexArray line(sf::LineStrip, 2);

    for (int i = 0; i < totalIterations; i++) {
        line[0].position = sf::Vector2f(0         , posY);
        line[1].position = sf::Vector2f(displaySize.x, posY);
        line[0].color = color;
        line[1].color = color;
        posY += tileSize.y;
        lines.add(line);

        line[0].position = sf::Vector2f(posX, 0          );
        line[1].position = sf::Vector2f(posX, displaySize.y);
        line[0].color = color;
        line[1].color = color;
        posX += tileSize.x;
        lines.add(line);
    }
    return lines;
}

sf::Sprite defaultPlayerBuild() {
    Texture alien;
    if (!alien.loadFromFile("alienTexture.png")) { println("Player texture not found"); }
    IntRect adelanten(0, 1, 6, 10);
    Sprite j1(alien, adelanten);
    j1.scale(2.5, 2.5);
    j1.move(10, 10);
    return j1;
}

void moveEntity(sf::RectangleShape&              sprite) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - int(tileSize.y)); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + int(tileSize.y)); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { sprite.setPosition(sprite.getPosition().x - int(tileSize.x), sprite.getPosition().y); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { sprite.setPosition(sprite.getPosition().x + int(tileSize.x), sprite.getPosition().y); }
    if (sprite.getPosition().x<0 || sprite.getPosition().y<0 || sprite.getPosition().x>displaySize.x || sprite.getPosition().y>displaySize.y) {
        sprite.setPosition(0, 0);
    }
}
void moveEntity(sf::Sprite&                      sprite) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - int(tileSize.y)); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + int(tileSize.y)); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { sprite.setPosition(sprite.getPosition().x - int(tileSize.x), sprite.getPosition().y); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { sprite.setPosition(sprite.getPosition().x + int(tileSize.x), sprite.getPosition().y); }
    if (sprite.getPosition().x<0 || sprite.getPosition().y<0 || sprite.getPosition().x>displaySize.x || sprite.getPosition().y>displaySize.y) {
        sprite.setPosition(0, 0);
    }
}
void moveEntity(std::vector<sf::RectangleShape>& sprite) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { for (int i = 0; i < sprite.size(); i++) { sprite[i].setPosition(sprite[i].getPosition().x, sprite[i].getPosition().y - int(tileSize.y)); } }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { for (int i = 0; i < sprite.size(); i++) { sprite[i].setPosition(sprite[i].getPosition().x, sprite[i].getPosition().y + int(tileSize.y)); } }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { for (int i = 0; i < sprite.size(); i++) { sprite[i].setPosition(sprite[i].getPosition().x - int(tileSize.x), sprite[i].getPosition().y); } }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { for (int i = 0; i < sprite.size(); i++) { sprite[i].setPosition(sprite[i].getPosition().x + int(tileSize.x), sprite[i].getPosition().y); } }
    //El coso para devolverlo a 0 da alta paja
}
void moveEntity(std::vector<sf::VertexArray>&    sprite) {
    int x = 0, y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { y -= tileSize.y; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { x -= tileSize.x; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { x += tileSize.x; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { y += tileSize.y; }
    if (x != 0 || y != 0) {
        for (int i = 0; i < sprite.size(); i++) {
            for (int e = 0; e < sprite[i].getVertexCount(); e++) {
                sprite[i].operator[](e).position =
                    sf::Vector2f(
                        sprite[i].operator[](e).position.x + x,
                        sprite[i].operator[](e).position.y + y
                    );
            }
        }
    }
  
}

/*void moveEntity(std::vector<sf::VertexArray>& sprite) {
    int Y = 0, X = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { Y -= tileSize.y; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { X -= tileSize.x; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { Y += tileSize.y; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { X += tileSize.x; }
    if (X != 0 || Y != 0) {
        for (int i = 0; i < sprite.size(); i++) {
            for (int e = 0; e < sprite[i].getVertexCount(); e++) {
                sprite[i].operator[](e).position = sf::Vector2f(
                    sprite[i].operator[](e).position.x + (X * tileSize.x),
                    sprite[i].operator[](e).position.y + (Y * tileSize.y)
                );
            }
        }
    }
    cout << "X: " << X << " Y: " << Y << endl;

}*/

sf::RectangleShape buildPoint() {
    sf::RectangleShape point;
    point.setFillColor(sf::Color::Red);
    point.setPosition(0, 0);
    point.setSize(tileSize);
    return point;
}

sf::VertexArray buildSquare(sf::Vector2f strtPos/*, sf::Vector2f plyrPos*/, int size, sf::Color color) {
    sf::VertexArray square(sf::Quads, 4);
    square[0].position = sf::Vector2f(strtPos.x                    , strtPos.y);
    square[1].position = sf::Vector2f(strtPos.x                    , strtPos.y + tileSize.y * size);
    square[2].position = sf::Vector2f(strtPos.x + tileSize.x * size, strtPos.y + tileSize.y * size);
    square[3].position = sf::Vector2f(strtPos.x + tileSize.x * size, strtPos.y);
    for (int i = 0; i < 4; i++) {   square[i].color = color;    }
    return square;
}

void moveVertexArray(sf::VertexArray& polygon,int x_,int y_) {
    float x = tileSize.x * x_;
    float y = tileSize.y * y_;
    for (int i = 0; i < polygon.getVertexCount(); i++){
        polygon[i].position = sf::Vector2f(polygon[i].position.x + x, polygon[i].position.y + y);
    }
}

sf::Vector2f center(sf::RectangleShape shape) {
    return sf::Vector2f((shape.getPosition().x - (shape.getSize().x) / 2) + tileSize.x, (shape.getPosition().y - (shape.getSize().y) / 2) + tileSize.y);
}

std::vector<sf::RectangleShape> rectangleInPoints(sf::Vector2i squareSize,sf::Vector2f strtPos,sf::Color color) {
    sf::RectangleShape aux;
    std::vector<sf::RectangleShape> out = { aux,aux,aux,aux };

    squareSize.x--;
    squareSize.y--;
    strtPos.x *= tileSize.x;
    strtPos.y *= tileSize.y;

    out[0].setPosition(sf::Vector2f(strtPos.x                            , strtPos.y                            ));
    out[1].setPosition(sf::Vector2f(strtPos.x + squareSize.x * tileSize.x, strtPos.y                            ));
    out[2].setPosition(sf::Vector2f(strtPos.x + squareSize.x * tileSize.x, strtPos.y + squareSize.y * tileSize.y));
    out[3].setPosition(sf::Vector2f(strtPos.x                            , strtPos.y + squareSize.y * tileSize.y));

    for (int i = 0; i < out.size(); i++) {
        out[i].setSize(tileSize);
        out[i].setFillColor(color);
    }

    return out;
}

void drawRectangles(sf::RenderWindow& window, std::vector<sf::RectangleShape> aux) {
    for (int i = 0; i < aux.size(); i++) {
        window.draw(aux[i]);
    }
}
void drawRectangles(sf::RenderWindow& window,             sf::RectangleShape  aux) {
    window.draw(aux);
}
void drawRectangle (sf::RenderWindow& window, std::vector<sf::RectangleShape> aux) {
    for (int i = 0; i < aux.size(); i++) {
        window.draw(aux[i]);
    }
}
void drawRectangle (sf::RenderWindow& window,             sf::RectangleShape  aux) {
    window.draw(aux);
}

void drawLines     (sf::RenderWindow& window, std::vector<sf::VertexArray>  lines) {
    for (int i = 0; i < lines.size(); i++) { window.draw(lines[i]); }
}

std::vector<sf::VertexArray> connectPointsOnSquares(std::vector<sf::RectangleShape> aux,sf::Color color) {
    std::vector<sf::VertexArray> out;
    sf::VertexArray line(sf::LineStrip, 2);
    for (int i = 0; i < aux.size()-1; i++) {
        line[0].position = center(aux[i]);
        line[1].position = center(aux[i + 1]);
        line[0].color = color;
        line[1].color = color;
        out.add(line);
    }
    line[0].position = center(aux[aux.size()-1]);
    line[1].position = center(aux[0]);
    line[0].color = color;
    line[1].color = color;
    out.add(line);
    return out;
}
std::vector<sf::VertexArray> connectPointsOnSquares(std::vector<sf::RectangleShape> aux                ) {
    std::vector<sf::VertexArray> out;
    sf::VertexArray line(sf::LineStrip, 2);
    for (int i = 0; i < aux.size() - 1; i++) {
        line[0].position = center(aux[i]);
        line[1].position = center(aux[i + 1]);
        out.add(line);
    }
    line[0].position = center(aux[aux.size() - 1]);
    line[1].position = center(aux[0]);
    out.add(line);
    return out;
}

std::vector<sf::VertexArray> sumRectShapeVectors(std::vector<sf::RectangleShape> a, std::vector<sf::RectangleShape> b,sf::Color color) {
    std::vector<sf::VertexArray> out;
    for (int i = 0; i < connectPointsOnSquares(a).size(); i++) {
        out.add(connectPointsOnSquares(a,color)[i]);
    }
    return out;
}

std::vector<sf::VertexArray> connectSquares(std::vector<sf::VertexArray>    a, std::vector<sf::VertexArray>    b, sf::Color color) {
    std::vector<sf::VertexArray> out;
    std::vector<sf::Vertex> points;

    for (int i = 0; i < a.size(); i++) { points.add(a[i].operator[](0)); }
    for (int i = 0; i < b.size(); i++) { points.add(b[i].operator[](0)); }

    sf::VertexArray line(sf::LineStrip, 2);
    for (int i = 0; i < points.size(); i++) {
        line[0].position = points[i].position;
        line[0].color = color;
        for (int e = 0; e < points.size(); e++) {
            line[1].position = points[e].position;
            line[1].color = color;
            out.add(line);
        }
    }
    return out;
}
std::vector<sf::VertexArray> connectSquares(std::vector<sf::RectangleShape> a, std::vector<sf::RectangleShape> b, sf::Color color) {
    std::vector<sf::VertexArray> a_ = connectPointsOnSquares(a);
    std::vector<sf::VertexArray> b_ = connectPointsOnSquares(b);
    std::vector<sf::VertexArray> out;
    std::vector<sf::Vertex> points;

    for (int i = 0; i < a_.size(); i++) { points.add(a_[i].operator[](0)); }
    for (int i = 0; i < b_.size(); i++) { points.add(b_[i].operator[](0)); }

    sf::VertexArray line(sf::LineStrip, 2);
    for (int i = 0; i < points.size(); i++) {
        line[0].position = points[i].position;
        line[0].color = color;
        for (int e = 0; e < points.size(); e++) {
            line[1].position = points[e].position;
            line[1].color = color;
            out.add(line);
        }
    }
    return out;
}
std::vector<sf::VertexArray> connectSquares(std::vector<sf::RectangleShape> a,                                    sf::Color color) {
    std::vector<sf::VertexArray> out;
    std::vector<sf::Vertex>      points;

    std::vector<sf::VertexArray> a_ = connectPointsOnSquares(a);

    for (int i = 0; i < a_.size(); i++) { points.add(a_[i].operator[](0)); }

    sf::VertexArray line(sf::LineStrip, 2);
    for (int i = 0; i < points.size(); i++) {
        line[0].position = points[i].position;
        line[0].color    = color;
        for (int e = 0; e < points.size(); e++) {
            line[1].position = points[e].position;
            line[1].color    = color;
            out.add(line);
        }
    }
    return out;
}
std::vector<sf::VertexArray> connectSquares(std::vector<sf::VertexArray>    a,                                    sf::Color color) {
    std::vector<sf::VertexArray> out;
    std::vector<sf::Vertex> points;

    for (int i = 0; i < a.size(); i++) { points.add(a[i].operator[](0)); }

    sf::VertexArray line(sf::LineStrip, 2);
    for (int i = 0; i < points.size(); i++) {
        line[0].position = points[i].position;
        line[0].color = color;
        for (int e = 0; e < points.size(); e++) {
            line[1].position = points[e].position;
            line[1].color = color;
            out.add(line);
        }
    }
    return out;
}

//-----------------------------------------------------------------------------------------------------------------------\\
//-<{@}>-<{@}>-<{@}>-<{@}>-<{@}>-<{@}>-<{@}>-<{@}>-<{@}>-<#{<@>}#>-<{@}>-<{@}>-<{@}>-<{@}>-<{@}>-<{@}>-<{@}>-<{@}>-<{@}>-\\
//-----------------------------------------------------------------------------------------------------------------------\\

int main() {
//-----------------------------------------------------------------------------------------------------------
    //Reference https://www.youtube.com/watch?v=huMO4VQEwPc&ab_channel=3DSage 9:14 (DOOM engine)
    //Reference https://www.youtube.com/watch?v=CcNCgmVJiBY&ab_channel=3DSage 2:26 distorsion x FOV
//-----------------------------------------------------------------------------------------------------------
    print("Screen setup...  ");

    sf::RenderWindow window(sf::VideoMode(displaySize.x, displaySize.y), "Matrix test");
    window.setFramerateLimit(FPS);

    println("Ready!");
//-----------------------------------------------------------------------------------------------------------
    print("Sprite setup...  ");

    sf::RectangleShape point = buildPoint();

    //sf::VertexArray    square = buildSquare(sf::Vector2f(tileSize_x * 2, tileSize_y * 2), point.getPosition(), 8, sf::Color::Green);
    //sf::VertexArray   square2 = buildSquare(sf::Vector2f(tileSize_x * 4, tileSize_y * 4), point.getPosition(), 12, sf::Color::Blue);

    std::vector<sf::RectangleShape> a,b;
    a = rectangleInPoints(sf::Vector2i(7, 7), sf::Vector2f(4, 2), sf::Color::Blue);
    b = rectangleInPoints(sf::Vector2i(7, 7), sf::Vector2f(3, 3), sf::Color::Magenta);
    std::vector<sf::VertexArray> e = connectSquares(a, b, sf::Color::Red);
    std::vector<sf::VertexArray> o;

    o = sumRectShapeVectors(a, b,sf::Color::Blue);

    println("Ready!");
//-----------------------------------------------------------------------------------------------------------
    while (window.isOpen()) {
        //---------------------------------------------------------------------------------------------------
        sf::Event event;
        while (window.pollEvent(event)) { 
            if (event.type == sf::Event::Closed) { window.close(); } 
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code){
                    case (sf::Keyboard::Escape): window.close(); break;
                    default:                                     break;
                }
            }
        }  
        //---------------------------------------------------------------------------------------------------    
        window.clear(sf::Color::White);
        //---------------------------------------------------------------------------------------------------
        moveEntity(e);
        drawLines(window, e);
        //---------------------------------------------------------------------------------------------------
        drawRectangles(window, a);
        drawRectangles(window, b);
        drawRectangles(window, point);
        //drawLines(window, connectSquares(a, b, sf::Color::Black));
        drawLines(window, helpMatrixMath(sf::Color::Red));
        //---------------------------------------------------------------------------------------------------
        window.display();
    //-------------------------------------------------------------------------------------------------------
    }
    window.close();
//-----------------------------------------------------------------------------------------------------------
    return 0;
}

//1:03 AM 24/7/2022
//TENGO QUE DEFORMAR EL VertexArray NO MOVERLO NOMAS PELOTUDA AAAAAAAAAAAA TA MAÑANMA REY LA PASE RE LINDO,
//SI SE PUEDE CARAJO 
//Cali, confio en vos <3
