DROP DATABASE CourseSelectionAndGradeManagement;
CREATE DATABASE CourseSelectionAndGradeManagement CHARACTER SET 'utf8' COLLATE 'utf8_general_ci';
USE CourseSelectionAndGradeManagement;

CREATE TABLE Students (
	SNO CHAR(4) NOT NULL,
	SNAME CHAR(8) NOT NULL,
	GENDER CHAR(2) NOT NULL,
	AGE CHAR(2) NOT NULL,
	SDEPT CHAR(10) NOT NULL,
	LOGN CHAR(20) NOT NULL,
	PSWD CHAR(20) NOT NULL,

	PRIMARY KEY(SNO)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE Courses (
	CNO CHAR(4) NOT NULL,
	CNAME CHAR(20) NOT NULL,
	CREDIT INTEGER NOT NULL,
	CDEPT CHAR(8) NOT NULL,
	TNAME CHAR(8) NOT NULL,

	PRIMARY KEY(CNO)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE CourseGrades (
	SNO CHAR(4) NOT NULL,
	CNO CHAR(4) NOT NULL,
	GRADE INTEGER,

	PRIMARY KEY(SNO, CNO),
	FOREIGN KEY(SNO) REFERENCES Students(SNO),
	FOREIGN KEY(CNO) REFERENCES Courses(CNO)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO Students(SNO, SNAME, GENDER, AGE, SDEPT, LOGN, PSWD) VALUES
("S1", "李銘", "男", 19, "計算機軟件", "S1", "S1"),
("S2", "劉曉鳴", "男", 20, "計算機應用", "S2", "S2"),
("S3", "李明", "男", 22, "計算機應用", "S3", "S3"),
("S4", "張鷹", "女", 21, "計算機軟件", "S4", "S4"),
("S5", "劉竟靜", "女", 22, "計算機軟件", "S5", "S5"),
("S6", "劉成剛", "男", 21, "計算機軟件", "S6", "S6");

INSERT INTO Courses(CNO, CNAME, CREDIT, CDEPT, TNAME) VALUES
("C1", "高級語言程序設計", 4, "計算機應用", "王曉名"),
("C2", "數據結構", 4, "計算機應用", "劉紅"),
("C3", "離散數學", 4, "計算機應用", "李嚴勁"),
("C4", "計算機原理", 6, "計算機軟件", "王曉名"),
("C5", "數據庫原理", 4, "計算機應用", "吳志剛"),
("C6", "WINDOW技術", 4, "計算機軟件", "吳志剛"),
("C8", "編譯原理", 4, "計算機軟件", "蔣瑩岳"),
("C9", "系統結構", 6, "計算機應用", "蔣瑩岳");

INSERT INTO CourseGrades(SNO, CNO, GRADE) VALUES
("S3", "C1", 88),
("S4", "C1", 67),
("S5", "C1", 67),
("S6", "C1", 78),
("S1", "C2", 66),
("S1", "C3", 88),
("S1", "C4", 60);

