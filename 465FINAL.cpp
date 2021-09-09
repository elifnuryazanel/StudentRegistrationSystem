#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <cstring>

using namespace std;

/* Here are 2 functions "convert" and "convert2" to convert the strings to upper or lower case strings in order to 
compare them without any errors. */

string convert(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		s[i] = toupper(s[i]);
	}
	return s;
}

string convert2(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}

/* This is the "Student" class where the information of students are kept. Also there is a 
member function of the class to input the information of students. */

class Student {
public:
	long long int id;
	string name, s_name;
	float gpa;
	string stu_semester;

	void getInformation()
	{
		cout << "\n\n   -----------------------------------------" << endl;
		cout << "              COURSE SELECTION" << endl;
		cout << "   -----------------------------------------" << endl << endl;

		cout << "     Please enter your name and surname: ";
		cin >> name >> s_name;

		cout << "     Please enter your ID: ";
		cin >> id;

		cout << "     Please enter the semester that you are in (spring/fall): ";
		cin >> stu_semester;

		while (stu_semester != "fall" && stu_semester != "spring" && stu_semester != "FALL" && stu_semester != "SPRING")
		{
			cout << "\n     Please enter a valid semester name!" << endl;
			cout << "     Correct semester name (spring/fall): ";
			cin >> stu_semester;
		}

		stu_semester = convert2(stu_semester);

		cout << "     Please enter your GPA: ";
		cin >> gpa;

		while (gpa < 0 || gpa > 4)
		{
			cout << "\n     Please enter a valid GPA!";
			cout << "\n     Your GPA: ";
			cin >> gpa;
		}

		cout << "    --------------------------------------------" << endl;

		if (gpa >= 2.0 && gpa < 2.5) {
			cout << "     You can take 40 ACTS courses this semester." << endl;
		}

		else if (gpa >= 2.5 && gpa < 3.0) {
			cout << "     You can take 45 ACTS courses this semester." << endl;
		}

		else if (gpa <= 1.7) {
			cout << "     You can take 33 ACTS courses this semester." << endl;
		}

		else if (gpa >= 3) {
			cout << "     You can take 48 ACTS courses this semester." << endl;
		}

		cout << "    --------------------------------------------" << endl;
	}
};

/* This is the "Courses" class which the information of the lectures are kept. */

class Courses {
public:
	string courseName;
	string courseCode;
	float acts;
	string semester;
	string preCourse;
	int number_of_courses;
};

/* This is the "control" function which is used to control repetition of the lectures. */

int control(Courses arr[], string a)
{
	int correct_name = 0;

	for (int j = 0; j < 50; j++)
	{
		if (arr[j].courseCode == a)
		{
			correct_name = 1;
		}
	}

	return correct_name;
}

/* This is the most important function of the program, the input of the lectures are taken and some calculations
are done in this function. */

void takeCourses(Courses a, Courses arr[50], Student b)
{
	int number_of_course, count = 0;
	float ACTS;
	a.acts = 0;
	string lectures[20];
	string lecture_codes[20];
	int correctness = 0;
	int order = 0;
	int same = 0;
	string pre_Course = "Y";


	pre_Course = convert(pre_Course);

	if (b.gpa >= 2.0 && b.gpa < 2.5) {
		ACTS = 40;
	}

	else if (b.gpa >= 2.5 && b.gpa < 3.0) {
		ACTS = 45;
	}

	else if (b.gpa <= 1.7) {
		ACTS = 33;
	}

	else if (b.gpa >= 3) {
		ACTS = 48;
	}

	cout << "\n     Please enter the number of courses you're going to take: ";
	cin >> number_of_course;
	cout << endl;

	for (int i = 1; i <= number_of_course; i++)
	{
		pre_Course = convert(pre_Course);

		correctness = 0;
		same = 0;
		
		cout << "     Course " << i << ": ";
		cin >> a.courseCode;

		a.courseCode = convert(a.courseCode);

		correctness = control(arr, a.courseCode);

		while (correctness != 1)
		{
			cout << "\n     Please enter a valid course name!" << endl << endl;
			cout << "     Course " << i << ": ";
			cin >> a.courseCode;
			a.courseCode = convert(a.courseCode);
			correctness = control(arr, a.courseCode);
		}

		for (int j = 0; j < 50; j++) //To find the index of the inputted lecture
		{
			if (arr[j].courseCode == a.courseCode)
			{
				count = j;
			}
		}

		lecture_codes[i - 1] = arr[count].courseCode;
		lectures[i - 1] = arr[count].courseName;

		for (int n = 0; n < i; n++)
		{
			if (a.courseCode == lecture_codes[n - 1]) //To check whether the lecture is written/taken before or not
			{
				same = 1;
				i--;
			}
		}

		if (same == 1)
		{
			cout << "     You have already choosen this course. Please choose another one. \n\n";
		}

		else if (arr[count].preCourse != "NULL")
		{
			cout << "     Have you taken the courses (" << arr[count].preCourse << ") which are pre courses of this lecture?";
			cout << "\n     Please enter Y for yes, N for no: ";
			cin >> pre_Course;

			if (pre_Course == "y" || pre_Course == "Y")
			{
				cout << "     You can take this course due to completing the pre-courses. " << endl << endl;
				cout << "     Required ACTS for this course is " << arr[count].acts << endl;
				a.acts += arr[count].acts;
				cout << "     Your total ACTS = " << a.acts << endl << endl;
			}

			else 
			{
				cout << "     You cannot take this course because you have to pass the pre-courses (" << arr[count].preCourse << ") " << endl << endl;
				i--;
			}
		}

		else if (arr[count].semester == "NULL" || arr[count].semester == b.stu_semester)
		{
			cout << "     Required ACTS for this course is " << arr[count].acts << endl;
			a.acts += arr[count].acts;
			cout << "     Your total ACTS = " << a.acts << endl << endl;

			if (a.acts > ACTS)
			{
				cout << "     YOU HAVE CROSSED THE ACTS LIMIT!!! PLEASE PREPARE ANOTHER SCHEDULE!\n" << endl;
				system("pause");
			}

		}

		else if (arr[count].semester != b.stu_semester)
		{
			cout << "     You cannot choose this course! It is not opened in this semester." << endl << endl;
			i--;
		}
	}

	cout << "\n     Dear " << b.name << " " << b.s_name << ", the lectures that you are going to take: \n\n";

	for (int n = 0; n < number_of_course; n++)
	{
		cout << "     " << lecture_codes[n];
		cout << " - " << lectures[n] << endl;
	}
}

int main() {

	Courses cur[50]; //an array of object to store the curriculum
	char answer;

	cur[0].courseName = "General Chemistry";
	cur[0].courseCode = "CHE105";
	cur[0].acts = 5;
	cur[0].semester = "NULL";
	cur[0].preCourse = "NULL";
	cur[1].courseName = "Calculus 1";
	cur[1].courseCode = "MATH151";
	cur[1].acts = 7;
	cur[1].semester = "NULL";
	cur[1].preCourse = "NULL";
	cur[2].courseName = "Computer Programming 1";
	cur[2].courseCode = "CMPE113";
	cur[2].acts = 4;
	cur[2].semester = "NULL";
	cur[2].preCourse = "NULL";
	cur[3].courseName = "Academic English 1";
	cur[3].courseCode = "ENG101";
	cur[3].acts = 3.5;
	cur[3].semester = "NULL";
	cur[3].preCourse = "NULL";
	cur[4].courseName = "Fundamentals Of Computation";
	cur[4].courseCode = "CMPE109";
	cur[4].acts = 2.5;
	cur[4].semester = "NULL";
	cur[4].preCourse = "NULL";
	cur[5].courseName = "General Physics 1";
	cur[5].courseCode = "PHYS101";
	cur[5].acts = 6;
	cur[5].semester = "fall";
	cur[5].preCourse = "NULL";
	cur[6].courseName = "Atatürk's Principles and History of Revolution 1 ";
	cur[6].courseCode = "HIST111";
	cur[6].acts = 2;
	cur[6].semester = "fall";
	cur[6].preCourse = "NULL";
	cur[7].courseName = "Fundamentals Of Electronic Circuit Components ";
	cur[7].courseCode = "CMPE134";
	cur[7].acts = 3.5;
	cur[7].semester = "spring";
	cur[7].preCourse = "NULL";
	cur[8].courseName = "Academic English 2";
	cur[8].courseCode = "ENG102";
	cur[8].acts = 3.5;
	cur[8].semester = "NULL";
	cur[8].preCourse = "NULL";
	cur[9].courseName = "General Physics 2";
	cur[9].courseCode = "PHYS102";
	cur[9].acts = 6;
	cur[9].semester = "spring";
	cur[9].preCourse = "NULL";
	cur[10].courseName = "Atatürk's Principle and History of Inkilap 2";
	cur[10].courseCode = "HIST112";
	cur[10].acts = 2;
	cur[10].semester = "spring";
	cur[10].preCourse = "NULL";
	cur[11].courseName = "History Of Civilization";
	cur[11].courseCode = "HIST221";
	cur[11].acts = 3;
	cur[11].semester = "spring";
	cur[11].preCourse = "NULL";
	cur[12].courseName = "Calculus 2";
	cur[12].courseCode = "MATH152";
	cur[12].acts = 7;
	cur[12].semester = "NULL";
	cur[12].preCourse = "MATH151";
	cur[13].courseName = "Computer Programming 2";
	cur[13].courseCode = "CMPE114";
	cur[13].acts = 5;
	cur[13].semester = "NULL";
	cur[13].preCourse = "CMPE113";
	cur[14].courseName = "Academic English 3";
	cur[14].courseCode = "ENG201";
	cur[14].acts = 6;
	cur[14].semester = "NULL";
	cur[14].preCourse = "ENG101 and ENG102";
	cur[15].courseName = "Digital Circuits and Systems";
	cur[15].courseCode = "EE203";
	cur[15].acts = 6;
	cur[15].semester = "fall";
	cur[15].preCourse = "NULL";
	cur[16].courseName = "Linear Algebra";
	cur[16].courseCode = "MATH275";
	cur[16].acts = 6;
	cur[16].semester = "NULL";
	cur[16].preCourse = "NULL";
	cur[17].courseName = "Discrete Computational Structures";
	cur[17].courseCode = "CMPE251";
	cur[17].acts = 7;
	cur[17].semester = "fall";
	cur[17].preCourse = "NULL";
	cur[18].courseName = "Object-Oriented Programming";
	cur[18].courseCode = "CMPE225";
	cur[18].acts = 8;
	cur[18].semester = "NULL";
	cur[18].preCourse = "CMPE114";
	cur[19].courseName = "Differential Equations";
	cur[19].courseCode = "MATH276";
	cur[19].acts = 6;
	cur[19].semester = "NULL";
	cur[19].preCourse = "MATH158 and MATH152";
	cur[20].courseName = "Probability and Statistics";
	cur[20].courseCode = "IE220";
	cur[20].acts = 5;
	cur[20].semester = "NULL";
	cur[20].preCourse = "NULL";
	cur[21].courseName = "Academic English 4";
	cur[21].courseCode = "ENG202";
	cur[21].acts = 3;
	cur[21].semester = "NULL";
	cur[21].preCourse = "ENG101 and ENG102";
	cur[22].courseName = "Data Structures";
	cur[22].courseCode = "CMPE226";
	cur[22].acts = 8;
	cur[22].semester = "NULL";
	cur[22].preCourse = "CMPE225";
	cur[23].courseName = "Introduction to Microprocessors and Microcontrollers";
	cur[23].courseCode = "CMPE236";
	cur[23].acts = 8;
	cur[23].semester = "spring";
	cur[23].preCourse = "EE203";
	cur[24].courseName = "Database Design and Management";
	cur[24].courseCode = "CMPE341";
	cur[24].acts = 7;
	cur[24].semester = "NULL";
	cur[24].preCourse = "NULL";
	cur[25].courseName = "English for Business Life";
	cur[25].courseCode = "ENG301";
	cur[25].acts = 3;
	cur[25].semester = "NULL";
	cur[25].preCourse = "ENG201 and ENG202";
	cur[26].courseName = "Algorithm";
	cur[26].courseCode = "CMPE323";
	cur[26].acts = 7;
	cur[26].semester = "fall";
	cur[26].preCourse = "CMPE226";
	cur[27].courseName = "Programming Languages";
	cur[27].courseCode = "CMPE325";
	cur[27].acts = 6;
	cur[27].semester = "fall";
	cur[27].preCourse = "CMPE225";
	cur[28].courseName = "Summer Intern";
	cur[28].courseCode = "CMPE399";
	cur[28].acts = 0;
	cur[28].semester = "NULL";
	cur[28].preCourse = "CMPE225";
	cur[29].courseName = "Computer Architecture and Organization";
	cur[29].courseCode = "CMPE331";
	cur[29].acts = 7;
	cur[29].semester = "fall";
	cur[29].preCourse = "EE203";
	cur[30].courseName = "Numerical Methods for Engineers";
	cur[30].courseCode = "MATH380";
	cur[30].acts = 5;
	cur[30].semester = "NULL";
	cur[30].preCourse = "MATH275";
	cur[31].courseName = "English for Business Life II";
	cur[31].courseCode = "ENG302";
	cur[31].acts = 3;
	cur[31].semester = "NULL";
	cur[31].preCourse = "ENG201 and ENG202";
	cur[32].courseName = "Software Engineering";
	cur[32].courseCode = "SE346";
	cur[32].acts = 6;
	cur[32].semester = "spring";
	cur[32].preCourse = "NULL";
	cur[33].courseName = "Computer Networks";
	cur[33].courseCode = "CMPE334";
	cur[33].acts = 6;
	cur[33].semester = "spring";
	cur[33].preCourse = "NULL";
	cur[34].courseName = "Formal Languages and Automata";
	cur[34].courseCode = "CMPE326";
	cur[34].acts = 6;
	cur[34].semester = "spring";
	cur[34].preCourse = "CMPE251";
	cur[35].courseName = "Non Technical Elective";
	cur[35].courseCode = "GE1FA1";
	cur[35].acts = 4;
	cur[35].semester = "NULL";
	cur[35].preCourse = "NULL";
	cur[36].courseName = "Turkish Language I";
	cur[36].courseCode = "TURK401";
	cur[36].acts = 2;
	cur[36].semester = "NULL";
	cur[36].preCourse = "NULL";
	cur[37].courseName = "Project Orientation";
	cur[37].courseCode = "CMPE493";
	cur[37].acts = 5;
	cur[37].semester = "NULL";
	cur[37].preCourse = "CMPE341 and CMPE226";
	cur[38].courseName = "Summer Practice II";
	cur[38].courseCode = "CMPE499";
	cur[38].acts = 0;
	cur[38].semester = "NULL";
	cur[38].preCourse = "CMPE226";
	cur[39].courseName = "Non Technical Elective";
	cur[39].courseCode = "GE2FA1";
	cur[39].acts = 5;
	cur[39].semester = "NULL";
	cur[39].preCourse = "NULL";
	cur[40].courseName = "Non Technical Elective";
	cur[40].courseCode = "GE2FA2";
	cur[40].acts = 5;
	cur[40].semester = "NULL";
	cur[40].preCourse = "NULL";
	cur[41].courseName = "Technical Elective";
	cur[41].courseCode = "AE4FA1";
	cur[41].acts = 5;
	cur[41].semester = "NULL";
	cur[41].preCourse = "NULL";
	cur[42].courseName = "Technical Elective";
	cur[42].courseCode = "AE4FA2";
	cur[42].acts = 5;
	cur[42].semester = "NULL";
	cur[42].preCourse = "NULL";
	cur[43].courseName = "Technical Elective";
	cur[43].courseCode = "AE4FA3";
	cur[43].acts = 5;
	cur[43].semester = "NULL";
	cur[43].preCourse = "NULL";
	cur[44].courseName = "Turkish Language 2";
	cur[44].courseCode = "TURK402";
	cur[44].acts = 2;
	cur[44].semester = "NULL";
	cur[44].preCourse = "NULL";
	cur[45].courseName = "Graduation Project";
	cur[45].courseCode = "CMPE494";
	cur[45].acts = 8;
	cur[45].semester = "NULL";
	cur[45].preCourse = "CMPE493";
	cur[46].courseName = "Operating Systems";
	cur[46].courseCode = "CMPE431";
	cur[46].acts = 5;
	cur[46].semester = "spring";
	cur[46].preCourse = "NULL";
	cur[47].courseName = "Technical Elective";
	cur[47].courseCode = "AE4SP1";
	cur[47].acts = 5;
	cur[47].semester = "NULL";
	cur[47].preCourse = "NULL";
	cur[48].courseName = "Technical Elective";
	cur[48].courseCode = "AE4SP2";
	cur[48].acts = 5;
	cur[48].semester = "NULL";
	cur[48].preCourse = "NULL";
	cur[49].courseName = "Technical Elective";
	cur[49].courseCode = "AE4SP3";
	cur[49].acts = 5;
	cur[49].semester = "NULL";
	cur[49].preCourse = "NULL";


	cout << "   -----------------------------------------" << endl;
	cout << "    WELCOME TO THE COURSE SELECTION SYSTEM!" << endl;
	cout << "   -----------------------------------------" << endl << endl;
	cout << "     Would you like to list the curriculum before choosing lectures? (Y/N): ";
	cin >> answer;
	

	if (answer == 'Y' || answer == 'y')
	{
		cout << endl;
		cout << "   -----------------------------------------" << endl;
		cout << "                  CURRICULUM" << endl;
		cout << "   -----------------------------------------" << endl;

		for (int i = 0; i < 50; i++)
		{
			cout << "\n     " << cur[i].courseCode << " - " << cur[i].courseName << " - " << cur[i].acts << " ACTS";

			if (cur[i].preCourse != "NULL")
			{
				cout << " - PRE COURSE(S): " << cur[i].preCourse;
			}
			
			if (cur[i].semester != "NULL")
			{
				cout << " - SEMESTER: " << cur[i].semester;
			}

			if (cur[i].semester == "NULL")
			{
				cout << " - SEMESTER: fall and spring";
			}

		}
	}
	
	Student info;
	info.getInformation();

	Courses obj;
	takeCourses(obj, cur, info);

	cout << "\n     -------------------------------------------------------";
	cout << "\n      THANK YOU FOR CHOOSING OUR COURSE SELECTION SYSTEM! :)\n";
	cout << "     -------------------------------------------------------";
}
