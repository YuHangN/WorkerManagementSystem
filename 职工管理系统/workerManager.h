#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#include <algorithm>
#define FILENAME "empRecord.txt"

class WorkerManager {
private:
	bool file_empty;
	int EmpNum;
	Worker** EmpArr;
	
public:

	WorkerManager();

	~WorkerManager();

	void showMenu();

	void addEmp();

	void save();

	int getEmpNum();

	void init_Emp();

	void showWorkers();

	void delWorker();

	int workerExist(int id);

	void modifyWorker();

	void findWorker();

	void sortWorker();

	void cleanFile();

};
