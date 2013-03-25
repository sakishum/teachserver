#ifndef _SQL_H_
#define _SQL_H_

#define SQL_SELECT_STU "SELECT student_id, class_id, password FROM student WHERE account = ?"
#define SQL_SELECT_COURSE "SELECT course_name FROM course WHERE course_name = ?"
#define SQL_SELECT_CLASS "SELECT count(*) AS COUNT FROM class WHERE class_name = ?"
#define SQL_SELECT_CLASSROOM "SELECT classroom_name, white_board FROM classroom WHERE classroom_name = ?"
#define SQL_SELECT_TEACHER "SELECT * FROM teacher WHERE account = ?"
#define SQL_SELECT_GRADE "SELECT grade_name FROM grade WHERE grade_name = ?"
#define SQL_SELECT_ALLSTU "SELECT stu.first_name, stu.last_name, stu.account, cla.class_name, gra.grade_name FROM student AS stu, class AS cla, grade AS gra WHERE stu.class_id = cla.class_id AND stu.grade_id = gra.grade_id AND gra.grade_name = ? AND cla.class_name = ?"

#endif
