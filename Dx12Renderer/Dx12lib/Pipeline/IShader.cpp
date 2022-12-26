#include "IShader.h"
#include <fstream>
#include <ios>

namespace dx12lib {

auto IShader::getFileName() const noexcept -> const std::string &{
    return _fileName;
}
auto IShader::getTarget() const noexcept -> const std::string &{
    return _target;
}
auto IShader::getEntryPoint() const noexcept -> const std::string &{
    return _entryPoint;
}
auto IShader::getMacros() const noexcept -> const std::vector<Macro> &{
    return _macros;
}
void IShader::setFileName(std::string fileName) {
    _fileName = std::move(fileName);
}
void IShader::setTarget(std::string target) {
    _target = std::move(target);
}
void IShader::setEntryPoint(std::string entryPoint) {
    _entryPoint = std::move(entryPoint);
}
void IShader::setMacros(std::vector<Macro> macros) {
    _macros = std::move(macros);
}
void IShader::addMacro(Macro macro) {
    _macros.push_back(std::move(macro));
}

auto IShader::getReflect() const -> WRL::ComPtr<ID3D12ShaderReflection> {
    return _pShaderReflection;
}

void IShader::compileFormFile(ID3DInclude *pInclude) {
    std::ifstream fin(_fileName, std::ios::in);
    if (!fin.is_open())
        return;

	std::stringstream sbuf;
	sbuf << fin.rdbuf();
    auto content = sbuf.str();
    compileFormMemory(content.data(), content.length(), pInclude);
    fin.close();
}

}