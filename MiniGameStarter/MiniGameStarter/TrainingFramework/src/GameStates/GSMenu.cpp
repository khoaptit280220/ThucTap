#include "GSMenu.h"
#include "Camera.h"
#include "GameConfig.h"
GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), 
	m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	std::string name = "music_bg.wav";
	if (Globals::isMusic == 1) {
		ResourceManagers::GetInstance()->PlaySound(name, true);
	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<GameButton> btnPlay = std::make_shared<GameButton>(model, shader, texture);
	btnPlay->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 - 40);
	btnPlay->SetSize(100, 100);
	btnPlay->SetOnClick([]() {
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
			
		});
	m_listButton.push_back(btnPlay);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton> btnClose = std::make_shared<GameButton>(model, shader, texture);
	btnClose = std::make_shared<GameButton>(model, shader, texture);
	btnClose->Set2DPosition(Globals::screenWidth - 50, 50);
	btnClose->SetSize(50, 50);
	btnClose->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(btnClose);

	//option game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_settings.tga");
	std::shared_ptr<GameButton> btnOption = std::make_shared<GameButton>(model, shader, texture);
	btnOption->Set2DPosition(Globals::screenWidth / 2 , Globals::screenHeight / 2 + 70);
	btnOption->SetSize(60, 60);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		
		});
	m_listButton.push_back(btnOption);

	//CREDIT game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_help.tga");
	std::shared_ptr<GameButton> btnCredit = std::make_shared<GameButton>(model, shader, texture);
	btnCredit->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 + 180);
	btnCredit->SetSize(60, 60);
	btnCredit->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CREDIT);
		
		});
	m_listButton.push_back(btnCredit);

	texture = ResourceManagers::GetInstance()->GetTexture("btn_menu.tga");
	std::shared_ptr<GameButton> btnHightScore = std::make_shared<GameButton>(model, shader, texture);
	btnHightScore = std::make_shared<GameButton>(model, shader, texture);
	btnHightScore->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 + 290);
	btnHightScore->SetSize(60, 60);
	btnHightScore->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_HIGHSCORE);
		});
	m_listButton.push_back(btnHightScore);

	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_textGameName = std::make_shared< Text>(shader, font, "Fish Run", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_textGameName->Set2DPosition(Vector2(100, 220));

	// tile setting
	m_textSetting = std::make_shared< Text>(shader, font, "Setting", Vector4(0.5f, 0.5f, 0.0f, 1.0f), 1.0f);
	m_textSetting->Set2DPosition(Vector2(200, 530));
	//title credit
	m_textCredit = std::make_shared< Text>(shader, font, "Credit", Vector4(0.5f, 0.5f, 0.0f, 1.0f), 1.0f);
	m_textCredit->Set2DPosition(Vector2(210, 640));
	// title highScore
	m_textHighScore = std::make_shared< Text>(shader, font, "HighScore", Vector4(0.5f, 0.5f, 0.0f, 1.0f), 1.0f);
	m_textHighScore->Set2DPosition(Vector2(190, 750));
	
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
	m_textCredit->Draw();
	m_textHighScore->Draw();
	m_textSetting->Draw();
}
