
function InitShaderMeta(pShaderMeta)
    pShaderMeta:setShaderFileName("Assets/Shaders/TestShader.hlsl");
    do
        local subPass1 = SubPassDesc.new("SubPass1");
        subPass1:addShaderFeature({ " AAA ", " BBB " });
        subPass1:setVertexShader("VS");
        subPass1:setPixelShader("PS");
        subPass1:setAlphaToMask(true);
        subPass1:setAlphaToMask(false);
        subPass1:setBlendColor("Srcalpha", "OneMinusSrcAlpha");
        subPass1:setBlendAlpha("DstAlpha", "ONEMinusDstAlpha", 0);
        subPass1:setBlendOp("add");
        subPass1:setColorMask("ARGB");
        subPass1:setConservative(false);
        subPass1:setCull("back");
        subPass1:setOffset(1.0, 100);
        subPass1:setZClip(false);
        subPass1:setZTest("less");
        subPass1:setZWrite(true);
        subPass1:setPrimitiveType("triangle");
        pShaderMeta:addSubPassDesc(subPass1);
    end
end