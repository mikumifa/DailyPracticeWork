// Generated from c:\Code\xy_Paser\src\myParser.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class myParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		APPEND=1, EXIT=2, LIST=3, PRINT=4, PRINTLENGTH=5, PRINTWORDS=6, PRINTWORDCOUNT=7, 
		REVERSE=8, SET=9, CONSTANT=10, END=11, PLUS=12, ID=13, LITERAL=14;
	public static final int
		RULE_program = 0, RULE_statement = 1, RULE_expression = 2, RULE_value = 3;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "statement", "expression", "value"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'append'", "'exit'", "'list'", "'print'", "'printlength'", "'printwords'", 
			"'printwordcount'", "'reverse'", "'set'", null, "';'", "'+'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "APPEND", "EXIT", "LIST", "PRINT", "PRINTLENGTH", "PRINTWORDS", 
			"PRINTWORDCOUNT", "REVERSE", "SET", "CONSTANT", "END", "PLUS", "ID", 
			"LITERAL"
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
	public String getGrammarFileName() { return "myParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public myParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class ProgramContext extends ParserRuleContext {
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(11);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << APPEND) | (1L << EXIT) | (1L << LIST) | (1L << PRINT) | (1L << PRINTLENGTH) | (1L << PRINTWORDS) | (1L << PRINTWORDCOUNT) | (1L << REVERSE) | (1L << SET))) != 0)) {
				{
				{
				setState(8);
				statement();
				}
				}
				setState(13);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class StatementContext extends ParserRuleContext {
		public TerminalNode APPEND() { return getToken(myParser.APPEND, 0); }
		public TerminalNode ID() { return getToken(myParser.ID, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode END() { return getToken(myParser.END, 0); }
		public TerminalNode LIST() { return getToken(myParser.LIST, 0); }
		public TerminalNode EXIT() { return getToken(myParser.EXIT, 0); }
		public TerminalNode PRINT() { return getToken(myParser.PRINT, 0); }
		public TerminalNode PRINTLENGTH() { return getToken(myParser.PRINTLENGTH, 0); }
		public TerminalNode PRINTWORDS() { return getToken(myParser.PRINTWORDS, 0); }
		public TerminalNode PRINTWORDCOUNT() { return getToken(myParser.PRINTWORDCOUNT, 0); }
		public TerminalNode SET() { return getToken(myParser.SET, 0); }
		public TerminalNode REVERSE() { return getToken(myParser.REVERSE, 0); }
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_statement);
		try {
			setState(47);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case APPEND:
				enterOuterAlt(_localctx, 1);
				{
				setState(14);
				match(APPEND);
				setState(15);
				match(ID);
				setState(16);
				expression();
				setState(17);
				match(END);
				}
				break;
			case LIST:
				enterOuterAlt(_localctx, 2);
				{
				setState(19);
				match(LIST);
				setState(20);
				match(END);
				}
				break;
			case EXIT:
				enterOuterAlt(_localctx, 3);
				{
				setState(21);
				match(EXIT);
				setState(22);
				match(END);
				}
				break;
			case PRINT:
				enterOuterAlt(_localctx, 4);
				{
				setState(23);
				match(PRINT);
				setState(24);
				expression();
				setState(25);
				match(END);
				}
				break;
			case PRINTLENGTH:
				enterOuterAlt(_localctx, 5);
				{
				setState(27);
				match(PRINTLENGTH);
				setState(28);
				expression();
				setState(29);
				match(END);
				}
				break;
			case PRINTWORDS:
				enterOuterAlt(_localctx, 6);
				{
				setState(31);
				match(PRINTWORDS);
				setState(32);
				expression();
				setState(33);
				match(END);
				}
				break;
			case PRINTWORDCOUNT:
				enterOuterAlt(_localctx, 7);
				{
				setState(35);
				match(PRINTWORDCOUNT);
				setState(36);
				expression();
				setState(37);
				match(END);
				}
				break;
			case SET:
				enterOuterAlt(_localctx, 8);
				{
				setState(39);
				match(SET);
				setState(40);
				match(ID);
				setState(41);
				expression();
				setState(42);
				match(END);
				}
				break;
			case REVERSE:
				enterOuterAlt(_localctx, 9);
				{
				setState(44);
				match(REVERSE);
				setState(45);
				match(ID);
				setState(46);
				match(END);
				}
				break;
			default:
				throw new NoViableAltException(this);
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

	public static class ExpressionContext extends ParserRuleContext {
		public List<ValueContext> value() {
			return getRuleContexts(ValueContext.class);
		}
		public ValueContext value(int i) {
			return getRuleContext(ValueContext.class,i);
		}
		public List<TerminalNode> PLUS() { return getTokens(myParser.PLUS); }
		public TerminalNode PLUS(int i) {
			return getToken(myParser.PLUS, i);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_expression);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(49);
			value();
			setState(54);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==PLUS) {
				{
				{
				setState(50);
				match(PLUS);
				setState(51);
				value();
				}
				}
				setState(56);
				_errHandler.sync(this);
				_la = _input.LA(1);
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

	public static class ValueContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(myParser.ID, 0); }
		public TerminalNode LITERAL() { return getToken(myParser.LITERAL, 0); }
		public ValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_value; }
	}

	public final ValueContext value() throws RecognitionException {
		ValueContext _localctx = new ValueContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_value);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(57);
			_la = _input.LA(1);
			if ( !(_la==ID || _la==LITERAL) ) {
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

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\20>\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\3\2\7\2\f\n\2\f\2\16\2\17\13\2\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\5\3\62\n\3\3\4\3\4\3\4\7\4"+
		"\67\n\4\f\4\16\4:\13\4\3\5\3\5\3\5\2\2\6\2\4\6\b\2\3\3\2\17\20\2C\2\r"+
		"\3\2\2\2\4\61\3\2\2\2\6\63\3\2\2\2\b;\3\2\2\2\n\f\5\4\3\2\13\n\3\2\2\2"+
		"\f\17\3\2\2\2\r\13\3\2\2\2\r\16\3\2\2\2\16\3\3\2\2\2\17\r\3\2\2\2\20\21"+
		"\7\3\2\2\21\22\7\17\2\2\22\23\5\6\4\2\23\24\7\r\2\2\24\62\3\2\2\2\25\26"+
		"\7\5\2\2\26\62\7\r\2\2\27\30\7\4\2\2\30\62\7\r\2\2\31\32\7\6\2\2\32\33"+
		"\5\6\4\2\33\34\7\r\2\2\34\62\3\2\2\2\35\36\7\7\2\2\36\37\5\6\4\2\37 \7"+
		"\r\2\2 \62\3\2\2\2!\"\7\b\2\2\"#\5\6\4\2#$\7\r\2\2$\62\3\2\2\2%&\7\t\2"+
		"\2&\'\5\6\4\2\'(\7\r\2\2(\62\3\2\2\2)*\7\13\2\2*+\7\17\2\2+,\5\6\4\2,"+
		"-\7\r\2\2-\62\3\2\2\2./\7\n\2\2/\60\7\17\2\2\60\62\7\r\2\2\61\20\3\2\2"+
		"\2\61\25\3\2\2\2\61\27\3\2\2\2\61\31\3\2\2\2\61\35\3\2\2\2\61!\3\2\2\2"+
		"\61%\3\2\2\2\61)\3\2\2\2\61.\3\2\2\2\62\5\3\2\2\2\638\5\b\5\2\64\65\7"+
		"\16\2\2\65\67\5\b\5\2\66\64\3\2\2\2\67:\3\2\2\28\66\3\2\2\289\3\2\2\2"+
		"9\7\3\2\2\2:8\3\2\2\2;<\t\2\2\2<\t\3\2\2\2\5\r\618";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}