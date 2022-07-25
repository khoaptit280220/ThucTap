#pragma once
#include "GameStateBase.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;

class GSPause :
	public GameStateBase
{
private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_text_resume;
	std::shared_ptr<Text>		m_text_replay;
	std::shared_ptr<Text>		m_text_HighScore;
	std::shared_ptr<Text>		m_text_setting;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
public:
	GSPause();
	~GSPause();

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

};

