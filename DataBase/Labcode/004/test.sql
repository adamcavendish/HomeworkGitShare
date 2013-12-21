SELECT
	Students.id,
	OpenCourses.semester,
	OpenCourses.course_id,
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
ORDER BY Students.id, OpenCourses.course_id, OpenCourses.teacher_id, OpenCourses.semester;

SELECT
	Students.id,
	OpenCourses.semester,
	OpenCourses.course_id,
	OpenCourses.teacher_id
FROM
	OpenCourses,
	Students
WHERE
	OpenCourses.course_id NOT IN (
		SELECT course_id FROM CourseSelection WHERE Students.id = CourseSelection.student_id) OR
	OpenCourses.semester NOT IN (
		SELECT semester FROM CourseSelection WHERE Students.id = CourseSelection.student_id) OR
	OpenCourses.teacher_id NOT IN (
		SELECT teacher_id FROM CourseSelection WHERE Students.id = CourseSelection.student_id)
ORDER BY Students.id, OpenCourses.course_id, OpenCourses.teacher_id, OpenCourses.semester;

