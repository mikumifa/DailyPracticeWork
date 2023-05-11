// Generated from ./src/myParser.g4 by ANTLR 4.9.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link myParser}.
 */
public interface myParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link myParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(myParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link myParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(myParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link myParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(myParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link myParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(myParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link myParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(myParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link myParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(myParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link myParser#value}.
	 * @param ctx the parse tree
	 */
	void enterValue(myParser.ValueContext ctx);
	/**
	 * Exit a parse tree produced by {@link myParser#value}.
	 * @param ctx the parse tree
	 */
	void exitValue(myParser.ValueContext ctx);
}