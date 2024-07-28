#include "manager.h"

Manager::Manager(int worker_id, string worker_name, int Dep_id) {
	this->worker_id = worker_id;
	this->worker_name = worker_name;
	this->Dep_id = Dep_id;
}

void Manager::showInfo() {
	cout << "职工编号： " << this->worker_id
		<< " \t职工姓名： " << this->worker_name
		<< " \t岗位：" << this->getPosName()
		<< " \t岗位职责：完成老板交给的任务,并下发任务给员工" << endl;
}

string Manager::getPosName() {
	return (string)"Manager";
}

int Manager::getWorkerId() const {
	return this->worker_id;
}

string Manager::getWorkerName()
{
	return this->worker_name;
}

void Manager::setWorkerId(int id) {
	this->worker_id = id;
}

void Manager::setWorkerName(string name) {
	this->worker_name = name;
}

void Manager::setWorkerPos(int posId) {
	this->Dep_id = posId;
}
