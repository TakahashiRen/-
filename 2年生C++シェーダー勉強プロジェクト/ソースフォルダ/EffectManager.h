#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <vector>
#include <list>

#include "ShaderParticle.h"

class EffectManager
{
//変数
public:
	//定数バッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix matWorld;
		DirectX::SimpleMath::Matrix matView;
		DirectX::SimpleMath::Matrix matProj;
		DirectX::SimpleMath::Vector4 Diffuse;
	};
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

private:
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_cBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//デバイスリソース
	DX::DeviceResources*	m_deviceResources;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	// エフェクトに用いるテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
	//ジオメトリシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;

	//カメラの位置
	DirectX::SimpleMath::Vector3 m_camera;
	//ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	//プロジェクション行列
	DirectX::SimpleMath::Matrix m_proj;

	//描画する頂点を格納する配列
	std::vector<DirectX::VertexPositionColorTexture> m_vertex;

	//パーティクルを格納する配列
	std::list<ShaderParticle*> m_effectList;

	
	//経過フレーム数
	float m_time;
	//エフェクトの生存フレーム数
	int m_life;
	//エフェクトが活動中かどうか
	bool m_isActive;

//関数
public:
	//コンストラクタ
	EffectManager();
	//デストラクタ
	~EffectManager();
	//エフェクト作成関数
	void Create(DX::DeviceResources* deviceResources, const wchar_t* name, int count);
	//各エフェクトの初期化関数
	void Initialize(int life, DirectX::SimpleMath::Vector3 pos);
	//エフェクトの更新関数
	void Update(DX::StepTimer timer);
	//描画関数
	void Render();
	//破棄時の関数
	void Lost();
	//描画に必要な行列を設定する関数
	void SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	//現在のエフェクトがアクティブかどうか 
	//true:アクティブ false:非アクティブ
	bool IsActive() { return m_isActive; }
	void SetActive(bool f) { m_isActive = f; }
private:
	//シェーダーを用いてエフェクトをまとめて描画する関数
	void ShaderDraw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

};