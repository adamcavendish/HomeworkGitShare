use school;

SYSTEM echo "1. 用四种方法表达查询：检索马小红老师所授课程的学期，课程号，上课时间。"
SELECT OpenCourses.semester, OpenCourses.course_id, OpenCourses.time FROM OpenCourses, Teachers WHERE
	OpenCourses.teacher_id = Teachers.id AND
	Teachers.name = "馬小紅";

SELECT OpenCourses.semester, OpenCourses.course_id, OpenCourses.time FROM OpenCourses WHERE
	teacher_id IN (SELECT id FROM Teachers WHERE Teachers.name = "馬小紅");

/*
SELECT DISTINCT OpenCourses.semester, OpenCourses.course_id, OpenCourses.time FROM OpenCourses WHERE course_id IN
	(SELECT DISTINCT OpenCourses.course_id FROM OpenCourses WHERE time IN
		(SELECT DISTINCT OpenCourses.time FROM OpenCourses WHERE teacher_id IN
			(SELECT DISTINCT Teachers.id FROM Teachers WHERE Teachers.name = "馬小紅")));
*/

SELECT OpenCourses.semester, OpenCourses.course_id, OpenCourses.time FROM OpenCourses WHERE
	"馬小紅" IN (SELECT name FROM Teachers WHERE OpenCourses.teacher_id = Teachers.id);

SELECT OpenCourses.semester, OpenCourses.course_id, OpenCourses.time FROM OpenCourses WHERE EXISTS
	(SELECT name FROM Teachers WHERE OpenCourses.teacher_id = Teachers.id AND Teachers.name = "馬小紅");

SELECT OpenCourses.semester, OpenCourses.course_id, OpenCourses.time FROM OpenCourses
INNER JOIN Teachers ON OpenCourses.teacher_id = Teachers.id WHERE Teachers.name = "馬小紅";

SYSTEM echo;

