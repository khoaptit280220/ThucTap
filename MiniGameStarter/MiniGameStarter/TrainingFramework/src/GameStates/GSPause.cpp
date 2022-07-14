#include "GSPause.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"

GSPause::GSPause() {}
GSPause::~GSPause() {}

void GSPause::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button resume
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	std::shared_ptr<GameButton> button_resume = std::make_shared<GameButton>(model, shader, texture);
	button_resume->Set2DPosition(200, 345);
	button_resume->SetSize(55, 55);
	button_resume->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button_resume);

	//button replay
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	std::shared_ptr<GameButton>  button_replay = std::make_shared<GameButton>(model, shader, texture);
	button_replay->Set2DPosition(200, 445);
	button_replay->SetSize(55, 55);
	button_replay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button_replay);
	
	//button setting
	texture = ResourceManagers::GetInstance()->GetTexture("btn_settings.tga");
	std::shared_ptr<GameButton> button_setting = std::make_shared<GameButton>(model, shader, texture);
	button_setting->Set2DPosition(200, 645);
	button_setting->SetSize(55, 55);
	button_setting->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OPTION);
		});
	m_listButton.push_back(button_setting);
	//title resume
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_text_resume = std::make_shared< Text>(shader, font, "Resume", Vector4(0.5f, 0.5f, 0.0f, 1.0f), 1.0f);
	m_text_resume->Set2DPosition(Vector2(165, 395));
	// tile replay
	m_text_replay = std::make_shared< Text>(shader, font, "Replay", Vector4(0.5f, 0.5f, 0.0f, 1.0f), 1.0f);
	m_text_replay->Set2DPosition(Vector2(165, 495));
	
	// title setting
	m_text_setting = std::make_shared< Text>(shader, font, "Setting", Vector4(0.5f, 0.5f, 0.0f, 1.0f), 1.0f);
	m_text_setting->Set2DPosition(Vector2(160, 695));
}

void GSPause::Exit()
{
}


void GSPause::Pause()
{
}

void GSPause::Resume()
{
}


void GSPause::HandleEvents()
{
}

void GSPause::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPause::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPause::HandleMouseMoveEvents(int x, int y)
{
}

void GSPause::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPause::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_text_resume->Draw();
	m_text_replay->Draw();
	m_text_setting->Draw();
	
}