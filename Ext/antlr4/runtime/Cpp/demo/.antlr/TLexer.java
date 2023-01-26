// Generated from d:\share\Eureka\Ext\antlr4\runtime\Cpp\demo\TLexer.g4 by ANTLR 4.9.2
/* lexer header section */
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class TLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		DUMMY=1, Return=2, Continue=3, INT=4, Digit=5, ID=6, LessThan=7, GreaterThan=8, 
		Equal=9, And=10, Colon=11, Semicolon=12, Plus=13, Minus=14, Star=15, OpenPar=16, 
		ClosePar=17, OpenCurly=18, CloseCurly=19, QuestionMark=20, Comma=21, String=22, 
		Foo=23, Bar=24, Any=25, Comment=26, WS=27, Dot=28, DotDot=29, Dollar=30, 
		Ampersand=31;
	public static final int
		CommentsChannel=2, DirectiveChannel=3;
	public static final int
		Mode1=1, Mode2=2;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN", "CommentsChannel", "DirectiveChannel"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE", "Mode1", "Mode2"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"Return", "Continue", "INT", "Digit", "ID", "LETTER", "LessThan", "GreaterThan", 
			"Equal", "And", "Colon", "Semicolon", "Plus", "Minus", "Star", "OpenPar", 
			"ClosePar", "OpenCurly", "CloseCurly", "QuestionMark", "Comma", "Dollar", 
			"Ampersand", "String", "Foo", "Bar", "Any", "Comment", "WS", "Baz", "Dot", 
			"DotDot"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, "'return'", "'continue'", null, null, null, "'<'", "'>'", 
			"'='", "'and'", "':'", "';'", "'+'", "'-'", "'*'", "'('", "')'", "'{'", 
			"'}'", "'?'", "','", null, null, null, null, null, null, "'.'", "'..'", 
			"'$'", "'&'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "DUMMY", "Return", "Continue", "INT", "Digit", "ID", "LessThan", 
			"GreaterThan", "Equal", "And", "Colon", "Semicolon", "Plus", "Minus", 
			"Star", "OpenPar", "ClosePar", "OpenCurly", "CloseCurly", "QuestionMark", 
			"Comma", "String", "Foo", "Bar", "Any", "Comment", "WS", "Dot", "DotDot", 
			"Dollar", "Ampersand"
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

	/* public lexer declarations section */
	bool canTestFoo() { return true; }
	bool isItFoo() { return true; }
	bool isItBar() { return true; }

	void myFooLexerAction() { /* do something*/ };
	void myBarLexerAction() { /* do something*/ };


	public TLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "TLexer.g4"; }

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

	@Override
	public void action(RuleContext _localctx, int ruleIndex, int actionIndex) {
		switch (ruleIndex) {
		case 24:
			Foo_action((RuleContext)_localctx, actionIndex);
			break;
		case 25:
			Bar_action((RuleContext)_localctx, actionIndex);
			break;
		}
	}
	private void Foo_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 0:
			 myFooLexerAction(); 
			break;
		}
	}
	private void Bar_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 1:
			 myBarLexerAction(); 
			break;
		}
	}
	@Override
	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 24:
			return Foo_sempred((RuleContext)_localctx, predIndex);
		case 25:
			return Bar_sempred((RuleContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean Foo_sempred(RuleContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return canTestFoo();
		case 1:
			return isItFoo();
		}
		return true;
	}
	private boolean Bar_sempred(RuleContext _localctx, int predIndex) {
		switch (predIndex) {
		case 2:
			return isItBar();
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2!\u00d3\b\1\b\1\b"+
		"\1\4\2\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n"+
		"\t\n\4\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21"+
		"\4\22\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30"+
		"\4\31\t\31\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37"+
		"\4 \t \4!\t!\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\4\6\4W\n\4\r\4\16\4X\3\5\3\5\3\6\3\6\3\6\7\6`\n\6\f\6\16\6c\13"+
		"\6\3\7\3\7\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\13\3\13\3\f\3\f\3\r\3\r"+
		"\3\16\3\16\3\17\3\17\3\20\3\20\3\21\3\21\3\22\3\22\3\23\3\23\3\23\3\23"+
		"\3\24\3\24\3\24\3\24\3\25\3\25\3\26\3\26\3\26\3\26\3\27\3\27\3\27\3\27"+
		"\3\27\3\30\3\30\3\30\3\30\3\31\3\31\7\31\u0098\n\31\f\31\16\31\u009b\13"+
		"\31\3\31\3\31\3\32\3\32\3\32\3\32\3\32\3\32\3\32\3\32\3\33\3\33\3\33\3"+
		"\33\3\33\3\33\3\33\3\34\3\34\3\34\5\34\u00b1\n\34\3\34\3\34\3\34\3\35"+
		"\3\35\7\35\u00b8\n\35\f\35\16\35\u00bb\13\35\3\35\5\35\u00be\n\35\3\35"+
		"\3\35\3\35\3\35\3\36\6\36\u00c5\n\36\r\36\16\36\u00c6\3\36\3\36\3\37\3"+
		"\37\3\37\3\37\3 \3 \3!\3!\3!\3\u0099\2\"\5\4\7\5\t\6\13\7\r\b\17\2\21"+
		"\t\23\n\25\13\27\f\31\r\33\16\35\17\37\20!\21#\22%\23\'\24)\25+\26-\27"+
		"/ \61!\63\30\65\31\67\329\33;\34=\35?\2A\36C\37\5\2\3\4\5\3\2\62;\4\2"+
		"\f\f\17\17\5\2\13\f\17\17\"\"\3\5\2C\2\\\2c\2|\2\u0082\2\1\22\u00d6\2"+
		"\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\21\3\2\2"+
		"\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2"+
		"\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2"+
		"\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3\2\2\2\2\63\3\2\2\2"+
		"\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2\2=\3\2\2\2\3A\3\2\2\2"+
		"\4C\3\2\2\2\5E\3\2\2\2\7L\3\2\2\2\tV\3\2\2\2\13Z\3\2\2\2\r\\\3\2\2\2\17"+
		"d\3\2\2\2\21f\3\2\2\2\23h\3\2\2\2\25j\3\2\2\2\27l\3\2\2\2\31p\3\2\2\2"+
		"\33r\3\2\2\2\35t\3\2\2\2\37v\3\2\2\2!x\3\2\2\2#z\3\2\2\2%|\3\2\2\2\'~"+
		"\3\2\2\2)\u0082\3\2\2\2+\u0086\3\2\2\2-\u0088\3\2\2\2/\u008c\3\2\2\2\61"+
		"\u0091\3\2\2\2\63\u0095\3\2\2\2\65\u009e\3\2\2\2\67\u00a6\3\2\2\29\u00ad"+
		"\3\2\2\2;\u00b5\3\2\2\2=\u00c4\3\2\2\2?\u00ca\3\2\2\2A\u00ce\3\2\2\2C"+
		"\u00d0\3\2\2\2EF\7t\2\2FG\7g\2\2GH\7v\2\2HI\7w\2\2IJ\7t\2\2JK\7p\2\2K"+
		"\6\3\2\2\2LM\7e\2\2MN\7q\2\2NO\7p\2\2OP\7v\2\2PQ\7k\2\2QR\7p\2\2RS\7w"+
		"\2\2ST\7g\2\2T\b\3\2\2\2UW\5\13\5\2VU\3\2\2\2WX\3\2\2\2XV\3\2\2\2XY\3"+
		"\2\2\2Y\n\3\2\2\2Z[\t\2\2\2[\f\3\2\2\2\\a\5\17\7\2]`\5\17\7\2^`\4\62;"+
		"\2_]\3\2\2\2_^\3\2\2\2`c\3\2\2\2a_\3\2\2\2ab\3\2\2\2b\16\3\2\2\2ca\3\2"+
		"\2\2de\t\5\2\2e\20\3\2\2\2fg\7>\2\2g\22\3\2\2\2hi\7@\2\2i\24\3\2\2\2j"+
		"k\7?\2\2k\26\3\2\2\2lm\7c\2\2mn\7p\2\2no\7f\2\2o\30\3\2\2\2pq\7<\2\2q"+
		"\32\3\2\2\2rs\7=\2\2s\34\3\2\2\2tu\7-\2\2u\36\3\2\2\2vw\7/\2\2w \3\2\2"+
		"\2xy\7,\2\2y\"\3\2\2\2z{\7*\2\2{$\3\2\2\2|}\7+\2\2}&\3\2\2\2~\177\7}\2"+
		"\2\177\u0080\3\2\2\2\u0080\u0081\b\23\2\2\u0081(\3\2\2\2\u0082\u0083\7"+
		"\177\2\2\u0083\u0084\3\2\2\2\u0084\u0085\b\24\3\2\u0085*\3\2\2\2\u0086"+
		"\u0087\7A\2\2\u0087,\3\2\2\2\u0088\u0089\7.\2\2\u0089\u008a\3\2\2\2\u008a"+
		"\u008b\b\26\4\2\u008b.\3\2\2\2\u008c\u008d\7&\2\2\u008d\u008e\3\2\2\2"+
		"\u008e\u008f\b\27\5\2\u008f\u0090\b\27\6\2\u0090\60\3\2\2\2\u0091\u0092"+
		"\7(\2\2\u0092\u0093\3\2\2\2\u0093\u0094\b\30\7\2\u0094\62\3\2\2\2\u0095"+
		"\u0099\7$\2\2\u0096\u0098\13\2\2\2\u0097\u0096\3\2\2\2\u0098\u009b\3\2"+
		"\2\2\u0099\u009a\3\2\2\2\u0099\u0097\3\2\2\2\u009a\u009c\3\2\2\2\u009b"+
		"\u0099\3\2\2\2\u009c\u009d\7$\2\2\u009d\64\3\2\2\2\u009e\u009f\6\32\2"+
		"\2\u009f\u00a0\7h\2\2\u00a0\u00a1\7q\2\2\u00a1\u00a2\7q\2\2\u00a2\u00a3"+
		"\3\2\2\2\u00a3\u00a4\6\32\3\2\u00a4\u00a5\b\32\b\2\u00a5\66\3\2\2\2\u00a6"+
		"\u00a7\7d\2\2\u00a7\u00a8\7c\2\2\u00a8\u00a9\7t\2\2\u00a9\u00aa\3\2\2"+
		"\2\u00aa\u00ab\6\33\4\2\u00ab\u00ac\b\33\t\2\u00ac8\3\2\2\2\u00ad\u00ae"+
		"\5\65\32\2\u00ae\u00b0\5A \2\u00af\u00b1\5\67\33\2\u00b0\u00af\3\2\2\2"+
		"\u00b0\u00b1\3\2\2\2\u00b1\u00b2\3\2\2\2\u00b2\u00b3\5C!\2\u00b3\u00b4"+
		"\5?\37\2\u00b4:\3\2\2\2\u00b5\u00b9\7%\2\2\u00b6\u00b8\n\3\2\2\u00b7\u00b6"+
		"\3\2\2\2\u00b8\u00bb\3\2\2\2\u00b9\u00b7\3\2\2\2\u00b9\u00ba\3\2\2\2\u00ba"+
		"\u00bd\3\2\2\2\u00bb\u00b9\3\2\2\2\u00bc\u00be\7\17\2\2\u00bd\u00bc\3"+
		"\2\2\2\u00bd\u00be\3\2\2\2\u00be\u00bf\3\2\2\2\u00bf\u00c0\7\f\2\2\u00c0"+
		"\u00c1\3\2\2\2\u00c1\u00c2\b\35\n\2\u00c2<\3\2\2\2\u00c3\u00c5\t\4\2\2"+
		"\u00c4\u00c3\3\2\2\2\u00c5\u00c6\3\2\2\2\u00c6\u00c4\3\2\2\2\u00c6\u00c7"+
		"\3\2\2\2\u00c7\u00c8\3\2\2\2\u00c8\u00c9\b\36\13\2\u00c9>\3\2\2\2\u00ca"+
		"\u00cb\7D\2\2\u00cb\u00cc\7c\2\2\u00cc\u00cd\7|\2\2\u00cd@\3\2\2\2\u00ce"+
		"\u00cf\7\60\2\2\u00cfB\3\2\2\2\u00d0\u00d1\7\60\2\2\u00d1\u00d2\7\60\2"+
		"\2\u00d2D\3\2\2\2\r\2\3\4X_a\u0099\u00b0\u00b9\u00bd\u00c6\f\7\3\2\6\2"+
		"\2\b\2\2\5\2\2\4\3\2\t\3\2\3\32\2\3\33\3\2\4\2\2e\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}