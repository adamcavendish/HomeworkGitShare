/* 在SC表中檢索某學生選課信息(SNO, CNO, GRADE) */

EXEC SQL BEGIN DECLARE SECTION;
	char sno[5] /* .... */;
EXEC SQL END DECLARE SECTION;

EXEC SQL DECLARE scx CURSOR FOR
	SELECT SNO, CNO, GRADE
	FROM SC
	WHERE SNO=(SELECT SNO FROM S WHERE SNAME = :givensname)
	FOR UPDATE OF GRADE;

EXEC SQL OPEN scx;
WHILE(1) {
	EXEC SQL FETCH FROM scx INTO :sno, :cno, :grade; /* get the current ptr-ptd-val, and get next */
	IF(SQLCA.SQLSTATE == '02000') /* 已取完查詢結果中的所有元祖 */
		BRAKE;
	
		if(SQLCA.SQLSTATE != '0') /* 取數據出錯 */
			Break;

		/* ... */
		if(grae < 60) {
			EXEC SQL DELETE FROM SC WHERE CURRENT OF scx;
		} ELSE {
			EXEC SQL UPDATE SC
				SET GRADE= GRADE + :rise
				WHERE CURRENT OF scx;
				grade = grade + rise;
		}

		printf("%s, %$s, %d", sno, cno, grade);
}
EXEC SQL CLOSE scx;

/*
CURSOR usage:
	1. open
	2. fetch
	3. close
*/

