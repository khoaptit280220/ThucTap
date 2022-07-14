#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"



GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("backgroundKhoa.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	//fish
	texture = ResourceManagers::GetInstance()->GetTexture("fishKhoa.tga");
	m_fish = std::make_shared<Sprite2D>(model, shader, texture);
	m_fish->Set2DPosition(x_fish, y_fish);
	m_fish->SetSize(100, 150);

	//Obstacle1
	texture = ResourceManagers::GetInstance()->GetTexture("obstacleKhoa1.tga");
	m_obstacle1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle1->Set2DPosition((float)(Globals::screenWidth - 480) / 2 + 80, 85);
	m_obstacle1->SetSize(160, 70);
	m_obstacle.push_back(m_obstacle1);
	
	//Obstacle2
	texture = ResourceManagers::GetInstance()->GetTexture("obstacleKhoa2.tga");
	m_obstacle2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle2->Set2DPosition((float)(Globals::screenWidth - 480) / 2 + 80 + 160 + 160, 85);
	m_obstacle2->SetSize(160, 70);
	m_obstacle.push_back(m_obstacle2);

	

	// button prev
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(200, 25);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	std::shared_ptr<GameButton>  button_pause = std::make_shared<GameButton>(model, shader, texture);
	button_pause->Set2DPosition(425, 25);
	button_pause->SetSize(50, 50);
	button_pause->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PAUSE);
		});
	m_listButton.push_back(button_pause);
	//button replay
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	std::shared_ptr<GameButton>  button_replay = std::make_shared<GameButton>(model, shader, texture);
	button_replay->Set2DPosition(350, 25);
	button_replay->SetSize(50, 50);
	button_replay->SetOnClick([]() {
		
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button_replay);
	
	
	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	//Obstacle Coint
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("coin1.tga");
	std::shared_ptr<SpriteAnimation> coin = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	coin->Set2DPosition((float)(Globals::screenWidth - 480) / 2 + 80 + 160 , 85);
	coin->SetSize(50, 50);
	m_coin.push_back(coin);

	m_KeyPress = 0;
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress |= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress |= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress |= 1 << 2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress |= 1 << 3;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress ^= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	
	/*if (m_KeyPress & KEY_MOVE_LEFT) {
		
		x_fish -= 0.1;
		m_fish->Set2DPosition(x_fish, y_fish);
	}
	else if (m_KeyPress & KEY_MOVE_RIGHT) {	
		
		x_fish += 0.1;	
		m_fish->Set2DPosition(x_fish, y_fish);
	}*/
	
	switch (m_KeyPress)//Handle Key event
	{
	case 1:
		
		x_fish -= 0.1;
		m_fish->Set2DPosition(x_fish, y_fish);
		break;
	case 4:
		
		x_fish += 0.1;
		m_fish->Set2DPosition(x_fish, y_fish);
		break;
	default:
		break;
	}
	
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_coin)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_fish->Draw();
	for (auto it : m_obstacle)
	{
		it->Draw();
	}
	for (auto it : m_coin)
	{
		it->Draw();
	}

}