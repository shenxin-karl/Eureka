
function InitShaderDesc(pShaderDesc) 
	pShaderDesc:setShaderFileName("Engine/HlslShader/ForwardPBR.hlsl")
	pShaderDesc:setShaderName("ForwardPBR")
	pShaderDesc:setVertexShader("VS")
	pShaderDesc:setPixelShader("PS")
end