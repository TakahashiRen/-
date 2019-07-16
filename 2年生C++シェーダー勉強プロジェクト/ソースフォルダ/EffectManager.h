#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <vector>
#include <list>

#include "ShaderParticle.h"

class EffectManager
{
//�ϐ�
public:
	//�萔�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix matWorld;
		DirectX::SimpleMath::Matrix matView;
		DirectX::SimpleMath::Matrix matProj;
		DirectX::SimpleMath::Vector4 Diffuse;
	};
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

private:
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_cBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//�f�o�C�X���\�[�X
	DX::DeviceResources*	m_deviceResources;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �G�t�F�N�g�ɗp����e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
	//�W�I���g���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;

	//�J�����̈ʒu
	DirectX::SimpleMath::Vector3 m_camera;
	//�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	//�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_proj;

	//�`�悷�钸�_���i�[����z��
	std::vector<DirectX::VertexPositionColorTexture> m_vertex;

	//�p�[�e�B�N�����i�[����z��
	std::list<ShaderParticle*> m_effectList;

	
	//�o�߃t���[����
	float m_time;
	//�G�t�F�N�g�̐����t���[����
	int m_life;
	//�G�t�F�N�g�����������ǂ���
	bool m_isActive;

//�֐�
public:
	//�R���X�g���N�^
	EffectManager();
	//�f�X�g���N�^
	~EffectManager();
	//�G�t�F�N�g�쐬�֐�
	void Create(DX::DeviceResources* deviceResources, const wchar_t* name, int count);
	//�e�G�t�F�N�g�̏������֐�
	void Initialize(int life, DirectX::SimpleMath::Vector3 pos);
	//�G�t�F�N�g�̍X�V�֐�
	void Update(DX::StepTimer timer);
	//�`��֐�
	void Render();
	//�j�����̊֐�
	void Lost();
	//�`��ɕK�v�ȍs���ݒ肷��֐�
	void SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	//���݂̃G�t�F�N�g���A�N�e�B�u���ǂ��� 
	//true:�A�N�e�B�u false:��A�N�e�B�u
	bool IsActive() { return m_isActive; }
	void SetActive(bool f) { m_isActive = f; }
private:
	//�V�F�[�_�[��p���ăG�t�F�N�g���܂Ƃ߂ĕ`�悷��֐�
	void ShaderDraw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

};