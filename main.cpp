#include <iostream>
#include <SFML/Graphics.hpp>

#include "./src/ConcavePolygon.h"

void drawPolygon(sf::RenderWindow& window, ConcavePolygon const & poly)
{
    if(poly.getNumberSubPolys() > 0)
    {
        drawPolygon(window, poly.getSubPolygon(0));
        drawPolygon(window, poly.getSubPolygon(1));
    }
    else
    {
    std::vector<Vertex > const & verts = poly.getVertices();

    std::vector<sf::Vertex > realVerts;

    sf::Text text;
    sf::Font font;
    font.loadFromFile("./fonts/courbd.ttf");
    text.setFont(font);
    //text.setCharacterSize(5);
    text.setScale({0.01f, 0.01f});

    for(unsigned int i=0; i<verts.size(); ++i)
    {
        sf::Vector2f position = {verts[i].position.x, verts[i].position.y};
        realVerts.push_back(sf::Vertex(position));

        text.setString(std::to_string(i));
        text.setPosition(position + sf::Vector2f{0.005f, 0.0f});
        window.draw(text);
    }
    if(realVerts.size() > 0)
        realVerts.push_back(realVerts[0]);

    window.draw(realVerts.data(), realVerts.size(), sf::LineStrip);
    }
}

void drawLineSegment(sf::RenderWindow& window, LineSegment const & seg)
{
    sf::Vector2f position = {seg.startPos.x, seg.startPos.y};
    sf::Color color = {100,150,100,100};
    sf::Vertex v1{position, color};
    position = {seg.finalPos.x, seg.finalPos.y};
    sf::Vertex v2{position, color};

    std::vector<sf::Vertex > verts = {v1, v2};

    window.draw(verts.data(), verts.size(), sf::LineStrip);
}

void drawGrid(sf::RenderWindow& window, sf::Vector2f const & spacing)
{
    sf::Vector2f viewSize = window.getView().getSize();

    int xGridLines = viewSize.x / spacing.x;
    int yGridLines = viewSize.y / spacing.y;

    std::vector<sf::Vertex > lineVertices;

    sf::Color gridColor = {100, 100, 100, 100};
    sf::Color axisColor = {200, 100, 100, 200};

    for(int i=-xGridLines/2; i<=xGridLines/2; ++i)
    {
        float x = (float)i * spacing.x;
        float yMin = -viewSize.y / 2.0f;
        float yMax = viewSize.y/2.0f;

        sf::Color currColor = gridColor;
        if(i==0)
            currColor = axisColor;

        lineVertices.push_back(sf::Vertex({x,yMin}, currColor));
        lineVertices.push_back(sf::Vertex({x,yMax}, currColor));
    }

    for(int i=-yGridLines/2; i<=yGridLines/2; ++i)
    {
        float y = (float)i * spacing.y;
        float xMin = -viewSize.x / 2.0f;
        float xMax = viewSize.x/2.0f;

        sf::Color currColor = gridColor;
        if(i==0)
            currColor = axisColor;

        lineVertices.push_back(sf::Vertex({xMin,y}, currColor));
        lineVertices.push_back(sf::Vertex({xMax,y}, currColor));
    }

    window.draw(lineVertices.data(), lineVertices.size(), sf::Lines);
}

void drawVertices(sf::RenderWindow & window, std::vector<Vertex > const & vertices)
{
    sf::Color color = {140,140,140,200};
    std::vector<sf::Vertex > realVerts;
    for(unsigned int i=0; i<vertices.size(); ++i)
    {
        sf::Vector2f position = {vertices[i].position.x, vertices[i].position.y};
        realVerts.push_back(sf::Vertex(position, color));
    }
    if(realVerts.size() > 0)
        realVerts.push_back(realVerts[0]);

    window.draw(realVerts.data(), realVerts.size(), sf::LineStrip);
}

void drawCoordinates(sf::RenderWindow & window, sf::Vector2f const & coords, sf::Vector2f const & offset)
{
    sf::Text text;
    sf::Font font;
    font.loadFromFile("./fonts/courbd.ttf");
    text.setFont(font);
    //text.setCharacterSize(5);
    text.setScale({0.01f, 0.01f});

    std::string str = "(" + std::to_string(coords.x) + ", " + std::to_string(coords.y) + ")";
    text.setString(str);
    text.setPosition(coords + offset);

    window.draw(text);
}

void printVertices(std::vector<Vertex > const & verts)
{
    std::cout << "\nPolygon, " << verts.size() << " vertices: \n";
    for(auto& vert : verts)
    {
        std::cout << "{{" << vert.position.x << "f, " << vert.position.y << "f}},\n";
    }
}

void scaleVerts(std::vector<Vertex > & verts, float amount)
{
    for(auto& vert : verts)
    {
        vert.position = vert.position * amount;
    }
}

int main()
{
    sf::RenderWindow window;
    sf::VideoMode mode(800, 800);
    window.create(mode, "test");

    sf::View view;
    view.setCenter({0.0f, 0.0f});
    view.zoom(0.02f);
    window.setView(view);

    std::vector<Vertex > verts = {
        /*{{-2.15f, -3.1f}},
        {{1.225f, -3.3f}},
        {{2.4f, -1.45f}},
        {{2.3f, 0.35f}},
        {{1.725f, 2.1f}},
        {{0.85f, -0.475f}},
        {{-1.7f, 2.375f}},
        {{-4.625f, -0.35f}}*/
        {{0.15f, -3.65f}},
{{2.475f, -3.275f}},
{{1.15f, -3.175f}},
{{1.0f, -2.175f}},
{{2.325f, -1.775f}},
{{4.725f, -1.725f}},
{{6.225f, -1.175f}},
{{6.95f, -0.05f}},
{{6.625f, 1.775f}},
{{4.775f, 4.15f}},
{{3.4f, 4.275f}},
{{2.425f, 3.175f}},
{{2.575f, 1.925f}},
{{1.825f, 0.0f}},
{{1.05f, -0.15f}},
{{-2.225f, 1.175f}},
{{-3.4f, 0.3f}},
{{-3.95f, -1.25f}},
{{-3.35f, -2.5f}},
{{-1.05f, -3.625f}}
    };

    std::vector<Vertex > mouseVerts;

    LineSegment mouseLs;
    mouseLs.startPos = {-0.938f, 0.0f};
    mouseLs.finalPos = {1.0f, 0.0f};
    int mouseLsSeg = 0;

    //scaleVerts(verts, 1000.0f);
    ConcavePolygon poly(verts);
    //poly.convexDecomp();

    std::cout << poly.checkIfRightHanded() << "\n";

    //poly.slicePolygon(1, 3);
    LineSegment segment;
    segment.finalPos = {0.0f, 1.0f};
    segment.startPos = {1.0f, -2.0f};
    //poly.convexDecomp();

    while(window.isOpen())
    {
        sf::Event currEvent;

        while(window.pollEvent(currEvent))
        {
            switch(currEvent.type)
            {
                case(sf::Event::Closed):
                    window.close();
                    break;
                case(sf::Event::KeyPressed):
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        if(mouseVerts.size() > 2)
                        {
                            poly = ConcavePolygon(mouseVerts);
                            //poly.convexDecomp();
                            mouseVerts.clear();
                        }
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                    {
                        poly.convexDecomp();
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                    {
                        poly.slicePolygon(mouseLs);
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                    {
                        poly.reset();
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
                    {
                        printVertices(poly.getVertices());
                    }

                    break;

                }
                case(sf::Event::MouseButtonPressed):
                {
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        Vec2 position = {mousePosition.x, mousePosition.y};
                        mouseVerts.push_back(Vertex(position));
                    }
                    else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        Vec2 position = {mousePosition.x, mousePosition.y};
                        if(mouseLsSeg % 2 == 0)
                            mouseLs.startPos = position;
                        else
                            mouseLs.finalPos = position;

                        ++mouseLsSeg;

                    }
                    break;

                }
                default:
                    break;
            }
        }


        window.clear(sf::Color::Black);

        drawGrid(window, {0.5f, 0.5f});
        drawPolygon(window, poly);
        drawLineSegment(window, mouseLs);
        drawCoordinates(window, window.mapPixelToCoords(sf::Mouse::getPosition(window)), {0.28f, 0.15f});
        drawVertices(window, mouseVerts);

        window.display();

        sf::sleep(sf::milliseconds(16));
    }
}
