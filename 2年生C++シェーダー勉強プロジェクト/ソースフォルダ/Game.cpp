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
/// �R���X�g���N�^
/// </summary>
Game::Game()
{
	//�f�o�C�X���\�[�X�N���X�̍쐬
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
/// ���s�ɕK�v��Direct3D���\�[�X������������
/// </summary>
/// <param name="window">�E�B���h�E���</param>
/// <param name="width">��ʕ�</param>
/// <param name="height">��ʍ���</param>
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();


	// TODO: �f�t�H���g�̉σ^�C���X�e�b�v���[�h�ȊO���K�v�ȏꍇ�́A�^�C�}�[�ݒ��ύX���Ă�������
    // �Ⴆ�΁A60FPS�Œ�̃^�C���X�e�b�v�X�V���W�b�N�̏ꍇ�A���̂悤�ɋL�q���܂�
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
/// ��{�I�ȃQ�[�����[�v�����s����֐�
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
/// �V�[���̍X�V�֐�
/// </summary>
/// <param name="timer">�o�ߎ��Ԃ�m�点��^�C�}�[</param>
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

	// ���̓N���X�̍X�V
	System::InputManager::GetInstance().Update();

	// TODO: �Q�[�����W�b�N�������ɋL�q����
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
/// �V�[���̕`��֐�
/// </summary>
void Game::Render()
{
    // �ŏ��̍X�V�̑O�ɕ`������Ȃ��ł�������
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    ID3D11DeviceContext1* context = m_deviceResources->GetD3DDeviceContext();

    // TODO: �`�揈���������ɋL�q���Ă�������
    context;

	for (auto i : m_explosionEffects)
	{
		if (!i)continue;
		if (i->IsActive() == false)continue;

		i->Render();
	}
	

    m_deviceResources->PIXEndEvent();

    // �����_�����O���ꂽ�t���[���̕\��
    m_deviceResources->Present();
}

// �o�b�N�o�b�t�@�[���N���A����w���p���\�b�h
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // �r���[�̃��Z�b�g
    ID3D11DeviceContext1* context = m_deviceResources->GetD3DDeviceContext();
    ID3D11RenderTargetView* renderTarget = m_deviceResources->GetRenderTargetView();
    ID3D11DepthStencilView* depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::Black);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// �����ł̓r���[�|�[�g��ݒ肵�Ȃ��\��
	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// ���b�Z�[�W�n���h���[
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

// �v���p�e�B
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: ��]�̉�ʃT�C�Y�ɕύX���� (�ŏ��̉�ʃT�C�Y�� 320x200).
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
/// <summary>
/// �f�o�C�X�Ɉˑ����郊�\�[�X�̍쐬�֐�
/// </summary>
void Game::CreateDeviceDependentResources()
{
	ID3D11Device1* device = m_deviceResources->GetD3DDevice();

	// TODO: �����Ńf�o�C�X�ˑ��̃I�u�W�F�N�g�����������܂��i�E�B���h�E�T�C�Y�Ɉˑ����܂���j
	RECT outputSize = m_deviceResources->GetOutputSize();
	UINT backBufferWidth = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize.bottom - outputSize.top, 1);

	//�R�����X�e�[�g�̍쐬
	//m_states = std::make_unique<CommonStates>(device);

	//m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_deviceResources->GetD3DDeviceContext());

	m_camera = Vector3(0, 0, 5);

	m_view = Matrix::CreateLookAt(m_camera, Vector3::Zero, Vector3::UnitY);
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(backBufferWidth) / float(backBufferHeight), 0.1f, 1000.f);
}


//�@�E�B���h�E�̃T�C�Y�ύX�C�x���g�ŕύX����邷�ׂẴ��������\�[�X�����蓖�Ă�֐�
void Game::CreateWindowSizeDependentResources()
{
    // TODO: �E�B���h�E�T�C�Y�Ɉˑ�����I�u�W�F�N�g�̏��������s��
	
}

void Game::OnDeviceLost()
{
	// TODO:������Direct3D�̃��\�[�X������L�q���Ă�������
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
/// �e��Direct3D�I�u�W�F�N�g�̎擾�֐�
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
	//�e�s��̋t�s����Z�o
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
