#include "workerManager.h"

WorkerManager::WorkerManager() {
	fstream iofs;
	iofs.open(FILENAME, ios::in);

	if (!iofs.is_open()) {
		this->EmpNum = 0;  
		this->file_empty = true;
		this->EmpArr = NULL; 
		iofs.close();
		return;
	}
	// ����ļ����Դ򿪵�������û������
	if (iofs.peek() == fstream::traits_type::eof()) {
		this->EmpNum = 0;
		this->file_empty = true;
		this->EmpArr = NULL;
		iofs.close();
		return;
	}
	// ����ļ����������ж���
	this->file_empty = false;
	this->EmpNum = this->getEmpNum();
	this->EmpArr = new Worker * [this->EmpNum];
	this->init_Emp();
}

WorkerManager::~WorkerManager() {
	if (this->EmpArr != nullptr) {
		delete[] this->EmpArr;
	}
}

void WorkerManager::showMenu() {
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::addEmp() {
	cout << "����������ְ�������� " << endl;
	int num;
	cin >> num;

	if (num > 0) {
		int newSize = this->EmpNum + num;
		// �����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		// ���ɿռ��ڵ�ָ������¿ռ䡣
		if (this->EmpArr != nullptr) {
			for (int i = 0; i < this->EmpNum; i++) {
				newSpace[i] = this->EmpArr[i];
			}
		}
		// �����µ�����
		for (int i = 0; i < num; i++) {
			string worker_name;
			int worker_id;
			int Dep_id;

			cout << "������� " << i + 1 << " ����ְ����ţ�" << endl;
			cin >> worker_id;

			cout << "������� " << i + 1 << " ����ְ��������" << endl;
			cin >> worker_name;

			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> Dep_id;

			Worker* worker = nullptr;
			switch (Dep_id)
			{
			case 1:
				worker = new Employee(worker_id, worker_name, Dep_id);
				break;
			case 2:
				worker = new Manager(worker_id, worker_name, Dep_id);
				break;
			case 3:
				worker = new Boss(worker_id, worker_name, Dep_id);
			default:
				break;
			}

			newSpace[this->EmpNum + i] = worker;
		}

		delete[] this->EmpArr;
		this->EmpArr = newSpace;
		this->EmpNum = newSize;

		save();
		this->file_empty = false;
		cout << "�ɹ����" << num << "����ְ����" << endl;
	}
	else {
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::save() {
	fstream iofs;

	iofs.open(FILENAME, ios::out); // ÿ�δ򿪶��ļ����в�����ʱ�򶼻�����ļ���Ȼ����������

	for (int i = 0; i < this->EmpNum; i++) {
		iofs << this->EmpArr[i]->getWorkerId() << " "
			<< this->EmpArr[i]->getWorkerName() << " "
			<< this->EmpArr[i]->getPosName() << endl;
	}
	iofs.close();
}

int WorkerManager::getEmpNum() {

	fstream iofs;
	iofs.open(FILENAME, ios::in);
	int workerNum = 0;

	string workerInfo;
	while (getline(iofs, workerInfo)) {
		workerNum++;
	}
	iofs.close();
	return workerNum;
}

void WorkerManager::init_Emp() {
	fstream iofs;

	iofs.open(FILENAME, ios::in);

	int workerId;
	string workerName;
	string position;
	int index = 0;

	while (iofs >> workerId && iofs >> workerName && iofs >> position) {
		Worker* worker = nullptr;
		if (position == "Employee") {
			worker = new Employee(workerId, workerName, 1);
		}
		else if (position == "Manager") {
			worker = new Manager(workerId, workerName, 2);
		}
		else {
			worker = new Boss(workerId, workerName, 3);
		}
		this->EmpArr[index++] = worker;
	}
	iofs.close();
}

void WorkerManager::showWorkers() {

	if (this->file_empty) {
		cout << "Ա������Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < this->EmpNum; i++) {
			this->EmpArr[i]->showInfo();
		}
	}
	system("Pause");
	system("cls");
}

void WorkerManager::delWorker() {
	if (this->file_empty) {
		cout << "Ա������Ϊ�գ�" << endl;
	}
	else {
		cout << "��������Ҫɾ����ְ���ţ�" << endl;
		int id;
		cin >> id;

		int index = workerExist(id);
		if (index == -1) {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
		else {
			delete this->EmpArr[index];

			for (int i = index; i < this->EmpNum - 1; i++) {
				this->EmpArr[i] = this->EmpArr[i + 1];
			}
			this->EmpNum--;
			if (this->EmpNum == 0) {
				this->file_empty = true;
			}
			this->save();

			cout << "ɾ���ɹ���" << endl;
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::workerExist(int id) {
	int index = -1;

	for (int i = 0; i < this->EmpNum; i++) {
		if (this->EmpArr[i]->getWorkerId() == id) {
			index = i;
			return index;
		}
	}
	return index;
}

void WorkerManager::modifyWorker() {
	if (this->file_empty) {
		cout << "Ա������Ϊ�գ�" << endl;
	}
	else {
		cout << "Ա����ţ�" << endl;
		int id;
		cin >> id;

		int index = this->workerExist(id);
		if (index == -1) {
			cout << "�޸�ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
		else {
			int workerId;
			string workerName;
			int workerPos;

			cout << "�鵽�� " << id << "��ְ������������ְ���ţ� " << endl;
			cin >> workerId;

			cout << "�������������� " << endl;
			cin >> workerName;

			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> workerPos;

			Worker* worker = nullptr;
			delete this->EmpArr[index];

			switch (workerPos) 
			{
			case 1:
				worker = new Employee(workerId, workerName, workerPos);
				this->EmpArr[index] = worker;
				break;
			case 2:
				worker = new Manager(workerId, workerName, workerPos);
				this->EmpArr[index] = worker;
				break;
			case 3:
				worker = new Boss(workerId, workerName, workerPos);
				this->EmpArr[index] = worker;
				break;
			default:
				break;
			}

			cout << "�޸ĳɹ�" << endl;
			this->save();
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::findWorker() {
	if (this->file_empty) {
		cout << "Ա������Ϊ�գ�" << endl;
	}
	else {
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;
		int choice;
		cin >> choice;

		if (choice == 1) {
			cout << "����ְ�����: " << endl;
			int id;
			cin >> id;

			int index = this->workerExist(id);
			if (index == -1) {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
			else {
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->EmpArr[index]->showInfo();
			}
		}
		else if (choice == 2) {
			cout << "��������ҵ�������" << endl;
			string name;
			cin >> name;

			bool found = false;
			for (int i = 0; i < this->EmpNum; i++) {
				if (this->EmpArr[i]->getWorkerName() == name) {
					found = true;
					cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
					this->EmpArr[i]->showInfo();
				}
			}
			if (!found) {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else {
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::sortWorker() {
	if (this->file_empty) {
		cout << "Ա������Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "��ѡ������ʽ�� " << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;
		int choice;
		cin >> choice;

		if (choice == 1) {
			sort(this->EmpArr, this->EmpArr + this->EmpNum, [](const Worker* a, const Worker* b) { // ��һ��ָ��ǰ�����const�����ŵ�ǰָ��ָ���ֵ�����޸ģ�����һ����������ָ�룬ֻ���Ե��ó�����Ա������
				return a->getWorkerId() < b->getWorkerId();
				});
		}
		else if (choice == 2) {
			sort(this->EmpArr, this->EmpArr + this->EmpNum, [](const Worker* a, const Worker* b) {
				return a->getWorkerId() > b->getWorkerId();
				});
		}
		else {
			cout << "����ѡ������" << endl;
			system("pause");
			system("cls");
			return;
		}
		
		cout << "����ɹ�,�������Ϊ��" << endl;
		this->save();
		this->showWorkers();
	}
}

void WorkerManager::cleanFile() {
	if (this->file_empty) {
		cout << "Ա������Ϊ�գ�" << endl;
	}
	else {
		cout << "ȷ��Ҫ���Ա��������" << endl;
		cout << "1��ȷ��" << endl;
		cout << "2������" << endl;
		int choice;
		cin >> choice;

		if (choice == 1) {
			ofstream ofs(FILENAME, ios::trunc);
			ofs.close();

			for (int i = 0; i < this->EmpNum; i++) {
				delete this->EmpArr[i];
			}
			this->EmpNum = 0;
			delete[] this->EmpArr;
			this->file_empty = true;
			this->EmpArr = nullptr;

			cout << "��ճɹ���" << endl;
		}
	}
	system("pause");
	system("cls");
}

