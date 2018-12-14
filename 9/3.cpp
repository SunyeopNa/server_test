#include <vector>
#include <iostream>



class Teacher;

class Student
{
private:
	Teacher *teacher; 
	int point = 0;

public:
	void addTeacher(Teacher *teacher)
	{
		this->teacher = teacher;
	}

	void addPoint(const int &point)
	{
		this->point += point;
	}

	void ask() 
	{
		cout << "Ask!" << endl'
	}

	int getPoint()
	{
		return point;
	}
};

class Teacher
{
private:
	std::vector<Student*> students; 

public:
	void addStudent(Student *student) 
	{
		students.push_back(student); 
		student->addTeacher(this); 
	}

	void TeachStudents() //학생들에게 수업을 하고, 출석 포인트를 준다.
	{
		for (const auto &ele : students)
		{
			//가르치는 학생 모두에게 수업 참여 포인트를 준다
			ele->addPoint(1);
		}
	}
};

int main()
{
	using namespace std;

	Teacher teacher;
	Student student1, student2;

	teacher.addStudent(&student1);
	teacher.addStudent(&student2);

	teacher.TeachStudents();

	cout << "학생 1의 출석 점수 : " << student1.getPoint() << endl;
	cout << "학생 2의 출석 점수 : " << student2.getPoint() << endl;
}