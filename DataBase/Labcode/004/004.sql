USE school;

SYSTEM echo "1. 建立计算机学院总评不及格成绩学生的视图，";
SYSTEM echo "包括学生学号、姓名、性别、手机、所选课程和成绩。";

CREATE VIEW FailedStudents AS (
	SELECT Students.id, Students.name, Students.gender, Students.cellphone, CourseSelection.course_id, CourseSelection.overall_score
	FROM Students, CourseSelection
	WHERE 
	Students.id = CourseSelection.student_id AND
	(CourseSelection.overall_score < 60 OR
		CourseSelection.overall_score IS NULL));

SYSTEM echo "FailedStudents View: ";
SELECT * FROM FailedStudents;

DROP VIEW FailedStudents;

SYSTEM echo "";

SYSTEM echo "2. 在CourseSelection表中插入记录，把每个学生没学过的课程都插入到表中";
SYSTEM echo "使得每个学生都选修每门课";

CREATE TEMPORARY TABLE CS_tmp SELECT * FROM CourseSelection;

INSERT INTO CS_tmp(student_id, semester, course_id, teacher_id) (
    SELECT DISTINCT
        Students.id,
        OpenCourses.semester,
        OpenCourses.course_id,
        OpenCourses.teacher_id
    FROM
        OpenCourses, Students
    WHERE
        OpenCourses.course_id NOT IN (
            SELECT DISTINCT
                CourseSelection.course_id
            FROM
                CourseSelection
            WHERE
                CourseSelection.student_id = Students.id));

SYSTEM echo "CourseSelection: ";
SELECT * FROM CourseSelection;
SYSTEM echo "CS_tmp: ";
SELECT * FROM CS_tmp;

DROP TABLE CS_tmp;

SYSTEM echo "";

SYSTEM echo "3. 求年龄大于所有女同学年龄的男学生姓名和年龄。";

SELECT
    S1.name,
    YEAR(CURDATE()) - YEAR(S1.birthday) AS age
FROM
    Students AS S1
WHERE
    S1.gender = '男' AND
    NOT EXISTS (
        SELECT * FROM Students AS S2 WHERE
            S2.gender = '女' AND
            (YEAR(CURDATE()) - YEAR(S1.birthday)) <= (YEAR(CURDATE()) - YEAR(S2.birthday)));

SYSTEM echo "";

SYSTEM echo "4. 在E表中修改08305001课程的平时成绩，若成绩小于等于75分时提高5%，若成绩大于75分时提高4%。"

CREATE TEMPORARY TABLE CS_tmp SELECT * FROM CourseSelection;

UPDATE CS_tmp SET CS_tmp.usual_time_score = CS_tmp.usual_time_score * 1.05 WHERE
    CS_tmp.course_id = '08305001' AND
    CS_tmp.usual_time_score < 75;
UPDATE CS_tmp SET CS_tmp.usual_time_score = CS_tmp.usual_time_score * 1.04 WHERE
    CS_tmp.course_id = '08305001' AND
    CS_tmp.usual_time_score >= 75;

SYSTEM echo "CourseSelection: ";
SELECT * FROM CourseSelection WHERE course_id = '08305001';
SYSTEM echo "CS_tmp: ";
SELECT * FROM CS_tmp WHERE course_id = '08305001';

DROP TABLE CS_tmp;

SYSTEM echo "";

SYSTEM echo "5. 删除没有开课的学院。";

CREATE TEMPORARY TABLE Colleges_tmp SELECT * FROM Colleges;

DELETE FROM Colleges_tmp WHERE Colleges_tmp.id NOT IN (SELECT college_id FROM Courses);

SYSTEM echo "Colleges: ";
SELECT * FROM Colleges;
SYSTEM echo "Colleges_tmp: ";
SELECT * FROM Colleges_tmp;

DROP TABLE Colleges_tmp;

SYSTEM echo "";

SYSTEM echo "6. 查询优、良、中、及格、不及格学生人数";

SYSTEM echo "優秀 (>=90): ";
SELECT COUNT(student_id) FROM CourseSelection WHERE overall_score >= 90 AND overall_score IS NOT NULL;
SYSTEM echo "良好 (>=80): ";
SELECT COUNT(student_id) FROM CourseSelection WHERE overall_score >= 80 AND overall_score IS NOT NULL;
SYSTEM echo "中等 (>=70): ";
SELECT COUNT(student_id) FROM CourseSelection WHERE overall_score >= 70 AND overall_score IS NOT NULL;
SYSTEM echo "及格 (>=60): ";
SELECT COUNT(student_id) FROM CourseSelection WHERE overall_score >= 60 AND overall_score IS NOT NULL;
SYSTEM echo "不及格 (<60): ";
SELECT COUNT(student_id) FROM CourseSelection WHERE overall_score < 60 AND overall_score IS NOT NULL;

SYSTEM echo "";

