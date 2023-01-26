// Generated from d:\share\Eureka\Engine\ShaderLab\ShaderLab.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ShaderLabParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, BoolVal=17, 
		IntVal=18, FloatVal=19, String=20, Identity=21, KWIdentity=22, KWTrue=23, 
		KWFalse=24, WhiteSpace=25, LineComment=26, Comment=27;
	public static final int
		RULE_shader = 0, RULE_shader_path = 1, RULE_property_block = 2, RULE_number_val = 3, 
		RULE_property_bool_val = 4, RULE_property_int_val = 5, RULE_property_float_val = 6, 
		RULE_property_float2_val = 7, RULE_property_float3_val = 8, RULE_property_float4_val = 9, 
		RULE_property_texture_val = 10, RULE_property_matrix = 11, RULE_property_name = 12, 
		RULE_property_description = 13, RULE_property_item = 14;
	private static String[] makeRuleNames() {
		return new String[] {
			"shader", "shader_path", "property_block", "number_val", "property_bool_val", 
			"property_int_val", "property_float_val", "property_float2_val", "property_float3_val", 
			"property_float4_val", "property_texture_val", "property_matrix", "property_name", 
			"property_description", "property_item"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'ShaderPath'", "':'", "';'", "'Properties'", "'{'", "'}'", "'('", 
			"','", "')'", "'bool'", "'Bool'", "'='", "'Int'", "'int'", "'Float'", 
			"'float '", null, null, null, null, null, "'Identity'", "'true'", "'false'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, "BoolVal", "IntVal", "FloatVal", "String", 
			"Identity", "KWIdentity", "KWTrue", "KWFalse", "WhiteSpace", "LineComment", 
			"Comment"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "ShaderLab.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ShaderLabParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class ShaderContext extends ParserRuleContext {
		public Shader_pathContext shader_path() {
			return getRuleContext(Shader_pathContext.class,0);
		}
		public Property_blockContext property_block() {
			return getRuleContext(Property_blockContext.class,0);
		}
		public ShaderContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_shader; }
	}

	public final ShaderContext shader() throws RecognitionException {
		ShaderContext _localctx = new ShaderContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_shader);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(30);
			shader_path();
			setState(32);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__3) {
				{
				setState(31);
				property_block();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Shader_pathContext extends ParserRuleContext {
		public TerminalNode String() { return getToken(ShaderLabParser.String, 0); }
		public Shader_pathContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_shader_path; }
	}

	public final Shader_pathContext shader_path() throws RecognitionException {
		Shader_pathContext _localctx = new Shader_pathContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_shader_path);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(34);
			match(T__0);
			setState(35);
			match(T__1);
			setState(36);
			match(String);
			setState(37);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_blockContext extends ParserRuleContext {
		public Property_itemContext property_item() {
			return getRuleContext(Property_itemContext.class,0);
		}
		public Property_blockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_block; }
	}

	public final Property_blockContext property_block() throws RecognitionException {
		Property_blockContext _localctx = new Property_blockContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_property_block);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(39);
			match(T__3);
			setState(40);
			match(T__4);
			setState(42);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Identity) {
				{
				setState(41);
				property_item();
				}
			}

			setState(44);
			match(T__5);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Number_valContext extends ParserRuleContext {
		public TerminalNode IntVal() { return getToken(ShaderLabParser.IntVal, 0); }
		public TerminalNode FloatVal() { return getToken(ShaderLabParser.FloatVal, 0); }
		public Number_valContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_number_val; }
	}

	public final Number_valContext number_val() throws RecognitionException {
		Number_valContext _localctx = new Number_valContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_number_val);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(46);
			_la = _input.LA(1);
			if ( !(_la==IntVal || _la==FloatVal) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_bool_valContext extends ParserRuleContext {
		public TerminalNode BoolVal() { return getToken(ShaderLabParser.BoolVal, 0); }
		public Property_bool_valContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_bool_val; }
	}

	public final Property_bool_valContext property_bool_val() throws RecognitionException {
		Property_bool_valContext _localctx = new Property_bool_valContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_property_bool_val);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(48);
			match(BoolVal);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_int_valContext extends ParserRuleContext {
		public TerminalNode IntVal() { return getToken(ShaderLabParser.IntVal, 0); }
		public Property_int_valContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_int_val; }
	}

	public final Property_int_valContext property_int_val() throws RecognitionException {
		Property_int_valContext _localctx = new Property_int_valContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_property_int_val);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(50);
			match(IntVal);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_float_valContext extends ParserRuleContext {
		public Number_valContext number_val() {
			return getRuleContext(Number_valContext.class,0);
		}
		public Property_float_valContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_float_val; }
	}

	public final Property_float_valContext property_float_val() throws RecognitionException {
		Property_float_valContext _localctx = new Property_float_valContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_property_float_val);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(52);
			number_val();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_float2_valContext extends ParserRuleContext {
		public List<Number_valContext> number_val() {
			return getRuleContexts(Number_valContext.class);
		}
		public Number_valContext number_val(int i) {
			return getRuleContext(Number_valContext.class,i);
		}
		public Property_float2_valContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_float2_val; }
	}

	public final Property_float2_valContext property_float2_val() throws RecognitionException {
		Property_float2_valContext _localctx = new Property_float2_valContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_property_float2_val);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(54);
			match(T__6);
			setState(55);
			number_val();
			setState(56);
			match(T__7);
			setState(57);
			number_val();
			setState(58);
			match(T__8);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_float3_valContext extends ParserRuleContext {
		public List<Number_valContext> number_val() {
			return getRuleContexts(Number_valContext.class);
		}
		public Number_valContext number_val(int i) {
			return getRuleContext(Number_valContext.class,i);
		}
		public Property_float3_valContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_float3_val; }
	}

	public final Property_float3_valContext property_float3_val() throws RecognitionException {
		Property_float3_valContext _localctx = new Property_float3_valContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_property_float3_val);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(60);
			match(T__6);
			setState(61);
			number_val();
			setState(62);
			match(T__7);
			setState(63);
			number_val();
			setState(64);
			match(T__7);
			setState(65);
			number_val();
			setState(66);
			match(T__8);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_float4_valContext extends ParserRuleContext {
		public List<Number_valContext> number_val() {
			return getRuleContexts(Number_valContext.class);
		}
		public Number_valContext number_val(int i) {
			return getRuleContext(Number_valContext.class,i);
		}
		public Property_float4_valContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_float4_val; }
	}

	public final Property_float4_valContext property_float4_val() throws RecognitionException {
		Property_float4_valContext _localctx = new Property_float4_valContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_property_float4_val);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(68);
			match(T__6);
			setState(69);
			number_val();
			setState(70);
			match(T__7);
			setState(71);
			number_val();
			setState(72);
			match(T__7);
			setState(73);
			number_val();
			setState(74);
			match(T__7);
			setState(75);
			number_val();
			setState(76);
			match(T__8);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_texture_valContext extends ParserRuleContext {
		public TerminalNode String() { return getToken(ShaderLabParser.String, 0); }
		public Property_texture_valContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_texture_val; }
	}

	public final Property_texture_valContext property_texture_val() throws RecognitionException {
		Property_texture_valContext _localctx = new Property_texture_valContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_property_texture_val);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(78);
			match(String);
			setState(79);
			match(T__4);
			setState(80);
			match(T__5);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_matrixContext extends ParserRuleContext {
		public TerminalNode KWIdentity() { return getToken(ShaderLabParser.KWIdentity, 0); }
		public Property_matrixContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_matrix; }
	}

	public final Property_matrixContext property_matrix() throws RecognitionException {
		Property_matrixContext _localctx = new Property_matrixContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_property_matrix);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(82);
			match(KWIdentity);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_nameContext extends ParserRuleContext {
		public TerminalNode Identity() { return getToken(ShaderLabParser.Identity, 0); }
		public Property_nameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_name; }
	}

	public final Property_nameContext property_name() throws RecognitionException {
		Property_nameContext _localctx = new Property_nameContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_property_name);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(84);
			match(Identity);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_descriptionContext extends ParserRuleContext {
		public TerminalNode String() { return getToken(ShaderLabParser.String, 0); }
		public Property_descriptionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_description; }
	}

	public final Property_descriptionContext property_description() throws RecognitionException {
		Property_descriptionContext _localctx = new Property_descriptionContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_property_description);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(86);
			match(String);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_itemContext extends ParserRuleContext {
		public Property_nameContext property_name() {
			return getRuleContext(Property_nameContext.class,0);
		}
		public Property_descriptionContext property_description() {
			return getRuleContext(Property_descriptionContext.class,0);
		}
		public Property_bool_valContext property_bool_val() {
			return getRuleContext(Property_bool_valContext.class,0);
		}
		public Property_int_valContext property_int_val() {
			return getRuleContext(Property_int_valContext.class,0);
		}
		public Property_float_valContext property_float_val() {
			return getRuleContext(Property_float_valContext.class,0);
		}
		public Property_itemContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_item; }
	}

	public final Property_itemContext property_item() throws RecognitionException {
		Property_itemContext _localctx = new Property_itemContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_property_item);
		int _la;
		try {
			setState(117);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(88);
				property_name();
				setState(89);
				match(T__6);
				setState(90);
				property_description();
				setState(91);
				match(T__7);
				setState(92);
				_la = _input.LA(1);
				if ( !(_la==T__9 || _la==T__10) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(93);
				match(T__8);
				setState(94);
				match(T__8);
				setState(95);
				match(T__11);
				setState(96);
				property_bool_val();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(98);
				property_name();
				setState(99);
				match(T__6);
				setState(100);
				property_description();
				setState(101);
				match(T__7);
				setState(102);
				_la = _input.LA(1);
				if ( !(_la==T__12 || _la==T__13) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(103);
				match(T__8);
				setState(104);
				match(T__8);
				setState(105);
				match(T__11);
				setState(106);
				property_int_val();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(108);
				property_name();
				setState(109);
				match(T__6);
				setState(110);
				property_description();
				setState(111);
				match(T__7);
				setState(112);
				_la = _input.LA(1);
				if ( !(_la==T__14 || _la==T__15) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(113);
				match(T__8);
				setState(114);
				match(T__11);
				setState(115);
				property_float_val();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\35z\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t\13\4"+
		"\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\3\2\3\2\5\2#\n\2\3\3\3\3"+
		"\3\3\3\3\3\3\3\4\3\4\3\4\5\4-\n\4\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b"+
		"\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\13\3\13"+
		"\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\f\3\f\3\f\3\f\3\r\3\r\3\16"+
		"\3\16\3\17\3\17\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\5\20x\n\20\3\20\2\2\21\2\4\6\b\n\f\16\20\22\24\26"+
		"\30\32\34\36\2\6\3\2\24\25\3\2\f\r\3\2\17\20\3\2\21\22\2n\2 \3\2\2\2\4"+
		"$\3\2\2\2\6)\3\2\2\2\b\60\3\2\2\2\n\62\3\2\2\2\f\64\3\2\2\2\16\66\3\2"+
		"\2\2\208\3\2\2\2\22>\3\2\2\2\24F\3\2\2\2\26P\3\2\2\2\30T\3\2\2\2\32V\3"+
		"\2\2\2\34X\3\2\2\2\36w\3\2\2\2 \"\5\4\3\2!#\5\6\4\2\"!\3\2\2\2\"#\3\2"+
		"\2\2#\3\3\2\2\2$%\7\3\2\2%&\7\4\2\2&\'\7\26\2\2\'(\7\5\2\2(\5\3\2\2\2"+
		")*\7\6\2\2*,\7\7\2\2+-\5\36\20\2,+\3\2\2\2,-\3\2\2\2-.\3\2\2\2./\7\b\2"+
		"\2/\7\3\2\2\2\60\61\t\2\2\2\61\t\3\2\2\2\62\63\7\23\2\2\63\13\3\2\2\2"+
		"\64\65\7\24\2\2\65\r\3\2\2\2\66\67\5\b\5\2\67\17\3\2\2\289\7\t\2\29:\5"+
		"\b\5\2:;\7\n\2\2;<\5\b\5\2<=\7\13\2\2=\21\3\2\2\2>?\7\t\2\2?@\5\b\5\2"+
		"@A\7\n\2\2AB\5\b\5\2BC\7\n\2\2CD\5\b\5\2DE\7\13\2\2E\23\3\2\2\2FG\7\t"+
		"\2\2GH\5\b\5\2HI\7\n\2\2IJ\5\b\5\2JK\7\n\2\2KL\5\b\5\2LM\7\n\2\2MN\5\b"+
		"\5\2NO\7\13\2\2O\25\3\2\2\2PQ\7\26\2\2QR\7\7\2\2RS\7\b\2\2S\27\3\2\2\2"+
		"TU\7\30\2\2U\31\3\2\2\2VW\7\27\2\2W\33\3\2\2\2XY\7\26\2\2Y\35\3\2\2\2"+
		"Z[\5\32\16\2[\\\7\t\2\2\\]\5\34\17\2]^\7\n\2\2^_\t\3\2\2_`\7\13\2\2`a"+
		"\7\13\2\2ab\7\16\2\2bc\5\n\6\2cx\3\2\2\2de\5\32\16\2ef\7\t\2\2fg\5\34"+
		"\17\2gh\7\n\2\2hi\t\4\2\2ij\7\13\2\2jk\7\13\2\2kl\7\16\2\2lm\5\f\7\2m"+
		"x\3\2\2\2no\5\32\16\2op\7\t\2\2pq\5\34\17\2qr\7\n\2\2rs\t\5\2\2st\7\13"+
		"\2\2tu\7\16\2\2uv\5\16\b\2vx\3\2\2\2wZ\3\2\2\2wd\3\2\2\2wn\3\2\2\2x\37"+
		"\3\2\2\2\5\",w";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}