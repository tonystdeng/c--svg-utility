#include "view.hpp"


Game::Game(char * path)
{
    window=new sf::RenderWindow(sf::VideoMode(width,height),"fps: ");
    window->setFramerateLimit(60);
    sl::fileinfo filetext=sl::fileLoader(path);
    //sl::printFile(filetext); // testing
    fileinfo=sl::file2vector(filetext);
    sl::printInfo(fileinfo); // testing
    double largest=0;
    double xmax=0,xmin=0,ymax=0,ymin=0;
    std::vector<sl::pointgraph> parts;
    sl::point *travelPtr=nullptr;
    for (int i=0;i<fileinfo.size();i++){
        std::vector<sl::pointgraph> newParts=sl::getPointGraph(fileinfo[i],travelPtr);
        parts.insert(parts.end(),newParts.begin(),newParts.end());
    }
    for (sl::pointgraph points:parts){
        for (sl::point i:points){
            if (i[0]>xmax){xmax=i[0];} else if (i[0]<xmin){xmin=i[0];}
            if (i[1]>ymax){ymax=i[1];} else if (i[1]<ymin){ymin=i[1];}
        }
    }
    largest=std::max({std::abs(xmax)-std::abs(xmin),std::abs(ymax)-std::abs(ymin)});
    double resoRate=std::min({width,height})/largest*0.8;
    double reposition=std::min({width,height})*0.1;

    sf::VertexArray svgshape{sf::LineStrip},simplified{sf::Points};
    for (sl::pointgraph points:parts){
        for (std::array<double,2>i:points){
            svgshape.append(sf::Vector2f{(float)((i[0]-xmin)*resoRate+reposition),(float)((i[1]-ymin)*resoRate+reposition)});
        }svgshapes.push_back(svgshape);
        svgshape.clear();
        points=sl::simplify(points);
        for (std::array<double,2>i:points){
            simplified.append(sf::Vector2f{(float)((i[0]-xmin)*resoRate+reposition)+hw,(float)((i[1]-ymin)*resoRate+reposition)});
        }simplifieds.push_back(simplified);
        simplified.clear();
    }
    dividLine.setSize(sf::Vector2f(width/256,height));
    dividLine.setPosition({hw-dividLine.getSize().x,0});
    dividLine.setFillColor({255,63,63});
}

Game::~Game()
{
    delete window;
}

void Game::main()
{
    if (checkEvent()){return;}
    updatefps();
    window->clear(sf::Color::Black);
    common();
    for (int i=0;i<svgshapes.size();i++){
        window->draw(svgshapes[i]);
        window->draw(simplifieds[i]);
    }
    window->display();
}

void Game::common()
{
    window->draw(dividLine);
}

bool Game::checkEvent()
{
    while (window->pollEvent(event)){
        if (event.type==sf::Event::Closed){
            window->close();
            return true;}
    }return false;
}

void Game::updatefps()
{
    elapsed=clock.restart();
    fpsupdateCountdown+=elapsed;
    if (fpsupdateCountdown>fpsupdateInterval)
    {
        fps = 1./elapsed.asSeconds();
        fpsloader<<fps;
        window->setTitle("fps: "+fpsloader.str());
        fpsloader.str("");fpsloader.clear();
        fpsupdateCountdown-=fpsupdateInterval;
    }
}
