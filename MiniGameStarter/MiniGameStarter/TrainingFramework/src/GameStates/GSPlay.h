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
	int m_KeyPress;

private:
	std::shared_ptr<Sprite2D>	m_background1;
	std::shared_ptr<Sprite2D>	m_background2;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_coin;
	std::list<std::shared_ptr<Sprite2D>>	m_obstacle;
	float x_fish = Globals::screenWidth /2;
	float y_fish = 650;
	float x_bg = Globals::screenWidth / 2;
	float y_bg1 = Globals::screenHeight / 2 - 5;
	float y_bg2 = 3 * Globals::screenHeight / 2 - 5;
	std::shared_ptr<Sprite2D> m_fish;
	std::shared_ptr<Sprite2D> m_obstacle1;
	std::shared_ptr<Sprite2D> m_obstacle2;
	std::shared_ptr<SpriteAnimation>	m_coint;
	bool isPress;
	bool isPressLeft;
};

