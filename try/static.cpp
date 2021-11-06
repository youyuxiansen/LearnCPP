//
// Created by Felix on 2021/7/18.
//

#include <iostream>

using namespace std;

class Student {
public:
    Student(char *name, int age, float score);

    void show();

private:
    static int m_total;

private:
    char *m_name;
    int m_age;
    float m_score;
};

// static 成员变量必须在类外初始化。
int Student::m_total = 0;

Student::Student(char *name, int age, float score) : m_name(name),
                                                     m_age(age), m_score(score) {
    m_total++;
}

void Student::show() {
    cout << m_name << "的年龄是" << m_age << "，成绩是" << m_score << "（当前共有" << m_total << "名学生）" << endl;
}

int main() {
    //创建匿名对象
    (new Student("小明", 15, 90))->show();
    (new Student("李磊", 16, 80))->show();
    (new Student("张华", 16, 99))->show();
    (new Student("王康", 14, 60))->show();
}

