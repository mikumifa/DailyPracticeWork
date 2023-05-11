// AOSearch.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������

#include "Lib.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Entered a command error!" << endl;
        cout << "Please use AOSearch.exe input.txt output.txt" << endl;
        return 0;
    }
    OlympicProgram test(argv[1], argv[2]);
    test.resolveInput();

    return 0;
}

