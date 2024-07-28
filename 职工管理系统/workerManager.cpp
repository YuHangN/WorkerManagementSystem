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
	// 如果文件可以打开但是里面没东西。
	if (iofs.peek() == fstream::traits_type::eof()) {
		this->EmpNum = 0;
		this->file_empty = true;
		this->EmpArr = NULL;
		iofs.close();
		return;
	}
	// 如果文件打开且里面有东西
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
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::addEmp() {
	cout << "请输入增加职工数量： " << endl;
	int num;
	cin >> num;

	if (num > 0) {
		int newSize = this->EmpNum + num;
		// 开辟新空间
		Worker** newSpace = new Worker * [newSize];
		// 将旧空间内的指针放入新空间。
		if (this->EmpArr != nullptr) {
			for (int i = 0; i < this->EmpNum; i++) {
				newSpace[i] = this->EmpArr[i];
			}
		}
		// 输入新的数据
		for (int i = 0; i < num; i++) {
			string worker_name;
			int worker_id;
			int Dep_id;

			cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;
			cin >> worker_id;

			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> worker_name;

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
		cout << "成功添加" << num << "名新职工！" << endl;
	}
	else {
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::save() {
	fstream iofs;

	iofs.open(FILENAME, ios::out); // 每次打开对文件进行操作的时候都会清空文件，然后进行输出。

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
		cout << "员工档案为空！" << endl;
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
		cout << "员工档案为空！" << endl;
	}
	else {
		cout << "请输入想要删除的职工号：" << endl;
		int id;
		cin >> id;

		int index = workerExist(id);
		if (index == -1) {
			cout << "删除失败，未找到该职工" << endl;
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

			cout << "删除成功！" << endl;
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
		cout << "员工档案为空！" << endl;
	}
	else {
		cout << "员工编号：" << endl;
		int id;
		cin >> id;

		int index = this->workerExist(id);
		if (index == -1) {
			cout << "修改失败，未找到该职工" << endl;
		}
		else {
			int workerId;
			string workerName;
			int workerPos;

			cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
			cin >> workerId;

			cout << "请输入新姓名： " << endl;
			cin >> workerName;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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

			cout << "修改成功" << endl;
			this->save();
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::findWorker() {
	if (this->file_empty) {
		cout << "员工档案为空！" << endl;
	}
	else {
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;
		int choice;
		cin >> choice;

		if (choice == 1) {
			cout << "查找职工编号: " << endl;
			int id;
			cin >> id;

			int index = this->workerExist(id);
			if (index == -1) {
				cout << "查找失败，查无此人" << endl;
			}
			else {
				cout << "查找成功！该职工信息如下：" << endl;
				this->EmpArr[index]->showInfo();
			}
		}
		else if (choice == 2) {
			cout << "请输入查找的姓名：" << endl;
			string name;
			cin >> name;

			bool found = false;
			for (int i = 0; i < this->EmpNum; i++) {
				if (this->EmpArr[i]->getWorkerName() == name) {
					found = true;
					cout << "查找成功！该职工信息如下：" << endl;
					this->EmpArr[i]->showInfo();
				}
			}
			if (!found) {
				cout << "查找失败，查无此人" << endl;
			}
		}
		else {
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::sortWorker() {
	if (this->file_empty) {
		cout << "员工档案为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;
		int choice;
		cin >> choice;

		if (choice == 1) {
			sort(this->EmpArr, this->EmpArr + this->EmpNum, [](const Worker* a, const Worker* b) { // 在一个指针前面加了const代表着当前指针指向的值不可修改，这是一个常量对象指针，只可以调用常量成员函数。
				return a->getWorkerId() < b->getWorkerId();
				});
		}
		else if (choice == 2) {
			sort(this->EmpArr, this->EmpArr + this->EmpNum, [](const Worker* a, const Worker* b) {
				return a->getWorkerId() > b->getWorkerId();
				});
		}
		else {
			cout << "输入选项有误" << endl;
			system("pause");
			system("cls");
			return;
		}
		
		cout << "排序成功,排序后结果为：" << endl;
		this->save();
		this->showWorkers();
	}
}

void WorkerManager::cleanFile() {
	if (this->file_empty) {
		cout << "员工档案为空！" << endl;
	}
	else {
		cout << "确定要清空员工档案？" << endl;
		cout << "1、确认" << endl;
		cout << "2、返回" << endl;
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

			cout << "清空成功！" << endl;
		}
	}
	system("pause");
	system("cls");
}

