#include "view.hpp"


Game::Game(char * path)
{
    window=new sf::RenderWindow(sf::VideoMode(width,height),"fps: ");
    window->setFramerateLimit(60);
    sl::fileinfo filetext=sl::fileLoader(path);
    //sl::printFile(filetext); // testing
    fileinfo=sl::file2vector(filetext);
    sl::printInfo(fileinfo); // testing
    std::vector<sl::pointgraph> parts=sl::svg2points(fileinfo);

    std::array<double, 6> repoinfo=sl::getrepoinfo(parts,std::min({width,height}));
    double xmax=repoinfo[0],xmin=repoinfo[1],ymax=repoinfo[2],ymin=repoinfo[3],resRate=repoinfo[5];
    double reposition=std::min({width,height})*0.1;

    parts=sl::resizeRepo(parts,xmin-reposition,ymin-reposition,resRate);

    sf::VertexArray svgshape{sf::LineStrip},simplified{sf::Points};
    for (sl::pointgraph points:parts){
        for (std::array<double,2>i:points){svgshape.append(sf::Vector2f{(float)i[0],(float)i[1]});}
        svgshapes.push_back(svgshape);  svgshape.clear();

        points=sl::simplify(points);
        for (std::array<double,2>i:points){simplified.append(sf::Vector2f{(float)i[0]+hw,(float)i[1]});}
        simplifieds.push_back(simplified);  simplified.clear();
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
