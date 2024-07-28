#pragma once
#include "worker.h"

class Employee : public Worker {
	
private:

public:
	Employee(int worker_id, string name, int Dep_Id);
	virtual void showInfo();
	// 获得岗位名称
	virtual string getPosName();
	virtual int getWorkerId() const;
	virtual string getWorkerName();
	virtual void setWorkerId(int id);
	virtual void setWorkerName(string name);
	virtual void setWorkerPos(int posId);
};	