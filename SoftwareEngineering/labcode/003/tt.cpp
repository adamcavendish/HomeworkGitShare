

int main()
{
	StudentRecord = hashmap(readAll(StudRecs));
	StudentNAttend = hashmap(readAll(NoAttend));
	Student = StudentRecord.begin();
	while(Student != StudentRecord.end()) {
		if(Student.GPA < minGPA)
			StudentRecord.erase(Student);
		if(StudentNAttend.find(Student.Name) != Hashmap::NOT_FOUND)
			StudentRecord.erase(Student);
		Student = StudentRecord.next();
	}//while

	return StudentRecord;
}
	

