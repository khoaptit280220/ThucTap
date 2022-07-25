#include "GSOption.h"
#include "Camera.h"
GSOption::GSOption() : GameStateBase(StateType::STATE_OPTION),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}


GSOption::~GSOption()
{
}



void GSOption::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// on sound
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga");
	std::shared_ptr<GameButton> btnSound = std::make_shared<GameButton>(model, shader, texture);
	btnSound->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 - 110);
	btnSound->SetSize(70, 70);
	btnSound->SetOnClick([]() {
		
		});
	m_listButton.push_back(btnSound);

	// off sound
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga");
	std::shared_ptr<GameButton> btnOffSound = std::make_shared<GameButton>(model, shader, texture);
	btnOffSound->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 );
	btnOffSound->SetSize(70, 70);
	btnOffSound->SetOnClick([]() {

		});
	m_listButton.push_back(btnOffSound);

	// on music
	texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	std::shared_ptr<GameButton> btnMusic = std::make_shared<GameButton>(model, shader, texture);
	btnMusic->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 + 110);
	btnMusic->SetSize(70, 70);
	btnMusic->SetOnClick([]() {

		});
	m_listButton.push_back(btnMusic);

	// off music
	texture = ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga");
	std::shared_ptr<GameButton> btnOffMusic = std::make_shared<GameButton>(model, shader, texture);
	btnOffMusic->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 + 220);
	btnOffMusic->SetSize(70, 70);
	btnOffMusic->SetOnClick([]() {

		});
	m_listButton.push_back(btnOffMusic);

	// back button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	std::shared_ptr<GameButton> btnPrev = std::make_shared<GameButton>(model, shader, texture);
	btnPrev = std::make_shared<GameButton>(model, shader, texture);
	btnPrev->Set2DPosition(80, 50);
	btnPrev->SetSize(50, 50);
	btnPrev->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(btnPrev);

	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_textGameName = std::make_shared< Text>(shader, font, "Fish Run", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_textGameName->Set2DPosition(Vector2(100, 200));
	
	//title on sound
	m_text_onSound = std::make_shared< Text>(shader, font, "On Sound", Vector4(0.5f, 0.5f, 0.0f, 1.0f), 1.0f);
	m_text_onSound->Set2DPosition(Vector2(Globals::screenWidth / 2 - 55, Globals::screenHeight / 2 - 50));
	
	// tile off sound
	m_text_offSound = std::make_shared< Text>(shader, font, "Off Sound", Vector4(0.5f, 0.5f, 0.0f, 1.0f), 1.0f);
	m_text_offSound->Set2DPosition(Vector2(Globals::screenWidth / 2 - 55, Globals::screenHeight / 2 + 60));

	// title on music
	m_text_onMusic = std::make_shared< Text>(shader, font, "On Music", Vector4(0.5f, 0.5f, 0.0f, 1.0f), 1.0f);
	m_text_onMusic->Set2DPosition(Vector2(Globals::screenWidth / 2 - 55, Globals::screenHeight / 2 + 170));
	
	// title off music
	m_text_offMusic = std::make_shared< Text>(shader, font, "Off Music", Vector4(0.5f, 0.5f, 0.0f, 1.0f), 1.0f);
	m_text_offMusic->Set2DPosition(Vector2(Globals::screenWidth / 2 - 55, Globals::screenHeight / 2 + 280));

	std::string name = "music_bg.wav";
	ResourceManagers::GetInstance()->PlaySound(name);
}

void GSOption::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSOption::Pause()
{
}

void GSOption::Resume()
{
}


void GSOption::HandleEvents()
{
}

void GSOption::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSOption::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSOption::HandleMouseMoveEvents(int x, int y)
{
}

void GSOption::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSOption::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
	m_text_offMusic->Draw();
	m_text_offSound->Draw();
	m_text_onMusic->Draw();
	m_text_onSound->Draw();
}
