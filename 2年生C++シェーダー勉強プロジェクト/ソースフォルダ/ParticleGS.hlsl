#include "Particle.hlsli"

static const int vnum = 4;

static const float4 offset_Array[vnum] = 
{
	float4(-0.5f, +0.5f, 0, 0),//ç∂è„
	float4(+0.5f, +0.5f, 0, 0),//âEè„
	float4(-0.5f, -0.5f, 0, 0),//ç∂â∫
	float4(+0.5f, -0.5f, 0, 0),//âEâ∫
};

[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream< PS_INPUT > output
)
{
	for (uint i = 0; i < vnum; i++)
	{
		PS_INPUT element;
		//element.Pos = input[0].Pos + offset_Array[i] * 0.1f * (input[0].Pos.x + 0.1f);
		element.Pos = input[0].Pos + offset_Array[i];

		element.Pos = mul(element.Pos, matWorld);
		element.Pos = mul(element.Pos, matView);
		element.Pos = mul(element.Pos, matProj);

		element.Color = input[0].Pos;

		element.Tex = -offset_Array[i] + float2(0.5f, 0.5f);
		output.Append(element);
	}
}