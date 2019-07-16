#pragma once
#include "StepTimer.h"

class ShaderParticle
{
//�ϐ�
public:
private:
	//�ʒu�@
	DirectX::SimpleMath::Vector3 m_position;
	//�ړ��x�N�g��
	DirectX::SimpleMath::Vector3 m_velocity;
	//����
	float m_life;
	//�J�n�ʒu
	DirectX::SimpleMath::Vector3 m_startPosition;
	//�J�n���x
	DirectX::SimpleMath::Vector3 m_startVelocity;
//�֐�
public:
	ShaderParticle();
	~ShaderParticle();

	void Initialize();
	void Initialize(int life, DirectX::SimpleMath::Vector3 vel, DirectX::SimpleMath::Vector3 pos);
	void Update(DX::StepTimer timer);
	void Render();

	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

};

