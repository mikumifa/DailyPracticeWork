#include <sstream>
#include "Lib.h"

//入口：输入的文件名、输出的文件名
//返回值：无
//作用：初始化对象
OlympicProgram::OlympicProgram(string input, string output) {
    this->input = input;
    this->output = output;
}
bool isFineType(string in){
    if(in.length()<=1)
        return false;
    if(in.length()==2){
        if(in=="Q1"||in=="Q"||in=="Q3"||in=="Q4")
            return true;
        else
            return false;
    }
    if(in.length()==4){
        if(in[0]=='0'&&in[1]=='1'){
            int n=stoi(in.substr(2));
            if(n>=16&&n<=29)
                return true;
        }
    }
    return false;
}
//入口：处理输入的文件
//返回值：无
//作用：根据所输入的信息调用不同的函数来处理
void OlympicProgram::resolveInput() {
    ifstream myfile(this->input, ios::in);
    string temp;
    if (!myfile.is_open()) {
        cout << "The file was not successfully opened" << endl;
        return;
    }
    ofstream file_writer(this->output, ios_base::out);
    ofstream outfile(this->output, ios::app);
    string outBuf;
    for (int i = 0; getline(myfile, temp); i++) {
        stringstream ss(temp);
        string order, ops;
        ss >> order >> ops;
        if (order == "players") {
            outBuf+=playerOutput();
        } else if (order == "result") {
                if(!isFineType(ops)) {
                    outBuf += outputWrong("N/A");
                    continue;
                }
                if(ops[0]!='Q')
            outBuf += outputResult(ops);
                else
                {}
        } else {

            outBuf += outputWrong("Error");
        }
        if (outBuf.size() > (1024 * 1024 * 5)) {
            outfile << outBuf;
            outBuf = "";
        }
    }
    if (outBuf != "")
        outfile << outBuf;
    myfile.close();
    outfile.close();
}

//入口：无
//返回值：string字符串
//作用：获取指令为total时的输出
string OlympicProgram::playerOutput() {
    Document d;        //文档树
    if (d.Parse(ReadFile("./src/players.json").c_str()).HasParseError())
        cout << "Parsing error!\n";
    const rapidjson::Value &playerList = d["players"];
    string os;
    string backtotal;
    for (unsigned int i = 0; i < playerList.Size(); i++) {
        rapidjson::Value::ConstMemberIterator full_name = playerList[i].FindMember("full_name");
        rapidjson::Value::ConstMemberIterator gender = playerList[i].FindMember("gender");
        rapidjson::Value::ConstMemberIterator nationality = playerList[i].FindMember("nationality");

        os = (string) "full_name:" + full_name->value.GetString() + '\n'
             + "gender:" + gender->value.GetString() + '\n'
             + "nationality:" + nationality->value.FindMember("name")->value.GetString() + '\n'
             + "-----";
        if (i != playerList.Size() - 1)
            os += '\n';
        backtotal += os;
    }
    return backtotal;
}

//入口：文件名
//返回值：string类型字符串
//作用：将文件读取为string返回
string ReadFile(string filename) {
    ifstream fin(filename.c_str(), ios::in);
    string str, t;
    if (!fin)
        cout << "The file was not successfully opened" << endl;
    while (getline(fin, t))
        str += t;
    fin.close();
    return str;
}
string findPlayerName(string team_id,string date){
    Document d;        //文档树
    if (d.Parse(ReadFile("./src/schedule/" + date + ".json").c_str()).HasParseError())
        cout << "Parsing error\n";
    const rapidjson::Value &teamList = d["teams"];
    const rapidjson::Value &playerList = d["players"];

    for (unsigned int i = 0; i < teamList.Size(); i++) {
        if(team_id==teamList[i].FindMember("uuid")->value.GetString())
        {
            string player_id=teamList[i].FindMember("players")->value[0].GetString();
            string player_Name;
            for (unsigned int k = 0; k < playerList.Size(); k++) {
                if(player_id==playerList[k].FindMember("uuid")->value.GetString())
                {
                    player_Name+="&";
                    player_Name+=playerList[k].FindMember("short_name")->value.GetString();

                }
            }
            return player_Name.substr(1);
        }
    }
    return "NULL";
}
//入口：比赛日期
//返回值：string类型字符串
//作用：处理指令为具体比赛日期时的输出
string OlympicProgram::outputResult(string date) {
    Document d;        //文档树
    if (d.Parse(ReadFile("./src/schedule/" + date + ".json").c_str()).HasParseError())
        cout << "Parsing error\n";
    const rapidjson::Value &matchList = d["matches"];
    const rapidjson::Value &teamList = d["teams"];
    string os;
    string backSchedule;
    for (unsigned int i = 0; i < matchList.Size(); i++) {
        //必要的临时储存变量指针
        rapidjson::Value::ConstMemberIterator actual_start_time = matchList[i].FindMember("actual_start_time");
        rapidjson::Value::ConstMemberIterator teams = matchList[i].FindMember("teams");
        rapidjson::Value::ConstMemberIterator score_0 = matchList[i].FindMember("teams")->value[0].FindMember("score");
        rapidjson::Value::ConstMemberIterator score_1 = matchList[i].FindMember("teams")->value[1].FindMember("score");
        string team_id_0=teams->value[0].FindMember("team_id")->value.GetString();
        string team_id_1=teams->value[1].FindMember("team_id")->value.GetString();
        os = (string) "time:" + actual_start_time->value.GetString() + '\n';
        os+="winner:";
        if(teams->value[0].FindMember("status")!=teams->value[0].MemberEnd())
            os+= findPlayerName(team_id_0,date);
        else
            os+=findPlayerName(team_id_1,date);
        os+="\nscore:";
        for (unsigned int k = 0; k < score_0->value.Size(); k++) {
            os+=score_0->value[k].FindMember("game")->value.GetString();
            os+=':';
            os+=score_1->value[k].FindMember("game")->value.GetString();
            if(k!=score_0->value.Size()-1)
            os+='|';
        }
        os+="\n-----\n";
        backSchedule += os;

    }
    return backSchedule;
}

//入口：错误信息
//返回值：string类型字符串
//作用：错误指令时的输出
string OlympicProgram::outputWrong(string wrong) {
    string os = wrong + '\n' + "-----\n";
    return os;
}
