USE school;

SYSTEM echo "2. 查询每个学生选课情况（包括没有选修课程的学生）";
/*
(SELECT
	Students.id,
	Students.name,
	Courses.id,
	Courses.name,
	CourseSelection.semester
FROM
	Students,
	Courses,
	CourseSelection
WHERE
	Students.id = CourseSelection.student_id AND
	Courses.id = CourseSelection.course_id
ORDER BY
	Students.id ASC);
*/

SELECT
	Students.id,
	Students.name,
	Courses.id,
	Courses.name,
	CourseSelection.semester
FROM
	(Students, Courses) LEFT JOIN CourseSelection
	ON
		Students.id = CourseSelection.student_id AND
		Courses.id = CourseSelection.course_id
ORDER BY
	Students.id ASC,
	Courses.id ASC;

SYSTEM echo "";

SYSTEM echo "Add a testboy who has taken all courses.";

INSERT INTO Students(id, name, gender, birthday, birthplace, cellphone, college_id) VALUES
("1108", "testboy", "男", "1993-03-06", "上海", "13613005486", "02");
INSERT INTO CourseSelection(student_id, semester, course_id, teacher_id, usual_time_score, exam_score, overall_score) 
VALUES
("1108", "2012-2013秋季", "08301001", "0101", 60, 60, 60),
("1108", "2012-2013秋季", "08302001", "0101", 60, 60, 60),
("1108", "2012-2013秋季", "08305001", "0101", 60, 60, 60),
("1108", "2012-2013秋季", "08305002", "0101", 60, 60, 60),
("1108", "2012-2013秋季", "08305003", "0101", 60, 60, 60),
("1108", "2012-2013秋季", "08305004", "0101", 60, 60, 60);

SYSTEM echo "";

SYSTEM echo "3. 检索所有课程都选修的的学生的学号与姓名。";

SELECT
	Students.id,
	Students.name
FROM
	Students
WHERE NOT EXISTS (
	SELECT * FROM Courses WHERE NOT EXISTS (
		SELECT * FROM CourseSelection
		WHERE
			Students.id = CourseSelection.student_id AND
			Courses.id = CourseSelection.course_id))
ORDER BY
	Students.id ASC;

SYSTEM echo "";

SYSTEM echo "delete the testboy and all his records."

DELETE FROM CourseSelection WHERE student_id = "1108";
DELETE FROM Students WHERE id = "1108";

SYSTEM echo "";

SYSTEM echo "4. 检索选修课程包含1106同学所学全部课程的学生学号和姓名。";

SELECT DISTINCT
	Students.id,
	Students.name
FROM
	Students,
	CourseSelection AS cs1
WHERE
	Students.id = cs1.student_id AND
	cs1.student_id != "1106" AND
	NOT EXISTS (
		SELECT * FROM CourseSelection AS cs2
		WHERE
			cs2.student_id = "1106" AND
			NOT EXISTS (
				SELECT * FROM CourseSelection AS cs3
				WHERE
					cs3.student_id = cs1.student_id AND
					cs3.course_id = cs2.course_id));
SYSTEM echo "";

SYSTEM echo "5. 查询每门课程中分数最高的学生学号和学生姓名。";

SELECT
	Courses.id,
	Courses.name,
	Students.id,
	Students.name,
	MAX(CourseSelection.overall_score) AS "Top Score"
FROM
	Students,
	Courses,
	CourseSelection
WHERE
	Courses.id = CourseSelection.course_id AND
	Students.id = CourseSelection.student_id
GROUP BY
	CourseSelection.course_id
ORDER BY
	CourseSelection.course_id ASC;

SYSTEM echo "";

SYSTEM echo "6. 查询年龄小于本学院平均年龄，所有课程总评成绩都高于";
SYSTEM echo "所选课程平均总评成绩的学生学号、姓名和平均总评成绩，按年龄排序。";

SELECT DISTINCT
	Students.id AS "Student ID",
	Students.name AS "Student Name",
	AVG(CourseSelection.overall_score) AS "AVG Overall Score"
	/*
	CourseSelection.course_id AS "Course ID",
	CourseSelection.overall_score AS "Overall Score",
	AVGScoreTable.avg_score AS "Average Score",
	AgeTable.age AS "Age"
	*/
FROM 
	Students,
	CourseSelection,
	(
		SELECT
			CourseSelection.course_id,
			AVG(CourseSelection.overall_score) AS avg_score
		FROM
			CourseSelection
		GROUP BY
			CourseSelection.course_id
	) AS AVGScoreTable,
	(
		SELECT
			Students.id,
			YEAR(CURDATE()) - YEAR(Students.birthday) AS age,
			Students.college_id
		FROM
			Students
	) AS AgeTable,
	(
		SELECT
			Students.college_id,
			AVG(YEAR(CURDATE()) - YEAR(Students.birthday)) AS avg_age
		FROM
			Students
		GROUP BY
			Students.college_id
	) AS AVGAgeTable
WHERE
	Students.id = CourseSelection.student_id AND
	Students.id = AgeTable.id AND
	Students.college_id = AgeTable.college_id AND
	CourseSelection.course_id = AVGScoreTable.course_id AND

	CourseSelection.overall_score > AVGScoreTable.avg_score AND
	AgeTable.age < AVGAgeTable.avg_age
GROUP BY
	Students.id
ORDER BY
	AgeTable.age ASC;

SYSTEM echo "";

