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

//	D3D11デバイスを作成する基本的なゲームの実装と
//	ゲームループの提供
class Game : public DX::IDeviceNotify
{
//変数
public:
private:
	// デバイスリソース
	std::unique_ptr<DX::DeviceResources> m_deviceResources;

	// レンダリングループタイマー
	DX::StepTimer m_timer;

	//コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	//スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	DirectX::SimpleMath::Matrix m_view;

	DirectX::SimpleMath::Matrix m_proj;

	DirectX::SimpleMath::Vector3 m_camera;

	//エフェクト
	std::vector<EffectManager*> m_explosionEffects;

//関数
public:
	//コンストラクタ
    Game();
	//デストラクタ
	~Game();

    // 初期化と管理
    void Initialize(HWND window, int width, int height);

    // 基本的なゲームループ
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // メッセージ
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // プロパティ
    void GetDefaultSize( int& width, int& height ) const;
	void ChangeFullscreen(BOOL flag);
	
	//Direct3Dリソースの取得関数
	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetContext();
	DirectX::CommonStates*	GetCommonStates();
	DirectX::SpriteBatch*	GetSpriteBatch();
	DirectX::XMINT2			GetWindowSize();
	DirectX::SimpleMath::Vector3 CalcScreenToWorld(int sx, int sy, float fz, int Screen_W, int Screen_H, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
private:

	//更新関数
    void Update(DX::StepTimer const& timer);
	//描画関数
    void Render();

	//バックバッファーのクリア
    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

};