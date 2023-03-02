#include "PassParser.h"
#include "EffectLab/Pass.h"
#include "EffectLab/ShaderKeyword.h"
#include "EffectLab/ShaderKeywordSet.h"
#include "Foundation/Exception.h"
#include "Objects/PathManager.h"

namespace Eureka {

PassParser::PassParser(std::string effectSourcePath)
: _effectSourcePath(effectSourcePath)
, _rasterizerParser(effectSourcePath)
, _blendParser(effectSourcePath)
, _depthStencilParser(std::move(effectSourcePath))
{
	_pKeywordSet = std::make_shared<ShaderKeywordSet>();
}

auto PassParser::parse(pd::EffectLabParser::PassContext *ctx) -> std::unique_ptr<Pass> {
	_pass = std::make_unique<Pass>();
	_pass->_tag = std::any_cast<std::string>(visitPass_tag(ctx->pass_tag()));
	for (auto *item : ctx->pass_block_item()) {
		item->accept(this);
	}

	if (_pass->_programContext.empty()) {
		Exception::Throw("the pass '{}' No source code for shader is provided", _pass->getTag());
	}

	_pass->_rasterizerDesc = _rasterizerParser.getRasterizerDesc();
	_pass->_depthStencilDesc = _depthStencilParser.getDepthStencilDesc();
	_pass->_stencilRef = _depthStencilParser.getStencilRef();
	_pass->_blendDesc = _blendParser.getBlendDesc();
	_pass->_pKeywordSet = _pKeywordSet;
	return std::move(_pass);
}

std::any PassParser::visitPass_tag(ParserDetails::EffectLabParser::Pass_tagContext *context) {
	auto text = context->StringLiteral()->getText();
	return extractString(text);
}

std::any PassParser::visitPassSourceContext(ParserDetails::EffectLabParser::PassSourceContextContext *context) {
	auto *pToken = context->getStart();
	if (_programContent.valid()) {
		Exception::Throw("{} {}:{} keyword 'HLSLPROGRAM' redefinition",
			_effectSourcePath,
			pToken->getLine(),
			pToken->getCharPositionInLine()
		);
	}

	_programContent.setLocation(pToken);
	constexpr size_t kBlockBeginLength = std::string_view("HLSLPROGRAM\n").length();
	constexpr size_t kBlockEndLength = std::string_view("ENDHLSL\n").length();
	std::string text = context->pass_source_context()->getText();
	std::string content = text.substr(kBlockBeginLength, text.length() - kBlockBeginLength - kBlockEndLength);
	std::string absolutePath = fs::absolute(_effectSourcePath).string();
	_pass->_programContext = fmt::format("#line {} \"{}\"\n{}", pToken->getLine(), absolutePath, content);
	return NullAny;
}

std::any PassParser::visitPassVertexShader(pd::EffectLabParser::PassVertexShaderContext *context) {
	auto token = context->getStart();
	if (_vertexShader.valid()) {
		parserShaderThrow(_vertexShader, token, "Vertex");
	}

	auto text = context->pass_vertex_shader()->Identity()->getText();
	_vertexShader.setLocation(token);
	_pass->_vertexEntryPoint = std::move(text);
	return NullAny;
}

std::any PassParser::visitPassHullShader(pd::EffectLabParser::PassHullShaderContext *context) {
	auto token = context->getStart();
	if (_hullShader.hasValue()) {
		parserShaderThrow(_hullShader, token, "Hull");
	}

	auto text = context->pass_hull_shader()->Identity()->getText();
	_hullShader.setLocation(token);
	_hullShader.set(text);
	_pass->_hullEntryPoint = std::move(text);
	return NullAny;
}

std::any PassParser::visitPassDomainShader(pd::EffectLabParser::PassDomainShaderContext *context) {
	auto token = context->getStart();
	if (_domainShader.hasValue()) {
		parserShaderThrow(_domainShader, token, "Domain");
	}

	auto text = context->pass_domain_shader()->Identity()->getText();
	_domainShader.setLocation(token);
	_domainShader.set(text);
	_pass->_domainEntryPoint = std::move(text);
	return NullAny;
}

std::any PassParser::visitPassGeometryShader(pd::EffectLabParser::PassGeometryShaderContext *context) {
	auto token = context->getStart();
	if (_geometryShader.hasValue()) {
		parserShaderThrow(_geometryShader, token, "Geometry");
	}

	auto text = context->pass_geometry_shader()->Identity()->getText();
	_geometryShader.setLocation(token);
	_geometryShader.set(text);
	_pass->_geometryEntryPoint = std::move(text);
	return NullAny;
}

std::any PassParser::visitPassPixelShader(pd::EffectLabParser::PassPixelShaderContext *context) {
	auto token = context->getStart();
	if (_pixelShader.hasValue()) {
		parserShaderThrow(_pixelShader, token, "Pixel");
	}

	auto text = context->pass_pixel_shader()->Identity()->getText();
	_pixelShader.setLocation(token);
	_pixelShader.set(text);
	_pass->_pixelEntryPoint = std::move(text);
	return NullAny;
}

std::any PassParser::visitPassRenderQueue(pd::EffectLabParser::PassRenderQueueContext *context) {
	auto token = context->getStart();
	if (_renderQueueLabel.hasValue()) {
		Exception::Throw("{} {}:{} keyword RenderQueue redefinition",
			_effectSourcePath,
			token->getLine(),
			token->getCharPositionInLine()
		);
	}

	auto text = context->pass_render_queue()->RenderQueueLabel()->getText();
	if (text == "BackGround") {
		_renderQueueLabel.set(RenderQueueLabel::BackGround);
	} else if (text == "Geometry") {
		_renderQueueLabel.set(RenderQueueLabel::Geometry);
	} else if (text == "Opaque") {
		_renderQueueLabel.set(RenderQueueLabel::Opaque);
	} else if (text == "AlphaTest") {
		_renderQueueLabel.set(RenderQueueLabel::AlphaTest);
	} else if (text == "Transparent") {
		_renderQueueLabel.set(RenderQueueLabel::Transparent);
	} else if (text == "Overlay") {
		_renderQueueLabel.set(RenderQueueLabel::Overlay);
	}

	_renderQueueLabel.setLocation(token);
	_pass->_renderQueue = _renderQueueLabel.get();
	return NullAny;
}

std::any PassParser::visitPassShaderFeature(pd::EffectLabParser::PassShaderFeatureContext *context) {
	ShaderKeywordSet::ShaderFeature shaderFeature;
	for (const auto &macroNode : context->pass_shader_feature()->Identity()) {
		auto token = macroNode->getSymbol();
		auto macro = extractString(macroNode->getText());
		auto iter = _macroLocationMap.find(macro);
		if (iter != _macroLocationMap.end()) {
			Exception::Throw("{} {}:{} the shader feature macro"
				"{} redefine, the last redefinition in {} {} {}",
				_effectSourcePath,
				token->getLine(),
				token->getCharPositionInLine(),
				macro,
				iter->second.line,
				iter->second.column
			);
		}

		Location location;
		location.setLocation(token);
		_macroLocationMap[macro] = location;
		shaderFeature.push_back(std::move(macro));
	}

	_pKeywordSet->addShaderFeatures(std::move(shaderFeature));
	return NullAny;
}

std::any PassParser::visitPassCullMode(pd::EffectLabParser::PassCullModeContext *context) {
	return _rasterizerParser.visitPassCullMode(context);
}

std::any PassParser::visitPassZClipMode(pd::EffectLabParser::PassZClipModeContext *context) {
	return _rasterizerParser.visitPassZClipMode(context);
}

std::any PassParser::visitPassZTestMode(pd::EffectLabParser::PassZTestModeContext *context) {
	return _depthStencilParser.visitPassZTestMode(context);
}

std::any PassParser::visitPassZWriteMode(ParserDetails::EffectLabParser::PassZWriteModeContext *context) {
	return _depthStencilParser.visitPassZWriteMode(context);
}

std::any PassParser::visitPassOffset(ParserDetails::EffectLabParser::PassOffsetContext *context) {
	return _rasterizerParser.visitPassOffset(context);
}

std::any PassParser::visitPassAlphaToMask(pd::EffectLabParser::PassAlphaToMaskContext *context) {
	return _blendParser.visitPassAlphaToMask(context);
}

std::any PassParser::visitPassConservative(pd::EffectLabParser::PassConservativeContext *context) {
	return _rasterizerParser.visitPassConservative(context);
}

std::any PassParser::visitPassColorMask(pd::EffectLabParser::PassColorMaskContext *context) {
	return _blendParser.visitPassColorMask(context);
}

std::any PassParser::visitPassBlend(pd::EffectLabParser::PassBlendContext *context) {
	return _blendParser.visitPassBlend(context);
}

std::any PassParser::visitPassBlendOp(pd::EffectLabParser::PassBlendOpContext *context) {
	return _depthStencilParser.visitPassBlendOp(context);
}

std::any PassParser::visitPassStencil(pd::EffectLabParser::PassStencilContext *context) {
	return _depthStencilParser.visitPassStencil(context);
}

void PassParser::parserShaderThrow(const LocAndObject<std::string> &shader, 
	const antlr4::Token *pToken,
	std::string_view keyword) const
{
	Exception::Throw("{} {}:{} keyword {} redefinition in {} {}:{} the last value is {}",
		_effectSourcePath,
		pToken->getLine(),
		pToken->getCharPositionInLine(),
		keyword,
		_effectSourcePath,
		shader.line,
		shader.column,
		shader.get()
	);
}

}
