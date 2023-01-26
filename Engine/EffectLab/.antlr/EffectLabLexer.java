// Generated from d:\share\Eureka\Engine\EffectLab\EffectLab.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class EffectLabLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, BoolVal=17, 
		IntVal=18, FloatVal=19, String=20, Identity=21, KWIdentity=22, KWTrue=23, 
		KWFalse=24, WhiteSpace=25, LineComment=26, Comment=27;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "BoolVal", 
			"IntVal", "FloatVal", "String", "Identity", "KWIdentity", "KWTrue", "KWFalse", 
			"WhiteSpace", "LineComment", "Comment"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'SourcePath'", "':'", "';'", "'Properties'", "'{'", "'}'", "'('", 
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


	public EffectLabLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "EffectLab.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\35\u00e1\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31"+
		"\t\31\4\32\t\32\4\33\t\33\4\34\t\34\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3"+
		"\2\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5"+
		"\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\f"+
		"\3\f\3\f\3\f\3\f\3\r\3\r\3\16\3\16\3\16\3\16\3\17\3\17\3\17\3\17\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\3\21\3\21\3\21\3\21\3\21\3\21\3\21\3\22\3\22"+
		"\5\22\u0081\n\22\3\23\3\23\7\23\u0085\n\23\f\23\16\23\u0088\13\23\3\24"+
		"\6\24\u008b\n\24\r\24\16\24\u008c\3\24\3\24\7\24\u0091\n\24\f\24\16\24"+
		"\u0094\13\24\3\24\5\24\u0097\n\24\3\25\3\25\7\25\u009b\n\25\f\25\16\25"+
		"\u009e\13\25\3\25\3\25\3\26\3\26\7\26\u00a4\n\26\f\26\16\26\u00a7\13\26"+
		"\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\30\3\30\3\30\3\30\3\30"+
		"\3\31\3\31\3\31\3\31\3\31\3\31\3\32\6\32\u00be\n\32\r\32\16\32\u00bf\3"+
		"\32\3\32\3\33\3\33\3\33\3\33\7\33\u00c8\n\33\f\33\16\33\u00cb\13\33\3"+
		"\33\5\33\u00ce\n\33\3\33\3\33\3\33\3\33\3\34\3\34\3\34\3\34\7\34\u00d8"+
		"\n\34\f\34\16\34\u00db\13\34\3\34\3\34\3\34\3\34\3\34\5\u009c\u00c9\u00d9"+
		"\2\35\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35"+
		"\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\61\32\63\33\65\34\67\35\3\2"+
		"\7\3\2\63;\3\2\62;\5\2C\\aac|\6\2\62;C\\aac|\5\2\13\f\17\17\"\"\2\u00eb"+
		"\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2"+
		"\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2"+
		"\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2"+
		"\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2"+
		"\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\39\3\2\2\2\5D\3"+
		"\2\2\2\7F\3\2\2\2\tH\3\2\2\2\13S\3\2\2\2\rU\3\2\2\2\17W\3\2\2\2\21Y\3"+
		"\2\2\2\23[\3\2\2\2\25]\3\2\2\2\27b\3\2\2\2\31g\3\2\2\2\33i\3\2\2\2\35"+
		"m\3\2\2\2\37q\3\2\2\2!w\3\2\2\2#\u0080\3\2\2\2%\u0082\3\2\2\2\'\u008a"+
		"\3\2\2\2)\u0098\3\2\2\2+\u00a1\3\2\2\2-\u00a8\3\2\2\2/\u00b1\3\2\2\2\61"+
		"\u00b6\3\2\2\2\63\u00bd\3\2\2\2\65\u00c3\3\2\2\2\67\u00d3\3\2\2\29:\7"+
		"U\2\2:;\7q\2\2;<\7w\2\2<=\7t\2\2=>\7e\2\2>?\7g\2\2?@\7R\2\2@A\7c\2\2A"+
		"B\7v\2\2BC\7j\2\2C\4\3\2\2\2DE\7<\2\2E\6\3\2\2\2FG\7=\2\2G\b\3\2\2\2H"+
		"I\7R\2\2IJ\7t\2\2JK\7q\2\2KL\7r\2\2LM\7g\2\2MN\7t\2\2NO\7v\2\2OP\7k\2"+
		"\2PQ\7g\2\2QR\7u\2\2R\n\3\2\2\2ST\7}\2\2T\f\3\2\2\2UV\7\177\2\2V\16\3"+
		"\2\2\2WX\7*\2\2X\20\3\2\2\2YZ\7.\2\2Z\22\3\2\2\2[\\\7+\2\2\\\24\3\2\2"+
		"\2]^\7d\2\2^_\7q\2\2_`\7q\2\2`a\7n\2\2a\26\3\2\2\2bc\7D\2\2cd\7q\2\2d"+
		"e\7q\2\2ef\7n\2\2f\30\3\2\2\2gh\7?\2\2h\32\3\2\2\2ij\7K\2\2jk\7p\2\2k"+
		"l\7v\2\2l\34\3\2\2\2mn\7k\2\2no\7p\2\2op\7v\2\2p\36\3\2\2\2qr\7H\2\2r"+
		"s\7n\2\2st\7q\2\2tu\7c\2\2uv\7v\2\2v \3\2\2\2wx\7h\2\2xy\7n\2\2yz\7q\2"+
		"\2z{\7c\2\2{|\7v\2\2|}\7\"\2\2}\"\3\2\2\2~\u0081\5/\30\2\177\u0081\5\61"+
		"\31\2\u0080~\3\2\2\2\u0080\177\3\2\2\2\u0081$\3\2\2\2\u0082\u0086\t\2"+
		"\2\2\u0083\u0085\t\3\2\2\u0084\u0083\3\2\2\2\u0085\u0088\3\2\2\2\u0086"+
		"\u0084\3\2\2\2\u0086\u0087\3\2\2\2\u0087&\3\2\2\2\u0088\u0086\3\2\2\2"+
		"\u0089\u008b\t\3\2\2\u008a\u0089\3\2\2\2\u008b\u008c\3\2\2\2\u008c\u008a"+
		"\3\2\2\2\u008c\u008d\3\2\2\2\u008d\u008e\3\2\2\2\u008e\u0092\13\2\2\2"+
		"\u008f\u0091\t\3\2\2\u0090\u008f\3\2\2\2\u0091\u0094\3\2\2\2\u0092\u0090"+
		"\3\2\2\2\u0092\u0093\3\2\2\2\u0093\u0096\3\2\2\2\u0094\u0092\3\2\2\2\u0095"+
		"\u0097\7h\2\2\u0096\u0095\3\2\2\2\u0096\u0097\3\2\2\2\u0097(\3\2\2\2\u0098"+
		"\u009c\7$\2\2\u0099\u009b\13\2\2\2\u009a\u0099\3\2\2\2\u009b\u009e\3\2"+
		"\2\2\u009c\u009d\3\2\2\2\u009c\u009a\3\2\2\2\u009d\u009f\3\2\2\2\u009e"+
		"\u009c\3\2\2\2\u009f\u00a0\7$\2\2\u00a0*\3\2\2\2\u00a1\u00a5\t\4\2\2\u00a2"+
		"\u00a4\t\5\2\2\u00a3\u00a2\3\2\2\2\u00a4\u00a7\3\2\2\2\u00a5\u00a3\3\2"+
		"\2\2\u00a5\u00a6\3\2\2\2\u00a6,\3\2\2\2\u00a7\u00a5\3\2\2\2\u00a8\u00a9"+
		"\7K\2\2\u00a9\u00aa\7f\2\2\u00aa\u00ab\7g\2\2\u00ab\u00ac\7p\2\2\u00ac"+
		"\u00ad\7v\2\2\u00ad\u00ae\7k\2\2\u00ae\u00af\7v\2\2\u00af\u00b0\7{\2\2"+
		"\u00b0.\3\2\2\2\u00b1\u00b2\7v\2\2\u00b2\u00b3\7t\2\2\u00b3\u00b4\7w\2"+
		"\2\u00b4\u00b5\7g\2\2\u00b5\60\3\2\2\2\u00b6\u00b7\7h\2\2\u00b7\u00b8"+
		"\7c\2\2\u00b8\u00b9\7n\2\2\u00b9\u00ba\7u\2\2\u00ba\u00bb\7g\2\2\u00bb"+
		"\62\3\2\2\2\u00bc\u00be\t\6\2\2\u00bd\u00bc\3\2\2\2\u00be\u00bf\3\2\2"+
		"\2\u00bf\u00bd\3\2\2\2\u00bf\u00c0\3\2\2\2\u00c0\u00c1\3\2\2\2\u00c1\u00c2"+
		"\b\32\2\2\u00c2\64\3\2\2\2\u00c3\u00c4\7\61\2\2\u00c4\u00c5\7\61\2\2\u00c5"+
		"\u00c9\3\2\2\2\u00c6\u00c8\13\2\2\2\u00c7\u00c6\3\2\2\2\u00c8\u00cb\3"+
		"\2\2\2\u00c9\u00ca\3\2\2\2\u00c9\u00c7\3\2\2\2\u00ca\u00cd\3\2\2\2\u00cb"+
		"\u00c9\3\2\2\2\u00cc\u00ce\7\17\2\2\u00cd\u00cc\3\2\2\2\u00cd\u00ce\3"+
		"\2\2\2\u00ce\u00cf\3\2\2\2\u00cf\u00d0\7\f\2\2\u00d0\u00d1\3\2\2\2\u00d1"+
		"\u00d2\b\33\2\2\u00d2\66\3\2\2\2\u00d3\u00d4\7\61\2\2\u00d4\u00d5\7,\2"+
		"\2\u00d5\u00d9\3\2\2\2\u00d6\u00d8\13\2\2\2\u00d7\u00d6\3\2\2\2\u00d8"+
		"\u00db\3\2\2\2\u00d9\u00da\3\2\2\2\u00d9\u00d7\3\2\2\2\u00da\u00dc\3\2"+
		"\2\2\u00db\u00d9\3\2\2\2\u00dc\u00dd\7,\2\2\u00dd\u00de\7\61\2\2\u00de"+
		"\u00df\3\2\2\2\u00df\u00e0\b\34\2\2\u00e08\3\2\2\2\16\2\u0080\u0086\u008c"+
		"\u0092\u0096\u009c\u00a5\u00bf\u00c9\u00cd\u00d9\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}