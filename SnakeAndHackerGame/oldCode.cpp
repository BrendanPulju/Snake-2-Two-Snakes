/*
for (int i = 0; i < 10; i++) {
	for (int j = 0; j < 10; j++) {
		RectangleShape temp(Vector2f(50, 50));
		if ((i + j) % 2 == 0) {
			temp.setFillColor(Color::Black);
		}
		else {
			temp.setFillColor(Color::Red);
		}
		temp.setOutlineColor(Color::White);
		temp.setOutlineThickness(2);
		temp.setPosition((i * 50) + 250, (j * 50) + 50);
		window.draw(temp);
	}
}
*/

/*#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Hello World");
	window.setFramerateLimit(60);

	sf::Event event;

	Font font;
	font.loadFromFile("PressStart2P.ttf");

	Text midText;
	midText.setFont(font);
	midText.setString("P1 Press Space");
	midText.setFillColor(Color(75, 75, 75));
	midText.setCharacterSize(25);
	midText.setPosition(400, 600);

	int numMoves = 0;

	bool p1Turn = true;
	bool turnStarted = false;
	bool turnDone = false;

	int p1Score = 0;
	int p2Score = 0;

	CircleShape p1(25);
	p1.setFillColor(Color(200, 75, 75));
	p1.setOutlineColor(Color::White);
	p1.setOutlineThickness(1);
	p1.setPosition(350, 50);

	CircleShape p2(25);
	p2.setFillColor(Color(75, 200, 75));
	p2.setOutlineColor(Color::White);
	p2.setOutlineThickness(1);
	p2.setPosition(800, 500);

	//board begins at (350, 50)
	int bArray[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			bArray[i][j] = 0;
		}
	}

	bool gameOn = false;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}

		window.clear(Color::White);

		// Draw board
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				RectangleShape temp(Vector2f(50, 50));
				if (bArray[i][j] == 0) {
					temp.setFillColor(Color(75, 75, 200, 200));
				}
				else if (bArray[i][j] == 1) {
					temp.setFillColor(Color(200, 75, 75, 200));
				}
				else {
					temp.setFillColor(Color(75, 200, 200, 200));
				}
				temp.setOutlineColor(Color::White);
				temp.setOutlineThickness(2);
				temp.setPosition((i * 50) + 350, (j * 50) + 50);
				window.draw(temp);
				
			}
		}

		if (gameOn == true) {
			//P1 get moves
			if (p1Turn == true) {
				if (Keyboard::isKeyPressed(Keyboard::Space) && !turnStarted) {
					numMoves = (rand() % 6 + 1);
					turnStarted = true;
				}
				if (turnStarted == true) {
					midText.setString("Moves Remaining: " + std::to_string(numMoves));
				}
			}
			// P1 movement
			if (p1Turn == true && numMoves != 0) {
				if (Keyboard::isKeyPressed(Keyboard::Left) && (p1.getPosition().x > 350))
				{
					p1.setPosition(p1.getPosition().x - 50, p1.getPosition().y);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && (p1.getPosition().x < 800))
				{
					p1.setPosition(p1.getPosition().x + 50, p1.getPosition().y);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) && (p1.getPosition().y > 50))
				{
					p1.setPosition(p1.getPosition().x, p1.getPosition().y - 50);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && (p1.getPosition().y < 500))
				{
					p1.setPosition(p1.getPosition().x, p1.getPosition().y + 50);
					numMoves--;
				}
				if (numMoves == 0) // check if last move was played
				{
					turnDone = true;
				}
				int iPos = (p1.getPosition().x - 350) / 50; //update bArray
				int jPos = (p1.getPosition().y - 50) / 50;
				bArray[iPos][jPos] = 1;
			}

			//P2 get moves
			if (p1Turn == false) {
				if (Keyboard::isKeyPressed(Keyboard::Space) && !turnStarted) {
					numMoves = (rand() % 6 + 1);
					turnStarted = true;
				}
				if (turnStarted == true) {
					midText.setString("Moves Remaining: " + std::to_string(numMoves));
				}
			}
			//P2 movement
			if (p1Turn == false && numMoves != 0) {
				if (Keyboard::isKeyPressed(Keyboard::Left) && (p1.getPosition().x > 350))
				{
					p2.setPosition(p2.getPosition().x - 50, p2.getPosition().y);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && (p2.getPosition().x < 800))
				{
					p2.setPosition(p2.getPosition().x + 50, p2.getPosition().y);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) && (p2.getPosition().y > 50))
				{
					p2.setPosition(p2.getPosition().x, p2.getPosition().y - 50);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && (p2.getPosition().y < 500))
				{
					p2.setPosition(p2.getPosition().x, p2.getPosition().y + 50);
					numMoves--;
				}
				if (numMoves == 0) // check if last move was played
				{
					turnDone = true;
				}
				int iPos = (p2.getPosition().x - 350) / 50;
				int jPos = (p2.getPosition().y - 50) / 50;
				bArray[iPos][jPos] = 2;
			}


			//draw and display
			window.draw(p1);
			window.draw(p2);
			window.draw(midText);
			window.display();

			//update turn for next loop
			if (turnDone == true)
			{
				p1Turn = not p1Turn;
				turnDone = false;
				turnStarted = false;
			}

			//update prompts for next turn
			if (p1Turn && !turnStarted) {
				midText.setString("P1 Press Space");
			}
			if (!p1Turn && !turnStarted) {
				midText.setString("P2 Press Space");
			}

			sleep(seconds(.1));
		}
	}

	return 0;
}

*/

/*
minimum working state:
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Hello World");
	window.setFramerateLimit(60);

	sf::Event event;

	Font font;
	font.loadFromFile("PressStart2P.ttf");

	Text midText;
	midText.setFont(font);
	midText.setString("P1 Press Space");
	midText.setFillColor(Color(75, 75, 75));
	midText.setCharacterSize(25);
	midText.setPosition(400, 600);

	int numMoves = 0;

	bool p1Turn = true;
	bool turnStarted = false;
	bool turnDone = false;

	int p1Score = 0;
	int p2Score = 0;
	bool scoresCalculated = false;

	CircleShape p1(25);
	p1.setFillColor(Color(200, 75, 75));
	p1.setOutlineColor(Color::White);
	p1.setOutlineThickness(1);
	p1.setPosition(350, 50);

	CircleShape p2(25);
	p2.setFillColor(Color(75, 200, 75));
	p2.setOutlineColor(Color::White);
	p2.setOutlineThickness(1);
	p2.setPosition(800, 500);

	//board begins at (350, 50)
	int bArray[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			bArray[i][j] = 0;
		}
	}

	bool gameOn = false;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}

		window.clear(Color::White);

		gameOn = false;

		// Draw board
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				RectangleShape temp(Vector2f(50, 50));
				if (bArray[i][j] == 0) {
					temp.setFillColor(Color(75, 75, 200, 200));
					gameOn = true;
				}
				else if (bArray[i][j] == 1) {
					temp.setFillColor(Color(200, 75, 75, 200));
				}
				else {
					temp.setFillColor(Color(75, 200, 200, 200));
				}
				temp.setOutlineColor(Color::White);
				temp.setOutlineThickness(2);
				temp.setPosition((i * 50) + 350, (j * 50) + 50);
				window.draw(temp);
			}
		}


		//calculate score if game is over
		if (gameOn == false && scoresCalculated == false) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (bArray[i][j] == 1) {
						p1Score++;
					}
					else if (bArray[i][j] == 2) {
						p2Score++;
					}
				}
			}
			scoresCalculated = true;
		}

		//ending screen
		if (gameOn == false){
			if (p1Score > p2Score) {
				midText.setString("Player 1 Wins!");
			}
			else if (p1Score < p2Score) {
				midText.setString("Player 2 Wins!");
			}
			else {
				midText.setString("Nobody Wins!");
			}
		}

		if (gameOn == true) {
			//P1 get moves
			if (p1Turn == true) {
				if (Keyboard::isKeyPressed(Keyboard::Space) && !turnStarted) {
					numMoves = (rand() % 6 + 1);
					turnStarted = true;
				}
				if (turnStarted == true) {
					midText.setString("Moves Remaining: " + std::to_string(numMoves));
				}
			}
			// P1 movement
			if (p1Turn == true && numMoves != 0) {
				if (Keyboard::isKeyPressed(Keyboard::Left) && (p1.getPosition().x > 350))
				{
					p1.setPosition(p1.getPosition().x - 50, p1.getPosition().y);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && (p1.getPosition().x < 800))
				{
					p1.setPosition(p1.getPosition().x + 50, p1.getPosition().y);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) && (p1.getPosition().y > 50))
				{
					p1.setPosition(p1.getPosition().x, p1.getPosition().y - 50);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && (p1.getPosition().y < 500))
				{
					p1.setPosition(p1.getPosition().x, p1.getPosition().y + 50);
					numMoves--;
				}
				if (numMoves == 0) // check if last move was played
				{
					turnDone = true;
				}
				int iPos = (p1.getPosition().x - 350) / 50; //update bArray
				int jPos = (p1.getPosition().y - 50) / 50;
				bArray[iPos][jPos] = 1;
			}

			//P2 get moves
			if (p1Turn == false) {
				if (Keyboard::isKeyPressed(Keyboard::Space) && !turnStarted) {
					numMoves = (rand() % 6 + 1);
					turnStarted = true;
				}
				if (turnStarted == true) {
					midText.setString("Moves Remaining: " + std::to_string(numMoves));
				}
			}
			//P2 movement
			if (p1Turn == false && numMoves != 0) {
				if (Keyboard::isKeyPressed(Keyboard::Left) && (p1.getPosition().x > 350))
				{
					p2.setPosition(p2.getPosition().x - 50, p2.getPosition().y);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && (p2.getPosition().x < 800))
				{
					p2.setPosition(p2.getPosition().x + 50, p2.getPosition().y);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) && (p2.getPosition().y > 50))
				{
					p2.setPosition(p2.getPosition().x, p2.getPosition().y - 50);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && (p2.getPosition().y < 500))
				{
					p2.setPosition(p2.getPosition().x, p2.getPosition().y + 50);
					numMoves--;
				}
				if (numMoves == 0) // check if last move was played
				{
					turnDone = true;
				}
				int iPos = (p2.getPosition().x - 350) / 50;
				int jPos = (p2.getPosition().y - 50) / 50;
				bArray[iPos][jPos] = 2;
			}

			//update turn for next loop
			if (turnDone == true)
			{
				p1Turn = not p1Turn;
				turnDone = false;
				turnStarted = false;
			}

			//update prompts for next turn
			if (p1Turn && !turnStarted) {
				midText.setString("P1 Press Space");
			}
			if (!p1Turn && !turnStarted) {
				midText.setString("P2 Press Space");
			}

			sleep(seconds(.1));
		}

		//draw and display
		window.draw(p1);
		window.draw(p2);
		window.draw(midText);
		window.display();
	}

	return 0;
}


*/
/*#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <chrono>

using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 700), "Snake 2");
	window.setFramerateLimit(60);

	sf::Event event;

	Font font;
	font.loadFromFile("PressStart2P.ttf");

	Text startText;
	startText.setFont(font);
	startText.setString("Press C for Classic Mode \nPress R for Random Mode");
	startText.setFillColor(Color(75, 75, 75));
	startText.setCharacterSize(25);
	startText.setPosition(50, 300);

	Text midText;
	midText.setFont(font);
	midText.setString("P1 Press Space");
	midText.setFillColor(Color(75, 75, 75));
	midText.setCharacterSize(25);
	midText.setPosition(400, 600);

	Text p1Text;
	p1Text.setFont(font);
	p1Text.setString("P1 Score: ");
	p1Text.setFillColor(Color(75, 75, 75));
	p1Text.setCharacterSize(25);
	p1Text.setPosition(25, 100);

	Text p2Text;
	p2Text.setFont(font);
	p2Text.setString("P2 Score: ");
	p2Text.setFillColor(Color(75, 75, 75));
	p2Text.setCharacterSize(25);
	p2Text.setPosition(875, 100);

	int numMoves = 0;

	bool p1Turn = true;
	bool turnStarted = false;
	bool turnDone = false;
	bool unique = false;
	bool dead = false;

	int p1Score = 0;
	int p2Score = 0;
	bool scoresCalculated = false;

	//CircleShape p1(25);
	//p1.setFillColor(Color(200, 75, 75));
	//p1.setOutlineColor(Color::White);
	//p1.setOutlineThickness(1);
	Texture rSnake;
	rSnake.loadFromFile("snakeRed.png");
	Sprite p1;
	p1.setTexture(rSnake);
	p1.setPosition(350, 50);

	//CircleShape p2(25);
	//p2.setFillColor(Color(75, 200, 75));
	//p2.setOutlineColor(Color::White);
	//p2.setOutlineThickness(1);
	Texture gSnake;
	gSnake.loadFromFile("snakeGreen.png");
	Sprite p2;
	p2.setTexture(gSnake);
	p2.setPosition(800, 500);

	// Hacker
	Texture hack;
	hack.loadFromFile("hackladder.jpg");
	Sprite hacker;
	hacker.setTexture(hack);
	hacker.setPosition(50, 200);
	Sprite hacker2;
	hacker2.setTexture(hack);
	hacker2.setPosition(900, 200);

	//board begins at (350, 50)
	int bArray[10][10];

	bool gameOn = false;
	bool startScreen = true;
	std::string mode = "none";

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}

		window.clear(Color::White);

		while (startScreen == true) {
			window.draw(startText);
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::C)) {
				mode = "classic";
				startScreen = false;
			}
			else if(Keyboard::isKeyPressed(Keyboard::R)) {
				mode = "random";
				startScreen = false;
			}

			// create board (classic or random)
			if (startScreen == false) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						if (mode == "random") {
							unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
							std::mt19937 generator(seed);
							int randNum = generator() % 3;
							if (randNum == 1) {
								bArray[i][j] = 1;
							}
							else if (randNum == 2) {
								bArray[i][j] = 2;
							}
							else {
								bArray[i][j] = 0;
							}
						}
						else {
							if ((i * j) % 3 == 1) {
								bArray[i][j] = 1;
							}
							else if ((i * j) % 3 == 2) {
								bArray[i][j] = 2;
							}
							else {
								bArray[i][j] = 0;
							}
						}
					}
				}
			}
		}

		gameOn = false;

		// Draw board
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				RectangleShape temp(Vector2f(50, 50));
				int tempNum = (rand() % 3 + 1);
				if (bArray[i][j] == 0) {
					temp.setFillColor(Color(75, 75, 200, 200)); //blue
					gameOn = true;
				}
				else if (bArray[i][j] == 1) {
					temp.setFillColor(Color(200, 50, 50, 200)); //red
				}
				else {
					temp.setFillColor(Color(75, 200, 75, 200)); //green
				}
				temp.setOutlineColor(Color::White);
				temp.setOutlineThickness(2);
				temp.setPosition((i * 50) + 350, (j * 50) + 50);
				window.draw(temp);
			}
		}

		//calculate score 
		if (scoresCalculated == false) {
			p1Score = 0;
			p2Score = 0;
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (bArray[i][j] == 1) {
						p1Score++;
					}
					else if (bArray[i][j] == 2) {
						p2Score++;
					}
				}
			}
		}

		//check if dead
		if (dead == true) {
			gameOn = false;
			if (p1Turn) {
				p2Score = 0;
			}
			else {
				p1Score = 0;
			}
		}

		//ending screen
		if (gameOn == false){
			if (p1Score > p2Score) {
				midText.setString("Player 1 Wins!");
			}
			else if (p1Score < p2Score) {
				midText.setString("Player 2 Wins!");
			}
			else {
				midText.setString("Nobody Wins!");
			}
			scoresCalculated = true;
		}

		// BIG GAME LOOP
		if (gameOn == true) {

			//P1 get moves
			if (p1Turn == true) {
				if (Keyboard::isKeyPressed(Keyboard::Space) && !turnStarted) {
					//numMoves = (rand() % 6 + 1);
					numMoves = 5;
					turnStarted = true;
				}
				if (turnStarted == true) {
					midText.setString("Moves Remaining: " + std::to_string(numMoves));
				}
			}
			// P1 movement
			if (p1Turn == true && numMoves != 0) {
				if (Keyboard::isKeyPressed(Keyboard::Left) && (p1.getPosition().x > 350))
				{
					p1.setPosition(p1.getPosition().x - 50, p1.getPosition().y);
					numMoves--;
					int iPos = (p1.getPosition().x - 350) / 50; //update bArray
					int jPos = (p1.getPosition().y - 50) / 50;
					if (bArray[iPos][jPos] == 0) {
						unique = true;
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && (p1.getPosition().x < 800))
				{
					p1.setPosition(p1.getPosition().x + 50, p1.getPosition().y);
					numMoves--;
					int iPos = (p1.getPosition().x - 350) / 50; //update bArray
					int jPos = (p1.getPosition().y - 50) / 50;
					if (bArray[iPos][jPos] == 0) {
						unique = true;
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) && (p1.getPosition().y > 50))
				{
					p1.setPosition(p1.getPosition().x, p1.getPosition().y - 50);
					numMoves--;
					int iPos = (p1.getPosition().x - 350) / 50; //update bArray
					int jPos = (p1.getPosition().y - 50) / 50;
					if (bArray[iPos][jPos] == 0) {
						unique = true;
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && (p1.getPosition().y < 500))
				{
					p1.setPosition(p1.getPosition().x, p1.getPosition().y + 50);
					numMoves--;
					int iPos = (p1.getPosition().x - 350) / 50; //update bArray
					int jPos = (p1.getPosition().y - 50) / 50;
					if (bArray[iPos][jPos] == 0) {
						unique = true;
					}
				}
				if (numMoves == 0) // check if last move was played
				{
					turnDone = true;
					if (unique == false) {
						gameOn = false;
						if (p1Turn) {
							dead = true;
						}
						else {
							dead = true;
						}
					}
				}
				int iPos = (p1.getPosition().x - 350) / 50; //update bArray
				int jPos = (p1.getPosition().y - 50) / 50;
				bArray[iPos][jPos] = 1;
			}

			//P2 get moves
			if (p1Turn == false) {
				if (Keyboard::isKeyPressed(Keyboard::Space) && !turnStarted) {
					//numMoves = (rand() % 6 + 1);
					numMoves = 5;
					turnStarted = true;
				}
				if (turnStarted == true) {
					midText.setString("Moves Remaining: " + std::to_string(numMoves));
				}
			}
			//P2 movement
			if (p1Turn == false && numMoves != 0) {
				if (Keyboard::isKeyPressed(Keyboard::Left) && (p1.getPosition().x > 350))
				{
					p2.setPosition(p2.getPosition().x - 50, p2.getPosition().y);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) && (p2.getPosition().x < 800))
				{
					p2.setPosition(p2.getPosition().x + 50, p2.getPosition().y);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) && (p2.getPosition().y > 50))
				{
					p2.setPosition(p2.getPosition().x, p2.getPosition().y - 50);
					numMoves--;
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) && (p2.getPosition().y < 500))
				{
					p2.setPosition(p2.getPosition().x, p2.getPosition().y + 50);
					numMoves--;
				}
				if (numMoves == 0) // check if last move was played
				{
					turnDone = true;
				}
				int iPos = (p2.getPosition().x - 350) / 50;
				int jPos = (p2.getPosition().y - 50) / 50;
				bArray[iPos][jPos] = 2;
			}

			//update turn for next loop
			if (turnDone == true)
			{
				p1Turn = not p1Turn;
				turnDone = false;
				turnStarted = false;
				unique = false;
			}

			//update prompts for next turn
			if (p1Turn && !turnStarted) {
				midText.setString("P1 Press Space");
			}
			if (!p1Turn && !turnStarted) {
				midText.setString("P2 Press Space");
			}

			sleep(seconds(.1));
		}

		//update scores
		p1Text.setString("P1 Score: " + std::to_string(p1Score));
		p2Text.setString("P2 Score: " + std::to_string(p2Score));

		//draw and display
		window.draw(p1);
		window.draw(p2);
		window.draw(midText);
		window.draw(hacker);
		window.draw(hacker2);
		window.draw(p1Text);
		window.draw(p2Text);
		window.display();
	}

	return 0;
}

*/