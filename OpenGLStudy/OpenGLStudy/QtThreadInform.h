#pragma once
#include <QThread>
#include <thread>
#include <functional>
#include <memory>
#include <iostream>
using namespace std;


class MyClass
{
public:
	// 类中的成员函数
	void MyFunction(int value) {
		std::cout << "Run funtion  value: " << value << std::endl;
	}
	void ThreadClassDeal(std::string& name)
	{
		cout << "Class::thread: " << name << endl;
		std::cout << "Class::Tid = " << std::this_thread::get_id() << std::endl;
		name = "aaaaaaaaaaaaaaaaaaaa";
		std::this_thread::sleep_for(std::chrono::seconds(10));
		cout << "Class::End thread " << endl;
	}
};


class CommunicationThread : public QThread {
    Q_OBJECT
public:
    CommunicationThread(QObject* parent = nullptr) : QThread(parent) {}
	std::string executeLogicInThread();
protected:
	void run() override;

signals:
    void resultReady(const QString& result);

private:
	MyClass m_MyClass;
	string data;
};

