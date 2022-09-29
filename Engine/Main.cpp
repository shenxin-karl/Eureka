#include <iostream>
#include "Application/Application.h"
#include "GameTimer/GameTimer.h"
#include "ShaderHelper/GraphicsShader.h"
#include "ShaderHelper/ShaderHelper.h"

void test() {

	Eureka::GraphicsShaderDesc graphicsShaderDesc;
	graphicsShaderDesc.fileName = "Assets/Shaders/TestShader.hlsl";
	
	auto shader = std::make_unique<Eureka::GraphicsShader>(graphicsShaderDesc);

	auto pByteCode = Eureka::ShaderHelper::compile(
		L"Assets/Shaders/TestShader.hlsl",
		nullptr,
		"VS",
		"vs_5_1"
	);

	WRL::ComPtr<ID3D12ShaderReflection> pShaderRef;
	ThrowIfFailed(D3DReflect(pByteCode->GetBufferPointer(), 
		pByteCode->GetBufferSize(), 
		IID_PPV_ARGS(&pShaderRef)
	));

	D3D12_SHADER_DESC desc;
	pShaderRef->GetDesc(&desc);
	for (unsigned int i = 0; i < desc.ConstantBuffers; ++i)
	{
		ID3D12ShaderReflectionConstantBuffer *buffer = pShaderRef->GetConstantBufferByIndex(i);

		D3D12_SHADER_BUFFER_DESC bufferDesc;
		buffer->GetDesc(&bufferDesc);
		// here ok. bufferDesc.Name == "cb3"

		// here wrong! bufferDesc.Variables==1, I expected 2       
		for (UINT j = 0; j < bufferDesc.Variables; j++)
		{
			ID3D12ShaderReflectionVariable *var = buffer->GetVariableByIndex(j);
			D3D12_SHADER_VARIABLE_DESC varDesc;
			var->GetDesc(&varDesc);
			// here also wrong.
			// I expect "MVP" first but it returns also "cb3"

			std::cout << varDesc.Name << std::endl;
		}
	}

	// 获取绑定槽位
	for (int i = 0; i < (INT)desc.BoundResources; i++)
	{
		D3D12_SHADER_INPUT_BIND_DESC  resource_desc;
		pShaderRef->GetResourceBindingDesc(i, &resource_desc);

		auto shaderVarName = resource_desc.Name;
		auto registerSpace = resource_desc.Space;
		auto resourceType = resource_desc.Type;
		auto bindPoint = resource_desc.BindPoint;

		std::cout << "var name is " << shaderVarName << std::endl;
		std::cout << "type name is " << resourceType << std::endl;
		std::cout << "bind point is " << bindPoint << std::endl;
		std::cout << "register space is " << registerSpace << std::endl;
	}

	D3D12_SIGNATURE_PARAMETER_DESC signDesc;
	for (size_t i = 0; i < desc.InputParameters; ++i) {
		pShaderRef->GetInputParameterDesc(i, &signDesc);
	}
}

int main() {
	test();

	Eureka::Application app;
	try {
		auto pGameTimer = std::make_shared<Eureka::GameTimer>();
		app.initialize();
		while (app.isRunning()) {
			pGameTimer->startNewFrame();
			app.beginTick(pGameTimer);
			app.tick(pGameTimer);
			app.endTick(pGameTimer);
		}
		app.destroy();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		MessageBox(nullptr, e.what(), "Error", MB_OK | MB_ICONHAND);
	}
}
