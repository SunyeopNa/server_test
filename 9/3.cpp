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

	void TeachStudents() //�л��鿡�� ������ �ϰ�, �⼮ ����Ʈ�� �ش�.
	{
		for (const auto &ele : students)
		{
			//����ġ�� �л� ��ο��� ���� ���� ����Ʈ�� �ش�
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

	cout << "�л� 1�� �⼮ ���� : " << student1.getPoint() << endl;
	cout << "�л� 2�� �⼮ ���� : " << student2.getPoint() << endl;
}