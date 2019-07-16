#include "pch.h"
#include "ShaderParticle.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


ShaderParticle::ShaderParticle()
	:m_life(0.0f),m_startPosition(Vector3::Zero),m_position(Vector3::Zero),m_startVelocity(Vector3::Zero),m_velocity(Vector3::Zero)
{
}


ShaderParticle::~ShaderParticle()
{
}

void ShaderParticle::Initialize()
{
}

void ShaderParticle::Initialize(int life, DirectX::SimpleMath::Vector3 vel, DirectX::SimpleMath::Vector3 pos)
{
	m_life = life;
	m_startPosition = pos;
	m_position = pos;
	m_startVelocity = vel;
	m_velocity = vel;
}

void ShaderParticle::Update(DX::StepTimer timer)
{
	m_position += m_velocity;
}

void ShaderParticle::Render()
{
}
