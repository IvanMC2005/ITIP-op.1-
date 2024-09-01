#include <iostream>
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cmath>
#include <string>
using namespace sf;
using namespace std;
using namespace sf;
int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "New");

	Vector2u size = window.getSize();
	VertexArray graph(LineStrip, size.x + 1);
	float  x0 = size.x / 2, x, y, x1, y1;

	float y0 = size.y / 2, i = 0;

	float scale = 50; // начальный масштаб графика
	float scale_speed = 0.2; // скорость масштабирования
	float e = 2.7182818;
	float low_border = -5; // нижняя граница диапазона
	float high_border = 3; // верхняя граница диапазона
	// описываем координатные оси
	RectangleShape OoX(Vector2f(12 * scale, 1));	
	OoX.setFillColor(Color::Black);
	OoX.setPosition(x0 - 6*scale, y0);
	RectangleShape OoY(Vector2f(1, 12 * scale));
	OoY.setFillColor(Color::Black);
	OoY.setPosition(x0, y0 - 6*scale);
	// описываем стрелки, задающие направление осям
	RectangleShape arrows[4];
	for (int i = 0; i < 4; i++)
	{
		arrows[i].setSize(Vector2f(1, 20));
		arrows[i].setFillColor(Color::Black);
	}
	arrows[0].setRotation(30);
	arrows[1].setRotation(-30);
	arrows[2].setRotation(120);
	arrows[3].setRotation(60);
	CircleShape centre(3);
	centre.setFillColor(Color::Red);
	centre.setPosition(x0 - 1, y0 - 1);
	// задаём шрифт для текста и сам текст (подписи осей, едичный отрезок)
	Font font;
	font.loadFromFile("C://C++//ITIP5_12//x64//Debug//Pwodissey.ttf");
	Text X("X", font, 20);
	Text Y("Y", font, 20);
	Text single("1", font, 20);
	Text zero("0", font, 20);
	zero.setFillColor(Color::Black);
	X.setFillColor(Color::Black);
	Y.setFillColor(Color::Black);
	single.setFillColor(Color::Black);
	// задаём деления на координатной плоскости
	RectangleShape grades[20];
	for (int i = 0; i < 20; i++)
	{
		grades[i].setSize(Vector2f(1, 20));
		grades[i].setFillColor(Color::Black);
	}
	while (window.isOpen())
	{
		// задаём положение и размер всем объектам, зависящим от масштаба
		OoX.setSize(Vector2f(12 * scale, 1));
		OoY.setSize(Vector2f(1, 12 * scale));
		OoX.setPosition(x0 - 6 * scale, y0);
		OoY.setPosition(x0, y0 - 6 * scale);
		arrows[0].setPosition(x0, y0 - 6 * scale);
		arrows[1].setPosition(x0, y0 - 6 * scale);
		arrows[2].setPosition(x0 + 6 * scale, y0);
		arrows[3].setPosition(x0 + 6 * scale, y0);
		X.setPosition(x0 + 6 * scale + 2, y0 + 2);
		zero.setPosition(x0 + 3, y0 + 3);
		Y.setPosition(x0 - 30, y0 - 6 * scale);
		single.setPosition(x0 + scale + 2, y0 + 3);
		for (int i = 0; i < 20; i++)
		{
			if (i < 10)
				if (i < 5)
					if (i == 4)
						grades[i].setPosition(Vector2f((low_border = x0 - (i % 5 + 1) * scale), y0 - 10));
					else
						grades[i].setPosition(Vector2f(x0 - (i % 5 + 1) * scale, y0 - 10));
				else
					if (i == 7)
						grades[i].setPosition(Vector2f((high_border = x0 + (i % 5 + 1) * scale), y0 - 10));
					else
						grades[i].setPosition(Vector2f(x0 + (i % 5 + 1) * scale, y0 - 10));
			else
			{
				grades[i].setRotation(90);
				if (i < 15)
					grades[i].setPosition(Vector2f(x0 + 10, y0 - (i % 5 + 1) * scale));
				else 
					grades[i].setPosition(Vector2f(x0 + 10, y0 + (i % 5 + 1) * scale));
			}
		}
		graph.clear(); // очищаем очередь точек перед переотрисовкой графика
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Subtract))	
			if (scale < 15)
			{
				scale = 15;
			}
			else
				scale -= scale_speed;	
		if (Keyboard::isKeyPressed(Keyboard::Add))
			if (scale < 5000)
				scale += scale_speed;
		window.clear(Color::White);
		// задаём точки графика функции и помещаем в VertexArray
		for (i = low_border - x0; i < high_border - x0; i++)
		{
			x = i / scale;
				
			y = (1 / e*e) / (x - 5);
			x1 = x0 + x * scale;
			y1 = y0 - y * scale;
			graph.append(Vertex(Vector2f(x1, y1), Color::Red));
		}
		window.draw(single);
		window.draw(zero);
		window.draw(centre);
		window.draw(graph);
		window.draw(OoX);
		window.draw(OoY);
		window.draw(X);
		window.draw(Y);
		for (int i = 0; i < 4; i++)
			window.draw(arrows[i]);
		for (int i = 0; i < 20; i++)
			window.draw(grades[i]);
		window.display();
	}

	return 0;
}