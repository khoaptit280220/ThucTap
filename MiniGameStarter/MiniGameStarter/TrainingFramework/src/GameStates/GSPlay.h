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
	bool	Check_collision();
	int m_KeyPress;
	

private:
	std::shared_ptr<Sprite2D>	m_background1;
	std::shared_ptr<Sprite2D>	m_background2;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_coin;
	std::list<std::shared_ptr<SpriteAnimation>>	m_coin1;
	std::list<std::shared_ptr<SpriteAnimation>>	m_coin2;
	std::list<std::shared_ptr<SpriteAnimation>>	m_coin3;
	std::list<std::shared_ptr<Sprite2D>>	m_obstacle;
	float x_fish = Globals::screenWidth /2;
	float y_fish = 650 + 50;
	float x_bg = Globals::screenWidth / 2;
	float y_bg1 = Globals::screenHeight / 2 ;
	float y_bg2 = 3 * Globals::screenHeight / 2 ;
	float x_ob = (Globals::screenWidth - 480) / 2 + 80;
	float x_ob1 = (Globals::screenWidth - 480) / 2 + 80;
	float x_ob2 = x_ob1 + 160;
	float x_ob3 = x_ob1 + 320;
	float x_ob4 = x_ob1 + 160;
	float y_ob1 = 85;
	float y_ob2 = -125;
	float y_ob3 = -335;
	float y_ob4 = -555;
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
	std::shared_ptr<SpriteAnimation> coin1;
	std::shared_ptr<SpriteAnimation> coin2;
	std::shared_ptr<SpriteAnimation> coin3;
	std::vector<int> listPosXObstacle;
	bool isRandomOb1 = false;
	bool isRandomOb2 = false;
	bool isRandomOb3 = false;
	bool isRandomX1 = false;
	bool isRandomX2 = false;
	bool isRandomX3 = false;
	bool isRandomX4 = false;
};

