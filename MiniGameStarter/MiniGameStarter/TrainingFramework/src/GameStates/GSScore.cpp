#include "GSScore.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include <string>
#include <fstream>

using namespace std;

GSScore::GSScore() {}
GSScore::~GSScore() {}

int GSScore::GetScoreFile(std::string fileName) {
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
void GSScore::Init()
{
	
	std::string text_HighScore = std::to_string(GetScoreFile(ResourceManagers::GetInstance()->m_ScorePath));

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button prev
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	std::shared_ptr<GameButton>  button_prev = std::make_shared<GameButton>(model, shader, texture);
	button_prev->Set2DPosition(50, 50);
	button_prev->SetSize(50, 50);
	button_prev->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		
		});
	m_listButton.push_back(button_prev);


	//title Highest Score

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_text_highScore = std::make_shared< Text>(shader, font, "Highest Score = " + text_HighScore, Vector4(1.0f, 0.3f, 0.0f, 1.0f), 1.2f);
	m_text_highScore->Set2DPosition(Vector2(130, 300));



}

void GSScore::Exit()
{
}


void GSScore::Pause()
{
}

void GSScore::Resume()
{
}


void GSScore::HandleEvents()
{
}

void GSScore::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSScore::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSScore::HandleMouseMoveEvents(int x, int y)
{
}

void GSScore::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSScore::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_text_highScore->Draw();
}