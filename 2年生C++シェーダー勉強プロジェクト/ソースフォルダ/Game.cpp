//
// Game.cpp
//
#include "pch.h"
#include "Game.h"
#include <DirectXMath.h>

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Game::Game()
{
	//デバイスリソースクラスの作成
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
	for (auto i : m_explosionEffects)
	{
		SAFE_DELETE(i);
	}
}

/// <summary>
/// 実行に必要なDirect3Dリソースを初期化する
/// </summary>
/// <param name="window">ウィンドウ情報</param>
/// <param name="width">画面幅</param>
/// <param name="height">画面高さ</param>
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();


	// TODO: デフォルトの可変タイムステップモード以外が必要な場合は、タイマー設定を変更してください
    // 例えば、60FPS固定のタイムステップ更新ロジックの場合、次のように記述します
    /*
	m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	EffectManager* e = new EffectManager();
	e->Create(m_deviceResources.get(), L"Resources\\Textures\\karaageExplosion_1.png", 100);
	e->SetRenderState(m_camera, m_view, m_proj);
	e->Initialize(60, Vector3(0, 0, 0));
	e->SetActive(false);

	m_explosionEffects.push_back(e);

}

#pragma region Frame Update
/// <summary>
/// 基本的なゲームループを実行する関数
/// </summary>
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

/// <summary>
/// シーンの更新関数
/// </summary>
/// <param name="timer">経過時間を知らせるタイマー</param>
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

	// 入力クラスの更新
	System::InputManager::GetInstance().Update();

	// TODO: ゲームロジックをここに記述する
    elapsedTime;
	Mouse::ButtonStateTracker m = System::InputManager::GetInstance().GetMouseTracker();


	if (m.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		int mx = System::InputManager::GetInstance().GetMousePosX();
		int my = System::InputManager::GetInstance().GetMousePosY();

		Vector3 v = CalcScreenToWorld(mx, my, 0.0f, 1280, 720, m_view, m_proj);
		v *= 50;
		v.z = 0.0f;
	

		for (auto i : m_explosionEffects)
		{
			if (i->IsActive() == false)
			{
				i->SetRenderState(m_camera, m_view, m_proj);
				i->Initialize(60, Vector3(v.x, v.y, 0));

				break;
			}
			if (i == m_explosionEffects[m_explosionEffects.size() - 1])
			{
				EffectManager* e = new EffectManager();
				e->Create(m_deviceResources.get(), L"Resources\\Textures\\karaageExplosion_2.png", 100);
				e->SetRenderState(m_camera, m_view, m_proj);
				e->Initialize(5, Vector3(v.x, v.y, 0));
				m_explosionEffects.push_back(e);
				break;
			}
		}



	}

	for (auto i : m_explosionEffects)
	{
		if (!i)continue;
		if (i->IsActive() == false)continue;
		i->Update(timer);
	}
}
#pragma endregion

#pragma region Frame Render
/// <summary>
/// シーンの描画関数
/// </summary>
void Game::Render()
{
    // 最初の更新の前に描画をしないでください
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    ID3D11DeviceContext1* context = m_deviceResources->GetD3DDeviceContext();

    // TODO: 描画処理をここに記述してください
    context;

	for (auto i : m_explosionEffects)
	{
		if (!i)continue;
		if (i->IsActive() == false)continue;

		i->Render();
	}
	

    m_deviceResources->PIXEndEvent();

    // レンダリングされたフレームの表示
    m_deviceResources->Present();
}

// バックバッファーをクリアするヘルパメソッド
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // ビューのリセット
    ID3D11DeviceContext1* context = m_deviceResources->GetD3DDeviceContext();
    ID3D11RenderTargetView* renderTarget = m_deviceResources->GetRenderTargetView();
    ID3D11DepthStencilView* depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::Black);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// ここではビューポートを設定しない予定
	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// メッセージハンドラー
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// プロパティ
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: 希望の画面サイズに変更する (最小の画面サイズは 320x200).
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
/// <summary>
/// デバイスに依存するリソースの作成関数
/// </summary>
void Game::CreateDeviceDependentResources()
{
	ID3D11Device1* device = m_deviceResources->GetD3DDevice();

	// TODO: ここでデバイス依存のオブジェクトを初期化します（ウィンドウサイズに依存しません）
	RECT outputSize = m_deviceResources->GetOutputSize();
	UINT backBufferWidth = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize.bottom - outputSize.top, 1);

	//コモンステートの作成
	//m_states = std::make_unique<CommonStates>(device);

	//m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_deviceResources->GetD3DDeviceContext());

	m_camera = Vector3(0, 0, 5);

	m_view = Matrix::CreateLookAt(m_camera, Vector3::Zero, Vector3::UnitY);
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(backBufferWidth) / float(backBufferHeight), 0.1f, 1000.f);
}


//　ウィンドウのサイズ変更イベントで変更されるすべてのメモリリソースを割り当てる関数
void Game::CreateWindowSizeDependentResources()
{
    // TODO: ウィンドウサイズに依存するオブジェクトの初期化を行う
	
}

void Game::OnDeviceLost()
{
	// TODO:ここでDirect3Dのリソース解放を記述してください
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}

void Game::ChangeFullscreen(BOOL flag)
{
	m_deviceResources->GetSwapChain()->SetFullscreenState(flag, NULL);
}

/// <summary>
/// 各種Direct3Dオブジェクトの取得関数
/// </summary>
/// <returns></returns>
ID3D11Device* Game::GetDevice()
{
	return m_deviceResources->GetD3DDevice();
}
ID3D11DeviceContext* Game::GetContext()
{
	return m_deviceResources->GetD3DDeviceContext();
}
DirectX::CommonStates* Game::GetCommonStates()
{
	return m_states.get();
}
DirectX::SpriteBatch* Game::GetSpriteBatch()
{
	return m_spriteBatch.get();
}

DirectX::SimpleMath::Vector3 Game::CalcScreenToWorld(int sx, int sy, float fz, int Screen_W, int Screen_H, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//各行列の逆行列を算出
	Matrix InvView, InvProj, vP, InvViewPort;

	InvView = XMMatrixInverse(nullptr,view);
	InvProj = XMMatrixInverse(nullptr, proj);
	vP = Matrix::Identity;

	vP._11 = Screen_W / 2.0f;
	vP._22 = -Screen_H / 2.0f;
	vP._41 = Screen_W / 2.0f;
	vP._42 = Screen_H / 2.0f;
	InvViewPort = XMMatrixInverse(nullptr, vP);

	Matrix tmp;
	InvViewPort *= InvProj; InvViewPort *= InvView;
	tmp = InvViewPort;

	//Vector3 v = SimpleMath::Vector3::Transform(Vector3(sx, sy, fz), tmp);
	Vector3 v = XMVector3TransformCoord(Vector3(sx, sy, fz), tmp);
	return v;
}

#pragma endregion
