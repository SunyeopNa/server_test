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
			cout << "용지가 부족합니다!" << endl;
			flags = false;
		}

		if (pages > availableInk)
		{
			cout << "잉크가 부족합니다!" << endl;
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
		cout << "모델명 : " << getModel()
			<< ", 제조사 : " << getManufact()
			<< ", 인쇄종이 잔량 : " << getAvailPaper()
			<< ", 잉크 잔량 : " << availableInk << endl;
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
			cout << "용지가 부족합니다!" << endl;
			flags = false;
		}

		if (pages > availableToner)
		{
			cout << "잉크가 부족합니다!" << endl;
			flags = false;
		}

		if (flags == true)
		{
			Printer::print(pages); 			// 부모 class의 함수
			availableToner = availableToner - pages;
		}

	}

	void showInfo()
	{
		cout << "모델명 : " << getModel()
			<< ", 제조사 : " << getManufact()
			<< ", 인쇄종이 잔량 : " << getAvailPaper()
			<< ", 잉크 잔량 : " << availableToner << endl;
	}
};

int main()
{
	InkjetPrinter *IP = new InkjetPrinter("DGU0001", "DGU", 100, 50);
	LaserPrinter *LP = new LaserPrinter("DGU0002", "GGU", 100, 150);

	cout << "-- 현재 작동중인 프린터의 정보" << endl;
	cout << "잉크젯 프린터 : "; IP->showInfo();
	cout << "레이저 프린터 : "; LP->showInfo();
	



	bool print_continue_flag = true; 
	while (print_continue_flag)
	{
		cout << endl;
		int printer_type, papers;
		cout << "프린터(1 : 잉크젯, 2: 레이저) 와 매수 입력 >> ";
		cin >> printer_type>> papers;

		
		if (printer_type == 1) IP->print(papers);
		else if (printer_type == 2) LP->print(papers);
		else
		{
			
			cout << "잘못된 프린터 타입" << endl << endl;;
			continue;
		}

		IP->showInfo();
		LP->showInfo();

		cin.ignore(); 
		cout << "계속 프린트 하시겠습니까? (y/n) >> ";
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