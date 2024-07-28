#include "employee.h"

Employee::Employee(int worker_id, string name, int Dep_id) {
	this->worker_id = worker_id;
	this->worker_name = name;
	this->Dep_id = Dep_id;
}

void Employee::showInfo() {
	cout << "ְ����ţ� " << this->worker_id
		<< " \tְ�������� " << this->worker_name
		<< " \t��λ��" << this->getPosName()
		<< " \t��λְ����ɾ�����������" << endl;
}

string Employee::getPosName() {
	return "Employee";
}

int Employee::getWorkerId() const {
	return this->worker_id;
}

string Employee::getWorkerName() {
	return this->worker_name;
}

void Employee::setWorkerId(int id) {
	this->worker_id = id;
}

void Employee::setWorkerName(string name) {
	this->worker_name = name;
}

void Employee::setWorkerPos(int posId) {
	this->Dep_id = posId;
}
