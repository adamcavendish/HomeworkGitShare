// router.js

// user_attr: 2 for root, 1 for teacher, 0 for student

module.exports = function(app) {
    app.route('/').get(function(req, res) {
        if(req.cookies.user) {
            res.render('home');
        } else {
            res.render('index');
        }//if-else
    });
    
    app.route('/users').get(function(req, res) {
        res.render('users');
    });
    
    app.route('/login').post(function(req, res) {
        var cookieAge = 60 * 1000; // 1000 mins
        
        var m_user = req.body.username;
        var m_pswd = req.body.password;
        var config = app.get('config');
        
        var loginEror = false;

        if(m_user === config.db_user && m_pswd === config.db_pass) {
            res.cookie('user', m_user, { maxAge: cookieAge });
            res.cookie('user_attr', '2', { maxAge: cookieAge });
        } else if(m_user[0] === 'S') {
            // login with Student
            req.schema.Student.find({ logn: m_user, pswd: m_pswd }, function(err, students) {
                if(students.length !== 0) {
                    res.cookie('user', m_user, { maxAge: cookieAge });
                    res.cookie('user_attr', '0', { maxAge: cookieAge });
                } else {
                    loginEror = true;
                }//if-else
            });
        } else if(m_user[0] === 'T') {
            // login with Teacher
            req.schema.Teacher.find({ logn: m_user, pswd: m_pswd }, function(err, teachers) {
                if(teachers.length !== 0) {
                    res.cookie('user', m_user, { maxAge: cookieAge });
                    res.cookie('user_attr', '1', { maxAge: cookieAge });
                } else {
                    loginEror = true;
                }
            });
        } else {
            // login error
            loginEror = true;
        }//if-else

        if(loginEror) {
            res.send('Invalid username or password!');
            console.log('Invalid username or password!');
            return;
        }//if
        
        console.log('Login as: ' + m_user);
        res.redirect('/home');    
    });
    
    app.route('/home').get(function(req, res) {
        console.log('cookies: ');
        console.log(req.cookies);
        
        var cur_user = req.cookies.user;
        var cur_user_attr = req.cookies.user_attr;
        
        if(cur_user === null) {
            res.send("You're not logged in!");
        } else if(cur_user_attr === '2') {
            res.render('rootManagement');
        } else if(cur_user_attr === '1') {
            res.render('gradeManagement');
        } else if(cur_user_attr === '0') {
            res.render('courseSelection');
        } else {
            res.send("You're not logged in. Corrupted user_attr!");
        }//if-else
    });
    
    app.route('/logout').get(function(req, res) {
        res.clearCookie('user');
        res.clearCookie('user_attr');
        res.redirect('/');
    });
    
    // -----------------Student-------------------------
    app.route('/Student.json').get(function(req, res) {
        req.schema.Student.find(function(err, students) {
            res.json(students);
        });
    });
    
    app.route('/addStudent_post').post(function(req, res) {
        console.log('Trying to add student: ');
        console.log(req.body);
        var student = new req.schema.Student(req.body);
        
        student.save(function(error, data) {
            res.json((error === null) ? { msg: '' } : { msg: error });
        });
    });
    
    app.route('/delStudent_post').post(function(req, res) {
        console.log('Trying to del a student: ');
        console.log(req.body);
        
        req.schema.Student.remove({ id: req.body.id }, function(error, result) {
            res.json((error == null) ? { msg: '' } : { msg: error });
        });
    });
    
    // -----------------------Teacher-----------------------
    app.route('/Teacher.json').get(function(req, res) {
        req.schema.Teacher.find(function(err, teachers) {
            res.json(teachers);
        });
    });
    
    app.route('/addTeacher_post').post(function(req, res) {
        console.log('Trying to add a teacher: ');
        console.log(req.body);
        var teacher = new req.schema.Teacher(req.body);

        teacher.save(function(error, data) {
            res.json((error === null) ? { msg: '' } : { msg: error });
        });
    });

    app.route('/delTeacher_post').post(function(req, res) {
        console.log('Trying to del a teacher: ');
        console.log(req.body);

        req.schema.Teacher.remove({ id: req.body.id }, function(error, result) {
            res.json((error == null) ? { msg: '' } : { msg: error });
        });
    });
    
    // ---------------------Course---------------------
    app.route('/Course.json').get(function(req, res) {
        req.schema.Course.find(function(err, courses) {
            res.json(courses);
        });
    });

    app.route('/addCourse_post').post(function(req, res) {
        console.log('Trying to add a Course: ');
        console.log(req.body);
        var course = new req.schema.Course(req.body);

        course.save(function(error, data) {
            res.json((error === null) ? { msg: '' } : { msg: error });
        });
    });

    app.route('/delCourse_post').post(function(req, res) {
        console.log('Trying to del a Course: ');
        console.log(req.body);

        req.schema.Course.remove({ id: req.body.id }, function(error, result) {
            res.json((error == null) ? { msg: '' } : { msg: error });
        });
    });
    
    // ----------------College------------------
    app.route('/College.json').get(function(req, res) {
        req.schema.College.find(function(err, colleges) {
            res.json(colleges);
        });
    });

    app.route('/addCollege_post').post(function(req, res) {
        console.log('Trying to add a College: ');
        console.log(req.body);
        var college = new req.schema.College(req.body);

        college.save(function(error, data) {
            res.json((error === null) ? { msg: '' } : { msg: error });
        });
    });

    app.route('/delCollege_post').post(function(req, res) {
        console.log('Trying to del a College: ');
        console.log(req.body);

        req.schema.College.remove({ id: req.body.id }, function(error, result) {
            res.json((error == null) ? { msg: '' } : { msg: error });
        });
    });
    
    // ----------------OpenCourse-----------------
    app.route('/OpenCourse.json').get(function(req, res) {
        req.schema.OpenCourse.find(function(err, openCourses) {
            res.json(openCourses);
        });
    });

    app.route('/addOpenCourse_post').post(function(req, res) {
        console.log('Trying to add a Opened Course: ');
        console.log(req.body);
        var openCourse = new req.schema.OpenCourse(req.body);

        openCourse.save(function(error, data) {
            res.json((error === null) ? { msg: '' } : { msg: error });
        });
    });

    app.route('/delOpenCourse_post').post(function(req, res) {
        console.log('Trying to del a Opened Course: ');
        console.log(req.body);

        req.schema.OpenCourse.remove({
            semester: req.body.semester,
            courseId: req.body.courseId,
            teacherId: req.body.teacherId,
            time: req.body.time
        }, function(error, result) { 
            res.json((error == null) ? { msg: '' } : { msg: error });
        });
    });
    
    // ----------------CourseSelection-----------------
    app.route('/CourseSelection.json').get(function(req, res) {
        req.schema.CourseSelection.find(function(err, courseSelection) {
            res.json(courseSelection);
        });
    });

    app.route('/addCourseSelection_post').post(function(req, res) {
        console.log('Trying to add a Course Selection: ');
        console.log(req.body);
        var courseSelection = new req.schema.CourseSelection(req.body);

        courseSelection.save(function(error, data) {
            res.json((error === null) ? { msg: '' } : { msg: error });
        });
    });

    app.route('/delCourseSelection_post').post(function(req, res) {
        console.log('Trying to del a Course Selection: ');
        console.log(req.body);

        req.schema.CourseSelection.remove({
            studentId: req.body.studentId,
            semester: req.body.semester,
            courseId: req.body.courseId,
            teacherId: req.body.teacherId
        }, function(error, result) {
            res.json((error == null) ? { msg: '' } : { msg: error });
        });
    });
}

/*
exports.sendfile = function(req, res) {
    res.sendfile('./public/images/logo.png', function(err) {
        if(err) {
            console.log(err);
        } else {
            console.log('file sent');
        }//if-else
    });
};
*/
