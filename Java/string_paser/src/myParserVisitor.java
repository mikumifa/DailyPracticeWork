// Generated from ./src/myParser.g4 by ANTLR 4.9.1
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link myParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface myParserVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link myParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(myParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link myParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStatement(myParser.StatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link myParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpression(myParser.ExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link myParser#value}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitValue(myParser.ValueContext ctx);
}