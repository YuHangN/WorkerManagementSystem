#include "manager.h"

Manager::Manager(int worker_id, string worker_name, int Dep_id) {
	this->worker_id = worker_id;
	this->worker_name = worker_name;
	this->Dep_id = Dep_id;
}

void Manager::showInfo() {
	cout << "ְ����ţ� " << this->worker_id
		<< " \tְ�������� " << this->worker_name
		<< " \t��λ��" << this->getPosName()
		<< " \t��λְ������ϰ彻��������,���·������Ա��" << endl;
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
