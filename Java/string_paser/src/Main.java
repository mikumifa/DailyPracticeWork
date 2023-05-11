import java.io.IOException;
import java.util.*;

import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.RuleNode;
import org.antlr.v4.runtime.tree.TerminalNode;


class Visitor extends myParserBaseVisitor<Object> {
    private Map<String, String> variables = new HashMap<>();

    @Override
    public Object visitProgram(myParser.ProgramContext ctx) {
        for (myParser.StatementContext statement : ctx.statement()) {
            visit(statement);
        }
        return null;
    }

    @Override
    public Object visitStatement(myParser.StatementContext ctx) {
        if (ctx.APPEND() != null) {
            String id = ctx.ID().getText();
            String currentValue = variables.get(id);
            String newValue = (String) visit(ctx.expression());
            if (currentValue == null) {
                variables.put(id, newValue);
            } else {
                variables.put(id, currentValue + newValue);
            }
            return null;
        } else if (ctx.LIST() != null) {
            System.out.printf("Identifier list(%d)\n",(variables.size()));
            for (String key : variables.keySet()) {
                System.out.println(key + ": \"" + variables.get(key)+"\"");
            }
            return null;
        } else if (ctx.EXIT() != null) {
            System.exit(0);
            return null;
        } else if (ctx.PRINT() != null) {
            System.out.println(visit(ctx.expression()));
            return null;
        } else if (ctx.PRINTLENGTH() != null) {
            String result = (String) visit(ctx.expression());
            System.out.println("Length is:"+result.length());
            return null;
        } else if (ctx.PRINTWORDCOUNT() != null) {
            String result = (String) visit(ctx.expression());
            String[] words = result.split("\\s+");
            System.out.println("Wordcount is: "+words.length);
            return null;
        } else if (ctx.PRINTWORDS() != null) {
            String result = (String) visit(ctx.expression());
            String[] words = result.split("\\s+");
            System.out.println("words are:");
            for (String word : words) {
                System.out.println(word);
            }
            return null;
        } else if (ctx.SET() != null) {
            String id = ctx.ID().getText();
            String value = (String) visit(ctx.expression());
            variables.put(id, value);
            return null;
        } else if (ctx.REVERSE() != null) {
            String id = ctx.ID().getText();
            String value = variables.get(id);
            String[] words = value.split("\\s+");
            String[] newWords = new String[words.length];
            for (int i = 0; i < words.length; i++) {
                newWords[words.length-1-i]=words[i];

            }
            variables.put(id, String.join(",",newWords));
            return null;
        } else {
            throw new RuntimeException("Unknown statement type: " + ctx.getText());
        }
    }

    @Override
    public String visitExpression(myParser.ExpressionContext ctx) {
        StringBuilder result = new StringBuilder(visitValue(ctx.value(0))); // 获得第一个值
        for (int i = 1; i < ctx.value().size(); i++) {
            String value = visitValue(ctx.value(i)); // 获得后续值
            result.append(value); // 拼接字符串
        }
        return result.toString();
    }

    @Override
    public String visitValue(myParser.ValueContext ctx) {
        if (ctx.ID() != null) {
            String id = ctx.ID().getText();
            String value = variables.get(id);
            if (value == null) {
                throw new RuntimeException("Variable " + id + " is not defined.");
            }
            return value;
        } else {
            return ctx.LITERAL().getText();
        }
    }
}


class ErrorListener extends BaseErrorListener {
    public boolean error = false;

    @Override
    public void syntaxError(Recognizer<?, ?> recognizer, Object offendingSymbol, int line, int charPositionInLine, String msg, RecognitionException e) {
        System.err.printf("Error type B at Line %d: %s%n", line, msg);

    }

}

public class Main {

    public static String[] parserRuleName;

    public static void main(String[] args) throws IOException {


        myLexer lexer = new myLexer(null); // 创建词法分析器，将输入流传递给它
        myParser parser = new myParser(null); // 创建语法分析器，将词法分析器的输出流传递给它

        parser.removeErrorListeners();
        ErrorListener myErrorListener = new ErrorListener();
        parser.addErrorListener(myErrorListener);
        Visitor visitor = new Visitor();
        Scanner scanner = new Scanner(System.in);
        String line;
        while ((line = scanner.nextLine()) != null) {
            line=line.replaceAll("SPACE","\" \"");
            line=line.replaceAll("TAB","\"\t\"");
            line=line.replaceAll("NEWLINE","\"\n\"");
            CharStream inputStream = CharStreams.fromString(line);
            lexer.setInputStream(inputStream); // 设置词法分析器的输入流为当前行
            CommonTokenStream tokenStream = new CommonTokenStream(lexer);
            parser.setTokenStream(tokenStream); // 设置语法分析器的输入流为词法分析器的输出流
            ParseTree tree = parser.program();
            visitor.visit(tree);
        }
    }
}
