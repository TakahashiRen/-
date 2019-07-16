#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);

SamplerState samLinear : register(s0);


float4 main(PS_INPUT input) : SV_TARGET
{
	float4 base = tex.Sample(samLinear, input.Tex);

	float time = Diffuse.y / 60;
	base.rgba -= time;

	return base;
}