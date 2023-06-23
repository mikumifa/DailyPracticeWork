package org.example;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.swing.*;
import javax.swing.Timer;
import java.awt.*;
import java.awt.List;
import java.awt.event.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

public class MathTestApp {
    private JFrame frame;
    private JPanel mainPanel, examPanel, controlPanel;
    private CardLayout cardLayout;
    private JTextField nameField, studentIdField, classField;
    private JButton startExamButton, submitButton, nextPageButton, prevPageButton;
    private Timer examTimer;
    private int questionCount = 50;
    private int per=5;
    private String allFile = "results.txt";
    private String errorFile = "errors.txt";
    private int testDuration = questionCount * 2;
    private JLabel countdownLabel;
    private long startTime;
    HashMap<String, String> answerMap = new HashMap<String, String>();
    HashMap<String, String> correctAnswerMap = new HashMap<String, String>();

    public class QuestionPanel extends JPanel {
        private JLabel questionLabel;
        private JTextField answerField;
        private String question;
        public QuestionPanel(String question) {
            setLayout(new BorderLayout());
            this.question=question;
            questionLabel = new JLabel(question + " = ");
            answerField = new JTextField(3);
            add(questionLabel, BorderLayout.WEST);
            add(answerField, BorderLayout.CENTER);
        }

        public String getAnswer() {
            return answerField.getText();
        }
        public String getQuestion() {
            return question;
        }
    }

    public MathTestApp() {
        frame = new JFrame("小学计算考试练习系统");
        mainPanel = new JPanel(new BorderLayout());
        examPanel = new JPanel();
        controlPanel = new JPanel();
        cardLayout = new CardLayout();
        examPanel.setLayout(cardLayout);
        examPanel.setBackground(Color.WHITE);
         nameField = new JTextField(5);
        studentIdField = new JTextField(5);
        classField = new JTextField(5);

        startExamButton = new JButton("开始考试");
        submitButton = new JButton("交卷");
        nextPageButton = new JButton("下一页");
        prevPageButton = new JButton("上一页");

        controlPanel.add(new JLabel("姓名:"));
        controlPanel.add(nameField);
        controlPanel.add(new JLabel("学号:"));
        controlPanel.add(studentIdField);
        controlPanel.add(new JLabel("班级:"));
        controlPanel.add(classField);
        controlPanel.add(startExamButton);


        mainPanel.add(controlPanel, BorderLayout.NORTH);
        mainPanel.add(examPanel, BorderLayout.CENTER);
        frame.getContentPane().add(mainPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(600, 50+20*per);
        frame.setVisible(true);
        // 添加开始考试按钮的事件监听器
        startExamButton.addActionListener(e -> {
                    // 在此处生成数学问题，并开始计时
            answerMap.clear();
            correctAnswerMap.clear();
                    examPanel.removeAll(); // 清除之前的内容
                    controlPanel.add(submitButton);
                    startExamButton.setVisible(false);
                    controlPanel.add(prevPageButton);
                    controlPanel.add(nextPageButton);
                    for (int i = 0; i < questionCount/per; i++) {
                        JPanel questionPanel = new JPanel(new GridLayout(0, 1));
                        for (int j = 0; j <per;j++) {
                            int index =i*per+j;
                            String question = generateQuestion();
                            QuestionPanel questionLabel = new QuestionPanel("(" + (index + 1) + ")  " + question);
                            ScriptEngineManager manager = new ScriptEngineManager();
                            ScriptEngine se = manager.getEngineByName("js");
                            try {
                                int result = (int) se.eval(question);
                                correctAnswerMap.put("(" + (index + 1) + ")  " + question, result + "");
                            } catch (ScriptException ex) {
                                throw new RuntimeException(ex);
                            }
                            questionPanel.add(questionLabel);
                            examPanel.add(questionPanel, "Question" + index);
                        }

                    }
                    startExam(testDuration);
                    cardLayout.show(examPanel, "Question0");
                    // 重新验证和重绘窗口
                    examPanel.revalidate();
                    examPanel.repaint();
                    nextPageButton.addActionListener(e2 -> {
                        // 使用 CardLayout 的 next 方法切换到下一题
                        saveAnswerToMap(examPanel);
                        cardLayout.next(examPanel);

                    });

                    prevPageButton.addActionListener(e2 -> {
                        saveAnswerToMap(examPanel);
                        cardLayout.previous(examPanel);
                    });
                    submitButton.addActionListener(e2 -> {
                        submitExam();
                        frame.setVisible(false);
                    });

                }

        );


    }

    public void saveAnswerToMap(JPanel examPanel) {
        // 获取问题和答案
        Component[] components = examPanel.getComponents(); // 获取examPanel中的所有组件
        for (Component component : components) {
            for (Component c : ((JPanel)component).getComponents()) {
                if (c instanceof QuestionPanel) {
                    QuestionPanel questionPanel = (QuestionPanel) c;
                    String question = questionPanel.getQuestion();
                    String answer=questionPanel.getAnswer();
                    answerMap.put(question, answer);
                }
            }
        }
    }

    private void startExam(int durationInMinutes) {
        countdownLabel = new JLabel();
        countdownLabel.setHorizontalAlignment(SwingConstants.CENTER);
        controlPanel.add(countdownLabel, BorderLayout.CENTER);
        startTime = System.currentTimeMillis();
        int delay = durationInMinutes * 60 * 1000; // 转换为毫秒

        examTimer = new Timer(1000, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                long elapsedTime = System.currentTimeMillis() - startTime;
                long remainingTime = delay - elapsedTime;
                if (remainingTime <= 0) {
                    // 时间到，提交答案并结束考试
                    submitExam();
                } else {
                    int minutes = (int) (remainingTime / (60 * 1000));
                    int seconds = (int) ((remainingTime / 1000) % 60);
                    countdownLabel.setText(String.format("%02d:%02d", minutes, seconds));
                }
            }
        });
        examTimer.setRepeats(true); // 确保计时器只触发一次
        examTimer.start();
    }

    private void submitExam() {
        if (examTimer != null) {
            examTimer.stop();
        }
        String name = nameField.getText();
        String studentId = studentIdField.getText();
        String studentClass = classField.getText();
        saveAnswerToMap(examPanel);
        saveResultsToFile(name, studentId, studentClass);
    }

    // 使用自定义比较器进行排序

    private void saveResultsToFile(String studentName, String studentId, String studentClass
                                   ) {
        int wrongCount = 0;
        StringBuilder resultError = new StringBuilder();
        StringBuilder resultAll = new StringBuilder();
        // 遍历问题和答案的HashMap
        TreeMap<String, String> sortedMap = new TreeMap<>(new Comparator<String>() {
            @Override
            public int compare(String str1, String str2) {
                // 提取标号部分
                int label1 = extractLabel(str1);
                int label2 = extractLabel(str2);

                return Integer.compare(label1, label2);
            }

            // 提取标号部分的辅助方法
            private int extractLabel(String str) {
                int startIndex = str.indexOf("(");
                int endIndex = str.indexOf(")");
                String labelStr = str.substring(startIndex + 1, endIndex);

                return Integer.parseInt(labelStr);
            }
        });
        sortedMap.putAll(answerMap);
        for (Map.Entry<String, String> entry : sortedMap.entrySet()) {
            String question = entry.getKey();
            String answer = entry.getValue();
            String correctAnswer = correctAnswerMap.get(question);
            resultAll.append(question).append("\n").append("正确答案:").append(correctAnswer).append("\n").append("你的答案:").append(answer).append("\n");
            // 判断答案是否正确
            if (!answer.equals(correctAnswer)) {
                wrongCount++;
                resultAll.append("结果错误\n");
                resultError.append(question).append("\n").append("正确答案:").append(correctAnswer).append("\n").append("你的答案:").append(answer).append("\n").append("\n");
            }else{
                resultAll.append("结果正确\n");

            }
        }

        try (PrintWriter writer = new PrintWriter(new File(allFile))) {
            writer.println("姓名: " + studentName);
            writer.println("学号: " + studentId);
            writer.println("班级: " + studentClass);
            writer.println("得分: " + (100 / questionCount) * (questionCount - wrongCount));
            writer.println("详细情况: \n" + resultAll.toString());

            //
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        try (PrintWriter writer = new PrintWriter(new File(errorFile))) {

            writer.println(resultError.toString());
            //
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    private String generateQuestion() {
        Random rand = new Random();
        int a = rand.nextInt(101);
        int b = rand.nextInt(101 - a);
        int c = rand.nextInt(101 - a - b);

        return a + (rand.nextBoolean() ? " + " : " - ") + b + (rand.nextBoolean() ? " + " : " - ") + c;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new MathTestApp();
            }
        });
    }
}
