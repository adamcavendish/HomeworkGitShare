
SELECT DISTINCT course_id FROM OpenCourses WHERE OpenCourses.course_id NOT IN
	(SELECT course_id FROM CourseSelection, Students
		WHERE CourseSelection.student_id = Students.id AND Students.name = "劉曉明");

SELECT Courses.id FROM Courses WHERE Courses.id NOT IN (
    SELECT CS.course_id FROM CourseSelection AS CS, Students WHERE
        CS.student_id = Students.id AND
        CS.course_id = Courses.id AND
        Students.name = "劉曉明"
    );

