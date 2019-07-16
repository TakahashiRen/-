//
// Game.h
//

#pragma once
#include <vector>

#include "DeviceResources.h"
#include "StepTimer.h"

#include "EffectManager.h"
#include "Object.h"
#include "Background.h"

//	D3D11�f�o�C�X���쐬�����{�I�ȃQ�[���̎�����
//	�Q�[�����[�v�̒�
class Game : public DX::IDeviceNotify
{
//�ϐ�
public:
private:
	// �f�o�C�X���\�[�X
	std::unique_ptr<DX::DeviceResources> m_deviceResources;

	// �����_�����O���[�v�^�C�}�[
	DX::StepTimer m_timer;

	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//�X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	DirectX::SimpleMath::Matrix m_view;

	DirectX::SimpleMath::Matrix m_proj;

	DirectX::SimpleMath::Vector3 m_camera;

	//�G�t�F�N�g
	std::vector<EffectManager*> m_explosionEffects;

//�֐�
public:
	//�R���X�g���N�^
    Game();
	//�f�X�g���N�^
	~Game();

    // �������ƊǗ�
    void Initialize(HWND window, int width, int height);

    // ��{�I�ȃQ�[�����[�v
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // ���b�Z�[�W
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // �v���p�e�B
    void GetDefaultSize( int& width, int& height ) const;
	void ChangeFullscreen(BOOL flag);
	
	//Direct3D���\�[�X�̎擾�֐�
	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetContext();
	DirectX::CommonStates*	GetCommonStates();
	DirectX::SpriteBatch*	GetSpriteBatch();
	DirectX::XMINT2			GetWindowSize();
	DirectX::SimpleMath::Vector3 CalcScreenToWorld(int sx, int sy, float fz, int Screen_W, int Screen_H, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
private:

	//�X�V�֐�
    void Update(DX::StepTimer const& timer);
	//�`��֐�
    void Render();

	//�o�b�N�o�b�t�@�[�̃N���A
    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

};