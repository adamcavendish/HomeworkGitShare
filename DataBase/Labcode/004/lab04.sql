SYSTEM echo "1. 建立计算机学院总评不及格成绩学生的视图，";
SYSTEM echo "包括学生学号、姓名、性别、手机、所选课程和成绩。";

DROP VIEW FailedStudents;

CREATE VIEW FailedStudents AS (
	SELECT Students.id, Students.name, Students.gender, Students.cellphone, CourseSelection.course_id, CourseSelection.overall_score
	FROM Students, CourseSelection
	WHERE 
	Students.id = CourseSelection.student_id AND
	(CourseSelection.overall_score < 60 OR
		CourseSelection.overall_score IS NULL));

SELECT * FROM FailedStudents;

SYSTEM echo "";

SYSTEM echo "2. 在CourseSelection表中插入记录，把每个学生没学过的课程都插入到表中";
SYSTEM echo "使得每个学生都选修每门课";

INSERT INTO CourseSelection(student_id, semester, course_id, teacher_id) (
	SELECT
		Students.id,
		OpenCourses.course_id,
		OpenCourses.semester,
		OpenCourses.teacher_id
	FROM
		Students,
		OpenCourses
	WHERE NOT EXISTS (
		SELECT * FROM CourseSelection WHERE
			OpenCourses.course_id = CourseSelection.course_id AND
			OpenCourses.semester = CourseSelection.semester AND
			OpenCourses.teacher_id = CourseSelection.teacher_id AND
			Students.id = CourseSelection.student_id
	)
);

SYSTEM echo "";

