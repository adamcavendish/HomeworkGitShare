SYSTEM echo "刪除沒有選任何一門課的學生信息";
DELETE FROM Students WHERE Students.id NOT IN (
	SELECT student_id FROM CourseSelection);

SYSTEM echo "刪除數據庫原理課程的選課數據";
DELETE FROM CourseSelection WHERE cousre_id IN (
	SELECT id FROM Courses WHERE name="數據庫原理");

