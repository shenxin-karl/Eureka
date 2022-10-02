
function InitShaderDesc(pShaderDesc)
    pShaderDesc:setShaderFileName("Assets/Shaders/TestShader.hlsl");
    pShaderDesc:addShaderFeature({ " AAA ", " BBB " });
    pShaderDesc:setVertexShader("VS");
    pShaderDesc:setPixelShader("PS");
    pShaderDesc:setAlphaToMask(true);
    pShaderDesc:setAlphaToMask(false);
    pShaderDesc:setBlendColor("Srcalpha", "OneMinusSrcAlpha");
    pShaderDesc:setBlendAlpha("DstAlpha", "ONEMinusDstAlpha", 0);
    pShaderDesc:setBlendOp("add");
    pShaderDesc:setColorMask("ARGB");
    pShaderDesc:setConservative(false);
    pShaderDesc:setCull("back");
    pShaderDesc:setOffset(1.0, 100);
    pShaderDesc:setZClip(false);
    pShaderDesc:setZTest("less");
    pShaderDesc:setZWrite(true);
    pShaderDesc:setPrimitiveType("triangle");
end