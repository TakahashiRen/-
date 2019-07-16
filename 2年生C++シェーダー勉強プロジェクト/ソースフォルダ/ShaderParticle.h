#pragma once
#include "StepTimer.h"

class ShaderParticle
{
//変数
public:
private:
	//位置　
	DirectX::SimpleMath::Vector3 m_position;
	//移動ベクトル
	DirectX::SimpleMath::Vector3 m_velocity;
	//寿命
	float m_life;
	//開始位置
	DirectX::SimpleMath::Vector3 m_startPosition;
	//開始速度
	DirectX::SimpleMath::Vector3 m_startVelocity;
//関数
public:
	ShaderParticle();
	~ShaderParticle();

	void Initialize();
	void Initialize(int life, DirectX::SimpleMath::Vector3 vel, DirectX::SimpleMath::Vector3 pos);
	void Update(DX::StepTimer timer);
	void Render();

	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

};

