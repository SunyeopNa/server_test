#include <iostream>
#include <string>
using namespace std;

class Printer
{
private :
	string model;
	string manufacturer;
	int availablePaper;

public:
	Printer(string in_model, string in_manu, int in_paper)
		:model(in_model), manufacturer(in_manu), availablePaper(in_paper)
	{}

	string getModel() { return model; }
	string getManufact() { return manufacturer; }
	int getAvailPaper() { return availablePaper; }


	void print(int pages) { availablePaper =  availablePaper - pages; }
};

class InkjetPrinter : public Printer
{
	int availableInk;

public :
	InkjetPrinter(string in_model, string in_manu, int in_paper, int in_Ink)
		: Printer(in_model, in_manu, in_paper), availableInk(in_Ink)
	{}

	void print(int pages)
	{
		

		bool flags = true;
		if (pages > this->getAvailPaper())
		{
			cout << "������ �����մϴ�!" << endl;
			flags = false;
		}

		if (pages > availableInk)
		{
			cout << "��ũ�� �����մϴ�!" << endl;
			flags = false;
		}

		if (flags == true)
		{
			Printer::print(pages); 			
			availableInk = availableInk - pages;
		}
	}

	void showInfo()
	{
		cout << "�𵨸� : " << getModel()
			<< ", ������ : " << getManufact()
			<< ", �μ����� �ܷ� : " << getAvailPaper()
			<< ", ��ũ �ܷ� : " << availableInk << endl;
	}

};

class LaserPrinter : public Printer
{
	int availableToner;

public :
	LaserPrinter(string in_model, string in_manu, int in_paper, int in_Toner)
		: Printer(in_model, in_manu, in_paper), availableToner(in_Toner)
	{}

	void print(int pages)
	{
		bool flags = true;
		if (pages > this->getAvailPaper())
		{
			cout << "������ �����մϴ�!" << endl;
			flags = false;
		}

		if (pages > availableToner)
		{
			cout << "��ũ�� �����մϴ�!" << endl;
			flags = false;
		}

		if (flags == true)
		{
			Printer::print(pages); 			// �θ� class�� �Լ�
			availableToner = availableToner - pages;
		}

	}

	void showInfo()
	{
		cout << "�𵨸� : " << getModel()
			<< ", ������ : " << getManufact()
			<< ", �μ����� �ܷ� : " << getAvailPaper()
			<< ", ��ũ �ܷ� : " << availableToner << endl;
	}
};

int main()
{
	InkjetPrinter *IP = new InkjetPrinter("DGU0001", "DGU", 100, 50);
	LaserPrinter *LP = new LaserPrinter("DGU0002", "GGU", 100, 150);

	cout << "-- ���� �۵����� �������� ����" << endl;
	cout << "��ũ�� ������ : "; IP->showInfo();
	cout << "������ ������ : "; LP->showInfo();
	



	bool print_continue_flag = true; 
	while (print_continue_flag)
	{
		cout << endl;
		int printer_type, papers;
		cout << "������(1 : ��ũ��, 2: ������) �� �ż� �Է� >> ";
		cin >> printer_type>> papers;

		
		if (printer_type == 1) IP->print(papers);
		else if (printer_type == 2) LP->print(papers);
		else
		{
			
			cout << "�߸��� ������ Ÿ��" << endl << endl;;
			continue;
		}

		IP->showInfo();
		LP->showInfo();

		cin.ignore(); 
		cout << "��� ����Ʈ �Ͻðڽ��ϱ�? (y/n) >> ";
		switch (getchar())
		{
		case 'y' :

			break;
		case 'n': 
			print_continue_flag = false;
			break;
		default:

			break;
		}
	}



	delete IP;
	delete LP;

	return 0;
}