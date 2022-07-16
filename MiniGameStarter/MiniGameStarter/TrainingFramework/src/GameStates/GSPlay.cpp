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
	listPosXObstacle.push_back(0);
	listPosXObstacle.push_back(160);
	listPosXObstacle.push_back(320);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("backgroundKhoa.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_background1->Set2DPosition(x_bg, y_bg1);
	m_background1->SetSize(Globals::screenWidth, Globals::screenHeight);

	m_background2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_background2->Set2DPosition(x_bg, y_bg2);
	m_background2->SetSize(Globals::screenWidth, Globals::screenHeight);

	//fish
	texture = ResourceManagers::GetInstance()->GetTexture("fishKhoa.tga");
	m_fish = std::make_shared<Sprite2D>(model, shader, texture);
	m_fish->Set2DPosition(x_fish, y_fish);
	m_fish->SetSize(100, 150);

	//Obstacle1
	texture = ResourceManagers::GetInstance()->GetTexture("obstacleKhoa1.tga");
	m_obstacle11 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle12 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle13 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle14 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle11->Set2DPosition(x_ob1 , y_ob1);
	m_obstacle12->Set2DPosition(x_ob1, y_ob2);
	m_obstacle13->Set2DPosition(x_ob1, y_ob3);
	m_obstacle14->Set2DPosition(x_ob3, y_ob4);
	m_obstacle11->SetSize(160, 70);
	m_obstacle12->SetSize(160, 70);
	m_obstacle13->SetSize(160, 70);
	m_obstacle14->SetSize(160, 70);
	m_obstacle.push_back(m_obstacle11);
	m_obstacle.push_back(m_obstacle12);
	m_obstacle.push_back(m_obstacle13);
	m_obstacle.push_back(m_obstacle14);

	texture = ResourceManagers::GetInstance()->GetTexture("obstacleKhoa2.tga");
	m_obstacle21 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle22 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle23 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle24 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle21->Set2DPosition(x_ob3, y_ob1);
	m_obstacle22->Set2DPosition(x_ob3, y_ob2);
	m_obstacle23->Set2DPosition(x_ob3, y_ob3);
	m_obstacle24->Set2DPosition(x_ob1, y_ob4);
	m_obstacle21->SetSize(160, 70);
	m_obstacle22->SetSize(160, 70);
	m_obstacle23->SetSize(160, 70);
	m_obstacle24->SetSize(160, 70);
	m_obstacle.push_back(m_obstacle21);
	m_obstacle.push_back(m_obstacle22);
	m_obstacle.push_back(m_obstacle23);
	m_obstacle.push_back(m_obstacle24);


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
	coin = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	coin->Set2DPosition(x_ob2 , y_ob1);
	coin->SetSize(50, 50);
	m_coin.push_back(coin);

	m_KeyPress = 0;
	isPress = false;
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

	//background move
	if (y_bg1 >= -Globals::screenHeight / 2 + 5 ) {
		y_bg1 = y_bg1 - 50 * deltaTime;
		m_background1->Set2DPosition(x_bg, y_bg1);
		
	}
	else {
		y_bg1 = 3 * Globals::screenHeight / 2 - 5;
		m_background1->Set2DPosition(x_bg, y_bg1);
		
	}
	 if (y_bg2 >= -Globals::screenHeight / 2 + 5) {
		y_bg2 = y_bg2 - 50 * deltaTime;
		m_background2->Set2DPosition(x_bg, y_bg2);
	}
	else  {
		y_bg2 = 3 * Globals::screenHeight / 2 - 5;
		m_background2->Set2DPosition(x_bg, y_bg2 );
	}

	 //move ob
	 if (y_ob1 < 640) {
		 y_ob1 += 30 * deltaTime;
		 m_obstacle11->Set2DPosition(x_ob1, y_ob1);
		 m_obstacle21->Set2DPosition(x_ob3, y_ob1);
		 coin->Set2DPosition(x_ob2, y_ob1);
	 }
	 else {
		 y_ob1 = 85;
		 m_obstacle11->Set2DPosition(x_ob1, y_ob1);
		 m_obstacle21->Set2DPosition(x_ob3, y_ob1);
		 coin->Set2DPosition(x_ob2, y_ob1);
	 }
	 if (y_ob2 < 640) {
		 y_ob2 += 30 * deltaTime;
		 m_obstacle12->Set2DPosition(x_ob1, y_ob2);
		 m_obstacle22->Set2DPosition(x_ob3, y_ob2);
		 coin->Set2DPosition(x_ob2, y_ob1);
	 }
	 else {
		 y_ob2 = 85;
		 m_obstacle12->Set2DPosition(x_ob1, y_ob2);
		 m_obstacle22->Set2DPosition(x_ob3, y_ob2);
		 coin->Set2DPosition(x_ob2, y_ob1);
	 }
	 if (y_ob3 < 640) {
		 y_ob3 += 30 * deltaTime;
		 m_obstacle13->Set2DPosition(x_ob1, y_ob3);
		 m_obstacle23->Set2DPosition(x_ob3, y_ob3);
		 coin->Set2DPosition(x_ob2, y_ob1);
	 }
	 else {
		 y_ob3 = 85;
		 m_obstacle13->Set2DPosition(x_ob1, y_ob3);
		 m_obstacle23->Set2DPosition(x_ob3, y_ob3);
		 coin->Set2DPosition(x_ob2, y_ob1);
	 }
	 if (y_ob4 < 640) {
		 y_ob4 += 30 * deltaTime;
		 m_obstacle14->Set2DPosition(x_ob1, y_ob4);
		 m_obstacle24->Set2DPosition(x_ob3, y_ob4);
		 coin->Set2DPosition(x_ob2, y_ob1);
	 }
	 else {
		 y_ob4 = 85;
		 m_obstacle14->Set2DPosition(x_ob1, y_ob4);
		 m_obstacle24->Set2DPosition(x_ob3, y_ob4);
		 coin->Set2DPosition(x_ob2, y_ob1);
	 }
	 
	 //Handle Key event
	switch (m_KeyPress)
	{
	case 1:
		if (x_fish > (float)Globals::screenWidth / 6) {
			x_fish -= 100 * deltaTime;
			m_fish->Set2DPosition(x_fish, y_fish);
		}
		break;
	case 4:
		if (x_fish <  5 * (float)Globals::screenWidth / 6) {
			x_fish += 100 * deltaTime;
			m_fish->Set2DPosition(x_fish, y_fish);
		}
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
	m_background1->Draw();
	m_background2->Draw();
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