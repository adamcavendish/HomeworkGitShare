USE school;
SELECT gender, COUNT(id), AVG(birthday) FROM Students GROUP BY gender;

SYSTEM echo "查詢每門課程都超過70分的學生學號";
SELECT student_id, overall_score FROM CourseSelection GROUP BY student_id HAVING min(overall_score) > 70;

SELECT student_id, count(student_id), sum(overall_score) FROM CourseSelection
GROUP BY student_id ORDER BY 3 ASC, 2 DESC;

SYSTEM echo "統計每個學生選修課程的門數(超過5門的學生才統計)。要求輸出學生學號和選修門數";
SYSTEM echo "查詢結果按門數降序排列";
SYSTEM echo "若門數相同，按照學號升序排列";
/* SELECT student_id, count(student_id) FROM CourseSelection GROUP BY student_id
HAVING count(student_id) >= 5 ORDER BY count(student_id) DESC, student_id ASC; */

SYSTEM echo "查找選修了VB課程且成績在70分以上的學生姓名和成績";
SELECT Students.id, CourseSelection.overall_score FROM Students, Courses, CourseSelection
WHERE
	Students.id = CourseSelection.student_id AND
	CourseSelection.course_id = Courses.id AND
	Courses.name = "數據結構" AND
	CourseSelection.overall_score > 70;

SYSTEM echo "查詢每門課程都超過70分的學生學號和姓名";
/* SELECT DISTINCT Students.id, Students.name FROM Students, CourseSelection WHERE
	Students.id = CourseSelection.student_id AND
	CourseSelection.overall_score > 70; */
SELECT Students.id, Students.name FROM Students, CourseSelection WHERE Students.id = CourseSelection.student_id
GROUP BY Students.id having min(CourseSelection.overall_score) > 70;

SYSTEM echo "統計每個學生選修課程的門數(超過5門的學生才統計)。要求輸出學生學號，姓名和選修門數";
SYSTEM echo "查詢結果按門數降序排列";
SYSTEM echo "若門數相同，按照學號升序排列";
/* @TODO */

SYSTEM echo "查詢平均成績超過所有女學生成績的男學生的學號和姓名";
SELECT Students.id, Students.name FROM Students, CourseSelection WHERE
	Students.id = CourseSelection.student_id AND
	Students.gender='男'
GROUP BY Students.id HAVING avg(CourseSelection.overall_score) > ALL(
	SELECT CourseSelection.overall_score FROM Students, CourseSelection WHERE
		Students.id = CourseSelection.student_id AND gender='女'
);

SYSTEM echo "查詢沒有選修C2課程的學號和姓名";
/* select sname, sno from s where sno not in (
	select sno from sc where cno='c2'); */
/* Select sname, sno from s where sno not exists(
	select * from sc where s.sno = sc.sno and cno = 'c2');*/
/*
	@NOTE `EXISTS` has better performance than `IN`
	EXISTS will execute the outter `select` first and then the inner one
	IN is vice versa, which is first inner and then outter.
*/

SYSTEM echo "查詢所有學生都選修的課程號和課程名";
SELECT cno, cname from c where not exists(
	select * from s where not exists(
		select * from sc where sc.sno=s.sno and sc.cno = c.cno));
/*
	@NOTE all(x) in P === not exist(x) not in P
	全稱量詞的轉化爲雙重否定問題
*/

SYSTEM echo "求選修學號爲S3的學生所修的課程的學生號碼";
SYSTEM echo "	Explanation:";
SYSTEM echo "	course = 學號爲S3的學生所修的全部課程;";
SYSTEM echo "	求至少選修了courses.all的學生的學號";
/* SELECT distinct sno from sc x where not exists(
	select * from sc y where sno='s3' and not exists (
		select * from sc z where sno=x.sno and cno=y.cno)); */













