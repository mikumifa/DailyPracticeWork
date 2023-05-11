#pragma once
#include <iostream>
#include <fstream> //文件读写操作
#include <string>
#include <algorithm>
#include "rapidjson-master/include/rapidjson/document.h"      //rapidjson解析json数据的头文件
#include "rapidjson-master/include/rapidjson/writer.h"
#include "rapidjson-master/include/rapidjson/stringbuffer.h"
using namespace std;
using namespace rapidjson;

//主要程序类
class OlympicProgram {
private:
	string input;
	string output;
	string totalout;//用来保存指令为total时的输出
	string scheduleOut[19];//用来保存指令为schedulexxxx的输出
public:
	OlympicProgram(string input,string output);
	void resolveInput();//根据输入的指令决定输出
	string playerOutput();//获取total奖牌信息
	string outputResult(string date);//获取指定日期赛程信息
	string outputWrong(string wrong);//获取输出错误信息
};

string ReadFile(string filename);//将读取的文件转为string
