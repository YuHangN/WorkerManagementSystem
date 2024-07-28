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
		case 0: // �˳�ϵͳ
			cout << "Bye" << endl;
			system("pause");
			exit(0);
		case 1: // ���ְ��
			wm.addEmp();
			break;
		case 2: // ��ʾְ��
			wm.showWorkers();
			break;
		case 3: // ɾ��ְ��
			wm.delWorker();
			break;
		case 4: // �޸�ְ��
			wm.modifyWorker();
			break;
		case 5: // ����ְ��
			wm.findWorker();
			break;
		case 6: // ����ְ��
			wm.sortWorker();
			break;
		case 7: // ����ļ�
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