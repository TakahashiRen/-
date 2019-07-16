#include "pch.h"
#include "EffectManager.h"
#include "BinaryFile.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//インプットレイアウトの定義
const std::vector<D3D11_INPUT_ELEMENT_DESC> EffectManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
EffectManager::EffectManager()
	:m_time(0.0f),m_isActive(true)
{
}

/// <summary>
/// デストラクタ
/// </summary>
EffectManager::~EffectManager()
{
	//各ポインタの開放
	Lost();

	//パーティクルリストの開放
	for (std::list<ShaderParticle*>::iterator ite = m_effectList.begin(); ite != m_effectList.end(); ite++)
	{
		SAFE_DELETE(*ite);
	}
}

/// <summary>
/// 作成関数
/// </summary>
/// <param name="deviceResources">デバイスリソースポインタ</param>
/// <param name="name">テクスチャのファイルパス</param>
/// <param name="count">作成数</param>
void EffectManager::Create(DX::DeviceResources * deviceResources, const wchar_t * name, int count)
{
	m_deviceResources = deviceResources;
	auto device = m_deviceResources->GetD3DDevice();

	// コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");

	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());

	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	// Gシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateGShader Failed.", NULL, MB_OK);
		return;
	}


	//const wchar_t* name = name;
	DirectX::CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), name, nullptr, m_texture.GetAddressOf());

	// プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(m_deviceResources->GetD3DDeviceContext());

	m_states = std::make_unique<CommonStates>(device);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_cBuffer);


	for (int i = 0; i < count; i++)
	{
		ShaderParticle* effect = new ShaderParticle();
		m_effectList.push_back(effect);
	}

}

/// <summary>
/// エフェクトの初期化関数
/// </summary>
/// <param name="life">生存フレーム数</param>
/// <param name="pos">開始位置</param>
void EffectManager::Initialize(int life, DirectX::SimpleMath::Vector3 pos)
{
	int range = 100;
	for (std::list<ShaderParticle*>::iterator ite = m_effectList.begin(); ite != m_effectList.end(); ite++)
	{
		Vector3 v = Vector3(((rand() % (range * 2)) - range) / (float)range * 0.01f, ((rand() % (range * 2)) - range) / (float)range * 0.01f, 0);

		(*ite)->Initialize(life, v, pos);
	}
	m_life = life;
	m_time = 0.0f;
	m_isActive = true;
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">タイマー</param>
void EffectManager::Update(DX::StepTimer timer)
{
	m_time++;
	if (m_time > m_life)
	{
		m_isActive = false;
	}
	for (std::list<ShaderParticle*>::iterator ite = m_effectList.begin(); ite != m_effectList.end(); ite++)
	{
		(*ite)->Update(timer);
	}
}

/// <summary>
/// 描画関数
/// </summary>
void EffectManager::Render()
{
	m_vertex.clear();
	for (std::list<ShaderParticle*>::iterator ite = m_effectList.begin(); ite != m_effectList.end(); ite++)
	{
		Vector3 pos = (*ite)->GetPosition();
		{
			VertexPositionColorTexture vertex;
			vertex = VertexPositionColorTexture(pos, Vector4::One, Vector2(0.0f, 0.0f));
			m_vertex.push_back(vertex);
		}
	}
	ShaderDraw(Matrix::CreateTranslation(Vector3(0, 0, 0)), m_view, m_proj);
}

/// <summary>
/// 破棄時の関数
/// </summary>
void EffectManager::Lost()
{
	m_inputLayout.Reset();
	m_batch.reset();
	m_states.reset();
	m_texture.Reset();
	m_VertexShader.Reset();
	m_PixelShader.Reset();
	m_GeometryShader.Reset();
}

/// <summary>
/// 描画に必要な情報を設定する関数
/// </summary>
/// <param name="camera">カメラ位置</param>
/// <param name="view">ビュー行列</param>
/// <param name="proj">プロジェクション行列</param>
void EffectManager::SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	m_camera = camera;
	m_view = view;
	m_proj = proj;
}

/// <summary>
/// シェーダーを用いてエフェクトを描画する関数
/// </summary>
/// <param name="world">描画位置の行列</param>
/// <param name="view">ビュー行列</param>
/// <param name="proj">プロジェクション行列</param>
void EffectManager::ShaderDraw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = Vector4(0, m_time, 1, 1);

	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
	context->PSSetConstantBuffers(0, 1, cb);
	context->VSSetConstantBuffers(0, 0, nullptr);
	context->GSSetConstantBuffers(0, 1, cb);

	context->UpdateSubresource(m_cBuffer.Get(), 0, nullptr, &cbuff, 0, 0);


	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthRead(), 0);
	// カリングは左周り
	context->RSSetState(m_states->CullNone());

	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);

	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	//context->VSSetShaderResources(1, 1, &m_texture);

	context->IASetInputLayout(m_inputLayout.Get());

	// 半透明部分を描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertex[0], m_vertex.size());
	m_batch->End();
}
