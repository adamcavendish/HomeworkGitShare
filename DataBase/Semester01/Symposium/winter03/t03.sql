USE school;

SYSTEM echo "3. 查询每门课的排名，输出课程号，学号，总评成绩，排名；";
SYSTEM echo "按课程号升序，课程相同按排名从高到低。";
SYSTEM echo "（提示：某个同学一门课的排名就是该门课成绩大于等于他的人数）";

SELECT
	course_id,
	student_id,
	overall_score,
	(
		SELECT
			COUNT(student_id) + 1
		FROM
			CourseSelection t2
		WHERE
			t1.course_id = t2.course_id AND
			t2.overall_score > t1.overall_score
	) AS rank
FROM
	CourseSelection t1
WHERE
	t1.overall_score IS NOT NULL
ORDER BY
	course_id ASC,
	rank DESC;

