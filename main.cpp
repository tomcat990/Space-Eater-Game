#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
using namespace sf;


int main(){
	
	srand(time(0));

	//objects


	RenderWindow window(sf::VideoMode(1000, 1000), "Space Eater");
  	
		//background picture
	Texture backtexture;
	backtexture.loadFromFile("images/image1.jpg");
	Sprite background;
	background.setTexture(backtexture);

	float x=20;
	float y=20;
		//player

	RectangleShape player({x,y});
	player.setFillColor(Color(150,100,0));
	player.setPosition({400,100});
		//food

	CircleShape food({7});
	food.setFillColor(Color(0,250,5));
	food.setPosition({float(rand()%1000),float(rand()%1000)});
		//enemies

	class Enemy {
	public:
    	CircleShape shape;

 	   Enemy(float x,float y) {
    	    shape = CircleShape(10.f, 3);  
        	shape.setFillColor(Color::Red);
			shape.setPosition(x,y);
   	   }
		
  	  void draw_enemy(RenderWindow& window) {
  	      window.draw(shape);
   		 }
	  
	  FloatRect global_enemy(){
	 	return shape.getGlobalBounds();
	  }
	};
	
	vector<Enemy> enemies;
	for (int i=0;i<45;i++){
		float k=rand()%991+4;
		float l=rand()%991+4;
		enemies.push_back(Enemy(k,l));
	}

		//selection of a font and making a score text
	Font font;
	font.loadFromFile("fonts/arial.TTF");
	Text score;
	score.setFont(font);
	int scorenum=0;
	score.setString("score:"+to_string(scorenum));
	score.setPosition(0,0);
	score.setFillColor(Color(0,250,250));
	
	//main loop of the game

	while(window.isOpen()){
		
			Event event;
		while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
	window.clear();
    
	//drawing objects
	
	//window.draw(background);
	window.draw(player);
	window.draw(food);
	window.draw(score);
	for(int i=0;i<enemies.size();i++){
		enemies[i].draw_enemy(window);
	}

		//intersection with food

	if(player.getGlobalBounds().intersects(food.getGlobalBounds())){
		food.setPosition(float((rand()%970)+10),float((rand()%970)+10));	
		scorenum+=100;
		score.setString("score:"+to_string(scorenum));	
	}
	
		//intersection with enemies

	for(int i=0;i<enemies.size();i++){
		if(player.getGlobalBounds().intersects(enemies[i].global_enemy())){
			this_thread::sleep_for(chrono::milliseconds(5));
			scorenum-=1;
			score.setString("score:"+to_string(scorenum));	
			
		}
	}

		//making a wraping world.

	float y_player=player.getPosition().y;
	float x_player=player.getPosition().x;
	if(player.getPosition().x >window.getSize().x)
	{
		player.setPosition(0,y_player);
	}
		
	if(player.getPosition().x <0){
	
		player.setPosition(window.getSize().x,y_player);
	}
	
	if(player.getPosition().y <0){
	
		player.setPosition(x_player,window.getSize().y);
	}
	
	if(player.getPosition().y >window.getSize().y){
	
		player.setPosition(x_player,0);
	}
	


		//player movements
	
	if(Keyboard::isKeyPressed(Keyboard::Key::Left)){
		player.move({-1.f,0.f});
	}
	
	
	if(Keyboard::isKeyPressed(Keyboard::Key::Right)){
		player.move({1.f,0.f});
	}

	
	if(Keyboard::isKeyPressed(Keyboard::Key::Up)){
		player.move({0.f,-1.f});
	}

	
	if(Keyboard::isKeyPressed(Keyboard::Key::Down)){
		player.move({0.f, 1.f});
	}


	

	window.display();


	}



return 0;

}
