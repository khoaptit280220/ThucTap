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
	texture = ResourceManagers::GetInstance()->GetTexture("obstacleKhoa.tga");
	m_obstacle11 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle12 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle11->SetSize(160, 70);
	m_obstacle12->SetSize(160, 70);
	m_obstacle.push_back(m_obstacle11);
	m_obstacle.push_back(m_obstacle12);

	texture = ResourceManagers::GetInstance()->GetTexture("obstacle2Khoa.tga");
	m_obstacle21 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle22 = std::make_shared<Sprite2D>(model, shader, texture);
	m_obstacle21->SetSize(160, 70);
	m_obstacle22->SetSize(160, 70);
	m_obstacle.push_back(m_obstacle21);
	m_obstacle.push_back(m_obstacle22);

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
	coin->SetSize(50, 50);
	m_coin.push_back(coin);
	coin1 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	coin1->SetSize(50, 50);
	m_coin1.push_back(coin1);
	coin2 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	coin2->SetSize(50, 50);
	m_coin2.push_back(coin2);
	coin3 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	coin3->SetSize(50, 50);
	m_coin3.push_back(coin3);

	m_KeyPress = 0;
	sum = 0;
}

void GSPlay::Exit()
{
}

bool GSPlay::Check_collision()
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
	y_bg1 = y_bg1 - 50 * deltaTime;
	if (y_bg1 < -Globals::screenHeight / 2) {
		y_bg1 += 2 * Globals::screenHeight;
	}
	m_background1->Set2DPosition(x_bg, y_bg1);
		
	y_bg2 = y_bg2 - 50 * deltaTime;
	if (y_bg2 < -Globals::screenHeight / 2) {
		y_bg2 += 2 * Globals::screenHeight;
	}
	m_background2->Set2DPosition(x_bg, y_bg2);
	
	 //move ob
	 if (y_ob1 < Globals::screenHeight + 35) {
	    y_ob1 += 50 * deltaTime;
		m_obstacle11->Set2DPosition(x_ob1, y_ob1);
		if(x_ob1 > 320) coin->Set2DPosition(x_ob1 - 320, y_ob1);
		else coin->Set2DPosition(x_ob1 + 160, y_ob1);
	 }
	 else {
		 y_ob1 = -35;
		 isRandomX1 = true;
		 if (isRandomX1) {
			 isRandomX1 = false;
			 int index = 0 + rand() % listPosXObstacle.size();
			 x_ob1 = listPosXObstacle[index] + x_ob;
		 }
		 m_obstacle11->Set2DPosition(x_ob1, y_ob1);
	 }

	 if (y_ob2 < Globals::screenHeight + 35) {
		 y_ob2 += 50 * deltaTime;
		 if (y_ob2 == -35) {
			 int index = 0 + rand() % listPosXObstacle.size();
			 x_ob2 = listPosXObstacle[index] + x_ob;
		 }
		 m_obstacle21->Set2DPosition(x_ob2, y_ob2);
		 if (x_ob2 > 320) coin1->Set2DPosition(x_ob2 - 320, y_ob2);
		 else coin1->Set2DPosition(x_ob2 + 160, y_ob2);
	 }
	 else {
		 y_ob2 = -35;
		 isRandomX2 = true;
		 if (isRandomX2) {
			 isRandomX2 = false;
			 int index = 0 + rand() % listPosXObstacle.size();
			 x_ob2 = listPosXObstacle[index] + x_ob;
		 }
		 m_obstacle21->Set2DPosition(x_ob2, y_ob2);
	 }

	 if (y_ob3 < Globals::screenHeight + 35) {
		 y_ob3 += 50 * deltaTime;
		 if (y_ob3 == -35) {
			 int index = 0 + rand() % listPosXObstacle.size();
			 x_ob3 = listPosXObstacle[index] + x_ob;
		 }
		 m_obstacle22->Set2DPosition(x_ob3, y_ob3);
		 if (x_ob3 > 320) coin2->Set2DPosition(x_ob3 - 160, y_ob3);
		 else coin2->Set2DPosition(x_ob3 + 160, y_ob3);
	 }
	 else {
		 y_ob3 = -35;
		 isRandomX3 = true;
		 if (isRandomX3) {
			 isRandomX3 = false;
			 int index = 0 + rand() % listPosXObstacle.size();
			 x_ob3 = listPosXObstacle[index] + x_ob;
		 }
		 m_obstacle22->Set2DPosition(x_ob3, y_ob3);
		 //if (x_ob3 > 320) coin1->Set2DPosition(x_ob3 - 160, y_ob3);
		 //else coin1->Set2DPosition(x_ob3 + 160, y_ob3);
	 }
	 
	 if (y_ob4 < Globals::screenHeight + 35) {
		 y_ob4 += 50 * deltaTime;
		 if (y_ob4 == -35) {
			 int index = 0 + rand() % listPosXObstacle.size();
			 x_ob4 = listPosXObstacle[index] + x_ob;
		 }
		 m_obstacle12->Set2DPosition(x_ob4, y_ob4);
		 if (x_ob4 > 320) coin3->Set2DPosition(x_ob4 - 160, y_ob4);
		 else coin3->Set2DPosition(x_ob4 + 160, y_ob4);
	 }
	 else {
		 y_ob4 = -35;
		 isRandomX4 = true;
		 if (isRandomX4) {
			 isRandomX4 = false;
			 int index = 0 + rand() % listPosXObstacle.size();
			 x_ob4 = listPosXObstacle[index] + x_ob;
		 }
		 m_obstacle12->Set2DPosition(x_ob4, y_ob4);
	 }
	 
	 //Handle Key event move fish
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
	for (auto it : m_coin1)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_coin2)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_coin3)
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
	for (auto it : m_coin1)
	{
		it->Draw();
	}
	for (auto it : m_coin2)
	{
		it->Draw();
	}
	for (auto it : m_coin3)
	{
		it->Draw();
	}
}