#include "pch.h"

#include "ESP.h"

bool ESP::Initialize() {
  if (m_Initialized)
    return true;

  LoadShaders();
  CreateMesh();
  CreateInputLayout();
  //CreateRasterizerAndDepthStates();

  m_Initialized = true;
  return true;
}

bool ESP::LoadShaders() {
  char filepath[512];
  GetModuleFileNameA(GetModuleHandle(NULL), filepath, 512);
  std::cout << filepath << std::endl;

  D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
  ID3D10Blob *vertexShaderBuffer = 0;
  ID3D10Blob *pixelShaderBuffer = 0;
  ID3D10Blob *CompileErrors = 0;
  HRESULT result;
  result = D3DCompileFromFile(L"Colors.vs", NULL, NULL, "ColorVertexShader",
                              "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
                              &vertexShaderBuffer, &CompileErrors);
  if (FAILED(result)) {
    // If the shader failed to compile it should have writen something to the
    // error message.
    if (!CompileErrors) {
      MessageBoxW(DirectXHook::SkyrimSE_hWnd, L"Colors.vs",
                  L"Missing Shader File", MB_OK);
    } else {
      MessageBoxW(DirectXHook::SkyrimSE_hWnd, L"Colors.vs", L"CompileErrors!",
                  MB_OK);
    }
  }

  result = D3DCompileFromFile(L"Colors.ps", NULL, NULL, "ColorPixelShader",
                              "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
                              &pixelShaderBuffer, &CompileErrors);
  if (FAILED(result)) {
    // If the shader failed to compile it should have writen something to the
    // error message.
    if (!CompileErrors) {
      MessageBoxW(DirectXHook::SkyrimSE_hWnd, L"Colors.ps",
                  L"Missing Shader File", MB_OK);
    } else {
      MessageBoxW(DirectXHook::SkyrimSE_hWnd, L"Colors.ps", L"CompileErrors!",
                  MB_OK);
    }
  }

  DirectXHook::D3D11_Device->CreateVertexShader(
      vertexShaderBuffer->GetBufferPointer(),
      vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);

  DirectXHook::D3D11_Device->CreatePixelShader(
      pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(),
      NULL, &m_pixelShader);

  return 1;
}

bool ESP::CreateMesh() {
  const float vertData[] = {-1, -1, 0.1, 1,  0, 0,   1, 1, 0.1,
                            0,  1,  0,   -1, 1, 0.1, 0, 0, 1};

  D3D11_BUFFER_DESC vertBufferDesc;
  ZeroMemory(&vertBufferDesc, sizeof(vertBufferDesc));
  vertBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  vertBufferDesc.ByteWidth = sizeof(float) * 6 * 3;
  vertBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  vertBufferDesc.CPUAccessFlags = 0;
  vertBufferDesc.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA vertBufferData;
  ZeroMemory(&vertBufferData, sizeof(vertBufferData));
  vertBufferData.pSysMem = vertData;

  HRESULT res = DirectXHook::D3D11_Device->CreateBuffer(
      &vertBufferDesc, &vertBufferData, &vertex_buffer);

  return 1;
}

bool ESP::CreateInputLayout() {
  D3D11_INPUT_ELEMENT_DESC vertElements[] = {
      {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
       D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,
       D3D11_INPUT_PER_VERTEX_DATA, 0}};

  HRESULT err = DirectXHook::D3D11_Device->CreateInputLayout(
      vertElements, _countof(vertElements), m_vs_blob->GetBufferPointer(),
      m_vs_blob->GetBufferSize(), &m_vertLayout);
  return true;
}

bool ESP::CreateRasterizerAndDepthStates() {
  D3D11_RASTERIZER_DESC soliddesc;
  ZeroMemory(&soliddesc, sizeof(D3D11_RASTERIZER_DESC));
  soliddesc.FillMode = D3D11_FILL_SOLID;
  soliddesc.CullMode = D3D11_CULL_NONE;
  HRESULT err = DirectXHook::D3D11_Device->CreateRasterizerState(
      &soliddesc, &m_SolidRasterState);

  D3D11_DEPTH_STENCIL_DESC depthDesc;
  ZeroMemory(&depthDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
  depthDesc.DepthEnable = true;
  depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  depthDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
  err = DirectXHook::D3D11_Device->CreateDepthStencilState(
      &depthDesc, &m_SolidDepthStencilState);

  return 1;
}