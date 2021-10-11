#pragma once
#include "pch.h"
#include "Effect.h"
#include "CursorRenderer.h"
#include "FrameRateRenderer.h"
#include <CommonStates.h>
#include "StepTimer.h"


class Renderer {
public:
	~Renderer();

	bool Initialize();

	bool InitializeEffectsAndCursor();

	void Render();

	enum class FilterType {
		LINEAR,
		POINT
	};

	bool GetSampler(FilterType filterType, ID3D11SamplerState** result);

	ComPtr<ID3D11Device1> GetD3DDevice() const{
		return _d3dDevice;
	}

	ComPtr<ID3D11DeviceContext1> GetD3DDC() const {
		return _d3dDC;
	}

	ComPtr<IDXGIDevice1> GetDXGIDevice() const {
		return _dxgiDevice;
	}

	bool GetRenderTargetView(ID3D11Texture2D* texture, ID3D11RenderTargetView** result);

	bool GetShaderResourceView(ID3D11Texture2D* texture, ID3D11ShaderResourceView** result);

	bool SetFillVS();

	bool SetSimpleVS(ID3D11Buffer* simpleVB);

	bool SetCopyPS(ID3D11SamplerState* sampler, ID3D11ShaderResourceView* input);

	bool SetAlphaBlend(bool enable);

	StepTimer& GetTimer() {
		return _timer;
	}

	const StepTimer& GetTimer() const {
		return _timer;
	}

private:
	bool _InitD3D();

	bool _CheckSrcState();

	void _Render();

	ComPtr<ID3D11Device1> _d3dDevice;
	ComPtr<IDXGIDevice1> _dxgiDevice;
	ComPtr<IDXGISwapChain2> _dxgiSwapChain;
	ComPtr<ID3D11DeviceContext1> _d3dDC;
	HANDLE _frameLatencyWaitableObject = NULL;
	bool _waitingForNextFrame = false;

	ComPtr<ID3D11SamplerState> _linearSampler;
	ComPtr<ID3D11SamplerState> _pointSampler;
	ComPtr<ID3D11BlendState> _alphaBlendState;

	ComPtr<ID3D11Texture2D> _effectInput;
	ComPtr<ID3D11Texture2D> _backBuffer;
	std::unordered_map<ID3D11Texture2D*, ComPtr<ID3D11RenderTargetView>> _rtvMap;
	std::unordered_map<ID3D11Texture2D*, ComPtr<ID3D11ShaderResourceView>> _srvMap;

	ComPtr<ID3D11VertexShader> _fillVS;
	ComPtr<ID3D11VertexShader> _simpleVS;
	ComPtr<ID3D11InputLayout> _simpleIL;
	ComPtr<ID3D11PixelShader> _copyPS;
	std::vector<Effect> _effects;

	CursorRenderer _cursorRenderer;
	FrameRateRenderer _frameRateRenderer;

	StepTimer _timer;
};
