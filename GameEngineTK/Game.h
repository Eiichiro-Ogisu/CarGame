//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include "DebugCamera.h"
#include "Camera.h"
#include "FollowCamera.h"

#include <PrimitiveBatch.h>		// PrimitiveBatch
#include <VertexTypes.h>		// VertexPositionColor
#include <Effects.h>			// BasicEffect
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Keyboard.h>


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

	// ���Ԃ̃J�E���g
    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	// �����o��ǉ����Ă���
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> m_batch;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DebugCamera> m_debugCamera;

	// �G�t�F�N�g�t�@�N�g��
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	
	// �w�i���f��
	std::unique_ptr<DirectX::Model> m_modelGround;

	std::unique_ptr<DirectX::Model> m_ground2[100];

	std::unique_ptr<DirectX::Model> m_modelSkydome;

	std::unique_ptr<DirectX::Model> m_modelHead;

	// ���f��
	std::unique_ptr<DirectX::Model> m_skydome2;

	// �e�B�[�|�b�g���f��
	std::unique_ptr<DirectX::Model> m_teapot;

	// �����[���h�s��
	DirectX::SimpleMath::Matrix m_worldBall[10];

	DirectX::SimpleMath::Matrix m_worldBall2[10];

	DirectX::SimpleMath::Matrix m_worldGround;

	// �e�B�[�|�b�g���[���h�s��
	DirectX::SimpleMath::Matrix m_worldTeapot[20];

	DirectX::SimpleMath::Matrix buf[20];

	// ���@�̃��[���h�s��
	DirectX::SimpleMath::Matrix m_worldHead = DirectX::SimpleMath::Matrix::Identity;

	int m_angle = 0;

	DirectX::SimpleMath::Matrix m_scale;

	float m_scale2 = 0;

	bool scaleFlag = false;

	float m_length;

	float worldTimer = 1.0f;

	int m_x[20];

	int m_z[20];

	DirectX::SimpleMath::Matrix transBuf[20];

	std::unique_ptr<DirectX::Keyboard> _keyboard;

	DirectX::Keyboard::State g_key;

	// ���@�̍��W
	DirectX::SimpleMath::Vector3 tankPos;

	float tankRot = 0.0f;

	// �J����
	std::unique_ptr<FollowCamera> m_camera;
};