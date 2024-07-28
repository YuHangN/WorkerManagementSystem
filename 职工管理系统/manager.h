#pragma once
#include "worker.h"

class Manager : public Worker {
public:
	Manager(int worker_id, string worker_name, int Dep_id);
	virtual void showInfo();
	virtual string getPosName();
	virtual int getWorkerId() const;
	virtual string getWorkerName();
	virtual void setWorkerId(int id);
	virtual void setWorkerName(string name);
	virtual void setWorkerPos(int posId);
};