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
#include <string>
#include<iostream>
#include<fstream>
#include"GSScore.h"
#include "soloud.h"
#include "GameConfig.h"
using namespace std;
GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}

int GSPlay::GetScoreFile(std::string fileName) {
	ifstream f(fileName);
	string maxScore;
	f >> maxScore;
	reverse(maxScore.begin(), maxScore.end());
	long long binarynum = stoi(maxScore);
	int decimalnum = 0, temp = 0, remainder;
	while (binarynum != 0)
	{
		remainder = binarynum % 10;
		binarynum = binarynum / 10;
		decimalnum = decimalnum + remainder * pow(2, temp);
		temp++;
	}
	return (decimalnum - 2) / 5;
	
}
void GSPlay::SetScoreFile(std::string fileName, int Max_score) {
	int temp1 = Max_score * 5 + 2; // tự quy ước
	string s = "";
	while (temp1 != 0) {
		int temp = temp1 % 2;
		temp1 /= 2;
		s += std::to_string(temp);
	}
	ofstream outfile(fileName);
	outfile << s;
}

void GSPlay::Init()
{
	
	listPosXObstacle.push_back(0);
	listPosXObstacle.push_back(160);
	listPosXObstacle.push_back(320);
	score = 0;
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
	texture = ResourceManagers::GetInstance()->GetTexture("fish1.tga");
	m_fish = std::make_shared<Sprite2D>(model, shader, texture);
	m_fish->Set2DPosition(x_fish, y_fish);
	m_fish->SetSize(70, 100);

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
		ResourceManagers::GetInstance()->StopSound("music_bg.wav");
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		
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
		/*ResourceManagers::GetInstance()->StopSound("music_bg.wav");
		if (Globals::isMusic == 1) {
			ResourceManagers::GetInstance()->PlaySound("music_bg.wav", true);
		}*/
		
		});
	m_listButton.push_back(button_replay);

	
	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: " + std::to_string(score), TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	//Obstacle Coint
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("coin1.tga");
	coin1 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	coin1->SetSize(50, 50);
	m_coin1.push_back(coin1);
	m_coin.push_back(m_coin1);
	coin2 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	coin2->SetSize(50, 50);
	m_coin2.push_back(coin2);
	m_coin.push_back(m_coin2);
	coin3 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	coin3->SetSize(50, 50);
	m_coin3.push_back(coin3);
	m_coin.push_back(m_coin3);
	coin4 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	coin4->SetSize(50, 50);
	m_coin4.push_back(coin4);
	m_coin.push_back(m_coin4);

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

bool GSPlay::CheckCollision()
{
	for (auto it : m_obstacle) {
		if ((it->GetPosY() - 95 < y_fish - 30) && (it->GetPosY() + 95 > y_fish + 30 )) {
			if ((it->GetPosX() - 105 < x_fish -30) && (it->GetPosX() + 105 > x_fish +30 )) {
				return true;
			}
		}
	}
	return false;
}

bool GSPlay::CheckCoin1() {
	for (auto it : m_coin1) {
		if ((it->GetPosY() + 20 >= y_fish - 50)  && (it->GetPosY() + 20 < y_fish + 20) ) {
			if ((it->GetPosX() > x_fish - 30) && (it->GetPosX() < x_fish + 30)) {
				return true;
			}
		}
	}
	return false;
}
bool GSPlay::CheckCoin2() {
	for (auto it : m_coin2) {
		if ((it->GetPosY() + 20 >= y_fish - 50) && (it->GetPosY() + 20 < y_fish + 20) ) {
			if ((it->GetPosX() > x_fish - 30) && (it->GetPosX() < x_fish + 30)) {
				return true;
			}
		}
	}
	return false;
}
bool GSPlay::CheckCoin3() {
	for (auto it : m_coin3) {
		if ((it->GetPosY() + 20 >= y_fish - 50) && (it->GetPosY() + 20 < y_fish + 20)) {
			if ((it->GetPosX() > x_fish - 30) && (it->GetPosX() < x_fish + 30)) {
				return true;
			}
		}
	}
	return false;
}
bool GSPlay::CheckCoin4() {
	for (auto it : m_coin4) {
		if ((it->GetPosY() + 20 >= y_fish - 50) && (it->GetPosY() + 20 < y_fish + 20)) {
			if ((it->GetPosX() > x_fish - 30) && (it->GetPosX() < x_fish + 30)) {
				return true;
			}
		}
	}
	return false;
}

void GSPlay::Update(float deltaTime)
{
	if(!CheckCollision())
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
			y_ob1 += speed * deltaTime;
			m_obstacle11->Set2DPosition(x_ob1, y_ob1);
			if (x_ob1 > 320) coin1->Set2DPosition(x_ob1 - 320, y_ob1);
			else coin1->Set2DPosition(x_ob1 + 160, y_ob1);
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
			isDrawCoin1 = true;
		}

		if (y_ob2 < Globals::screenHeight + 35) {
			y_ob2 += speed * deltaTime;
			if (y_ob2 == -35) {
				int index = 0 + rand() % listPosXObstacle.size();
				x_ob2 = listPosXObstacle[index] + x_ob;
			}
			m_obstacle21->Set2DPosition(x_ob2, y_ob2);
			if (x_ob2 > 320) coin2->Set2DPosition(x_ob2 - 320, y_ob2);
			else coin2->Set2DPosition(x_ob2 + 160, y_ob2);
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
			isDrawCoin2 = true;
		}

		if (y_ob3 < Globals::screenHeight + 35) {
			y_ob3 += speed * deltaTime;
			if (y_ob3 == -35) {
				int index = 0 + rand() % listPosXObstacle.size();
				x_ob3 = listPosXObstacle[index] + x_ob;
			}
			m_obstacle22->Set2DPosition(x_ob3, y_ob3);
			if (x_ob3 > 320) coin3->Set2DPosition(x_ob3 - 160, y_ob3);
			else coin3->Set2DPosition(x_ob3 + 160, y_ob3);
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
			isDrawCoin3 = true;
		}

		if (y_ob4 < Globals::screenHeight + 35) {
			y_ob4 += speed * deltaTime;
			if (y_ob4 == -35) {
				int index = 0 + rand() % listPosXObstacle.size();
				x_ob4 = listPosXObstacle[index] + x_ob;
			}
			m_obstacle12->Set2DPosition(x_ob4, y_ob4);
			if (x_ob4 > 320) coin4->Set2DPosition(x_ob4 - 160, y_ob4);
			else coin4->Set2DPosition(x_ob4 + 160, y_ob4);
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
			isDrawCoin4 = true;
		}

		//Handle Key event move fish
		switch (m_KeyPress)
		{
		case 1:
			if (x_fish >= (float)Globals::screenWidth / 6) {
				x_fish -= 150 * deltaTime;
				m_fish->Set2DPosition(x_fish, y_fish);
			}
			break;
		case 4:
			if (x_fish <= 5 * (float)Globals::screenWidth / 6) {
				x_fish += 150 * deltaTime;
				m_fish->Set2DPosition(x_fish, y_fish);
			}
			break;
		default:
			break;
		}

		if (CheckCoin1() && isDrawCoin1) {
			score += 1;
			if (Globals::isSound==1) {
				ResourceManagers::GetInstance()->PlaySound("point.wav", false);
			}
			
			isDrawCoin1 = false;
			m_score->SetText("score: " + std::to_string(score));
		}
		if (CheckCoin2() && isDrawCoin2) {
			score += 1;
			if (Globals::isSound==1) {
				ResourceManagers::GetInstance()->PlaySound("point.wav", false);
			}
			isDrawCoin2 = false;
			m_score->SetText("score: " + std::to_string(score));
		}
		if (CheckCoin3() && isDrawCoin3) {
			score += 1;
			if (Globals::isSound==1) {
				ResourceManagers::GetInstance()->PlaySound("point.wav", false);
			}
			isDrawCoin3 = false;
			m_score->SetText("score: " + std::to_string(score));
		}
		if (CheckCoin4() && isDrawCoin4) {
			score += 1;
			if (Globals::isSound==1) {
				ResourceManagers::GetInstance()->PlaySound("point.wav", false);
			}
			isDrawCoin4 = false;
			m_score->SetText("score: " + std::to_string(score));
		}
		if (score == 3) {
			speed = 60;
		}
		else if (score == 6) {
			speed = 70;
		}
		else if (score == 10) {
			speed = 90;
		}
		else if (score == 13) {
			speed = 100;
		}
		else if (score == 16) {
			speed = 120;
		}
		else if (score == 20) {
			speed = 150;
		}
		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
		for (auto it : m_coin)
		{
			for (auto it : it)
			{
				it->Update(deltaTime);
			}
		}
		
	}

	else 
	{
		
		if (!die) {
			if (Globals::isSound == 1) {
				ResourceManagers::GetInstance()->PlaySound("hit.wav", false);
				ResourceManagers::GetInstance()->PlaySound("die.wav", false);
			}
			
			die = true;
			return;
		}
		m_score->SetText("Game over, Your score: " + std::to_string(score));
		m_score->Set2DPosition(Vector2(75, 300));
		
		if (score > GetScoreFile(ResourceManagers::GetInstance()->m_ScorePath)) {
			SetScoreFile(ResourceManagers::GetInstance()->m_ScorePath, score);
		}	
		if (Globals::isMusic == 1) {
			ResourceManagers::GetInstance()->StopSound("music_bg.wav");
		}
	}
	
}

void GSPlay::Draw()
{
	m_background1->Draw();
	m_background2->Draw();
	m_score->Draw();
	m_fish->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	
	for (auto it : m_obstacle)
	{
		it->Draw();
	}
	if (isDrawCoin1) {
		for (auto it : m_coin1)
		{
			it->Draw();
		}
	}
	if (isDrawCoin2) {
		for (auto it : m_coin2)
		{
			it->Draw();
		}
	}
	if (isDrawCoin3) {
		for (auto it : m_coin3)
		{
			it->Draw();
		}
	}
	if (isDrawCoin4) {
		for (auto it : m_coin4)
		{
			it->Draw();
		}
	}
}