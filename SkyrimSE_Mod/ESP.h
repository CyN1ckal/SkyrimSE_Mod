#pragma once

class ESP {
public:
  static bool Initialize();

private:
  static inline bool m_Initialized = false;
  static inline ID3D11Buffer *vertex_buffer = nullptr;
  static inline ID3D11VertexShader *m_vertexShader = nullptr;
  static inline ID3D11PixelShader *m_pixelShader = nullptr;
  static inline ID3D11InputLayout *m_layout = nullptr;
  static inline ID3D10Blob *m_vs_blob = nullptr;
  static inline ID3D11InputLayout *m_vertLayout = nullptr;
  static inline ID3D11RasterizerState *m_SolidRasterState = nullptr;
  static inline ID3D11DepthStencilState *m_SolidDepthStencilState = nullptr;

private:
  static bool LoadShaders();
  static bool CreateMesh();
  static bool CreateInputLayout();
  static bool CreateRasterizerAndDepthStates();
};