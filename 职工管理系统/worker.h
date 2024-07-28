#pragma once
using namespace std;
#include <string>
#include <iostream>

class Worker {

protected:
	int worker_id;
	string worker_name;
	// 所在部门id。
	int Dep_id;

public:
	virtual void showInfo() = 0;
	// 获得岗位名称。
	virtual string getPosName() = 0;

	virtual int getWorkerId() const = 0;

	virtual string getWorkerName() = 0;

	virtual void setWorkerId(int id) = 0;

	virtual void setWorkerName(string name) = 0;

	virtual void setWorkerPos(int posId) = 0;

};