#include "boss.h"

Boss::Boss(int worker_id, string worker_name, int Dep_id) {
	this->worker_id = worker_id;
	this->worker_name = worker_name;
	this->Dep_id = Dep_id;
}

void Boss::showInfo() {
	cout << "职工编号： " << this->worker_id
		<< " \t职工姓名： " << this->worker_name
		<< " \t岗位：" << this->getPosName()
		<< " \t岗位职责：管理公司所有事务" << endl;
}

string Boss::getPosName() {
	return (string)"Boss";
}

int Boss::getWorkerId() const {
	return this->worker_id;
}

string Boss::getWorkerName() {
	return this->worker_name;
}

void Boss::setWorkerId(int id) {
	this->worker_id = id;
}

void Boss::setWorkerName(string name) {
	this->worker_name = name;
}

void Boss::setWorkerPos(int posId) {
	this->Dep_id = posId;
}

