#pragma once
#include "GameStateBase.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	void Spawn( );
	int m_KeyPress;
	

private:
	std::shared_ptr<Sprite2D>	m_background1;
	std::shared_ptr<Sprite2D>	m_background2;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_coin;
	std::list<std::shared_ptr<Sprite2D>>	m_obstacle;
	float x_fish = Globals::screenWidth /2;
	float y_fish = 650 + 50;
	float x_bg = Globals::screenWidth / 2;
	float y_bg1 = Globals::screenHeight / 2 - 5;
	float y_bg2 = 3 * Globals::screenHeight / 2 - 5;
	float x_ob1 = (Globals::screenWidth - 480) / 2 + 80;
	float x_ob2 = x_ob1 + 160;
	float x_ob3 = x_ob1 + 320;
	float y_ob1 = 85;
	float y_ob2 = -65;
	float y_ob3 = -215;
	float y_ob4 = -365;
	float sum;
	std::shared_ptr<Sprite2D> m_fish;
	std::shared_ptr<Sprite2D> m_obstacle11;
	std::shared_ptr<Sprite2D> m_obstacle21;
	std::shared_ptr<Sprite2D> m_obstacle12;
	std::shared_ptr<Sprite2D> m_obstacle22;
	std::shared_ptr<Sprite2D> m_obstacle13;
	std::shared_ptr<Sprite2D> m_obstacle23;
	std::shared_ptr<Sprite2D> m_obstacle14;
	std::shared_ptr<Sprite2D> m_obstacle24;
	std::shared_ptr<Sprite2D> m_obsTemp;
	std::shared_ptr<SpriteAnimation> coin;
	std::vector<int> listPosXObstacle;
	bool isPress;
	bool isPressLeft;
	bool isRandomX1 = false;
	bool isRandomX2 = false;
	bool isRandomX3 = false;
};

