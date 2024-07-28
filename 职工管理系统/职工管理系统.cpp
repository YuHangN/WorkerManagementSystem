#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"

using namespace std;

int main() {

	WorkerManager wm;
	int choice;

	while (true) {

		wm.showMenu();
		cout << "Please enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 0: // 退出系统
			cout << "Bye" << endl;
			system("pause");
			exit(0);
		case 1: // 添加职工
			wm.addEmp();
			break;
		case 2: // 显示职工
			wm.showWorkers();
			break;
		case 3: // 删除职工
			wm.delWorker();
			break;
		case 4: // 修改职工
			wm.modifyWorker();
			break;
		case 5: // 查找职工
			wm.findWorker();
			break;
		case 6: // 排序职工
			wm.sortWorker();
			break;
		case 7: // 清空文件
			wm.cleanFile();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;

}