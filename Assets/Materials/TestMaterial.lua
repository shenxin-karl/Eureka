
function initMaterial(pShaderMeta)
    pShaderMeta:setShaderFileName("Assets/Shaders/TestShader.hlsl");
    do
        local pass1 = SubPassDesc.new();
        pass1:addShaderFeature({ "AAA", "BBB" });
        pass1:setVertexShader("VS");
        pass1:setAlphaToMask(1);
    end
end