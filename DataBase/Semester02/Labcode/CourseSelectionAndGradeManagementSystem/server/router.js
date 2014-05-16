// router.js
var mongoose = require('mongoose');

// user_attr: 2 for root, 1 for teacher, 0 for student

module.exports = function(app) {
    var debugInfo = require('../debugInfo.js');
    
    app.route('/').get(function(req, res) {
        if(req.cookies.user) {
            res.redirect('home');
        } else {
            res.render('index');
        }//if-else
    });
    
    app.route('/users').get(function(req, res) {
        res.render('users');
    });
    
    app.route('/login').post(function(req, res) {
        var cookieAge = 60 * 60 * 1000; // 1000 mins
        
        if(req.cookies.user) {
            res.clearCookie('user');
            res.clearCookie('user_attr');
        }//if
        
        var m_user = req.body.username;
        var m_pswd = req.body.password;
        var config = app.get('config');
        
        debugInfo.printUserAndPswd(app, m_user, m_pswd);
        
        var loginError = function() {
            console.log('Invalid username or password!');
            res.send('Invalid username or password!');
        }

        if(m_user === config.db_user && m_pswd === config.db_pass) {
            console.log('Login with root');
            
            res.cookie('user', m_user, { maxAge: cookieAge });
            res.cookie('user_attr', '2', { maxAge: cookieAge });
            
            console.log('Login as: ' + JSON.stringify(m_user));
            res.redirect('/home');  
        } else if(m_user[0] === 'S') {
            // login with Student
            req.schema.Student.find({ 'logn': m_user, 'pswd': m_pswd }, function(err, students) {
                if(students.length > 0) {
                    console.log('Login with student in db: ');
                    console.log(students);
                    
                    res.cookie('user', m_user, { maxAge: cookieAge });
                    res.cookie('user_attr', '0', { maxAge: cookieAge });
                    
                    console.log('Login as: ' + JSON.stringify(m_user));
                    res.redirect('/home');  
                } else {
                    console.log('Login student not found');
                    loginError();
                }//if-else
            });
        } else if(m_user[0] === 'T') {
            // login with Teacher
            req.schema.Teacher.find({ logn: m_user, pswd: m_pswd }, function(err, teachers) {
                if(teachers.length > 0) {
                    console.log('Login with teacher in db: ');
                    console.log(teachers);
                    
                    res.cookie('user', m_user, { maxAge: cookieAge });
                    res.cookie('user_attr', '1', { maxAge: cookieAge });
                    
                    console.log('Login as: ' + JSON.stringify(m_user));
                    res.redirect('/home');
                } else {
                    console.log('Login teacher not found');
                    loginError();
                }//if-else
            });
        } else {
            loginError();
        }//if-else
    });
    
    app.route('/home').get(function(req, res) {
        console.log('cookies: ');
        console.log(req.cookies);
        
        var cur_user = req.cookies.user;
        var cur_user_attr = req.cookies.user_attr;
        
        if(cur_user === null || cur_user === undefined) {
            res.send("You're not logged in!");
        } else if(cur_user_attr === '2') {
            res.render('rootManagement');
        } else if(cur_user_attr === '1') {
            res.render('gradeManagement');
        } else if(cur_user_attr === '0') {
            res.render('courseSelection');
        } else {
            res.send("You're not logged in. Corrupted user: " + cur_user + " user_attr: " + cur_user_attr + " !");
        }//if-else
    });
    
    app.route('/logout').get(function(req, res) {
        res.clearCookie('user');
        res.clearCookie('user_attr');
        res.redirect('/');
    });
    
    // -----------------Student-------------------------
    app.route('/Student.json').get(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            console.log('Not logged in, get /Student.json failed!');
            res.end();
        } else {
            req.schema.Student.find(function(err, students) {
                res.json(students);
            });
        }//if-else
    });
    
    app.route('/addStudent_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            res.json({ msg: "You're not root!"});
        } else {
            console.log('Trying to add student: ');
            console.log(req.body);
            var student = new req.schema.Student(req.body);

            student.save(function(error, data) {
                res.json((error === null) ? { msg: '' } : { msg: error });
            });
        }//if-else
    });
    
    app.route('/delStudent_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            res.json({ msg: "You're not root!"});
        } else {
            console.log('Trying to del a student: ');
            console.log(req.body);

            req.schema.Student.remove({ id: req.body.id }, function(error, result) {
                res.json((error == null) ? { msg: '' } : { msg: error });
            });
        }//if-else
    });
    
    // -----------------------Teacher-----------------------
    app.route('/Teacher.json').get(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            console.log('Not logged in, get /Teacher.json failed!');
            res.end();
        } else {
            req.schema.Teacher.find(function(err, teachers) {
                res.json(teachers);
            });
        }//if-else
    });
    
    app.route('/addTeacher_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            res.json({ msg: "You're not root!"});
        } else {
            console.log('Trying to add a teacher: ');
            console.log(req.body);
            var teacher = new req.schema.Teacher(req.body);

            teacher.save(function(error, data) {
                res.json((error === null) ? { msg: '' } : { msg: error });
            });
        }//if-else
    });

    app.route('/delTeacher_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            res.json({ msg: "You're not root!"});
        } else {
            console.log('Trying to del a teacher: ');
            console.log(req.body);

            req.schema.Teacher.remove({ id: req.body.id }, function(error, result) {
                res.json((error == null) ? { msg: '' } : { msg: error });
            });
        }//if-else
    });
    
    // ---------------------Course---------------------
    app.route('/Course.json').get(function(req, res) {
        req.schema.Course.find(function(err, courses) {
            res.json(courses);
        });
    });

    app.route('/addCourse_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            res.json({ msg: "You're not root!"});
        } else {
            console.log('Trying to add a Course: ');
            console.log(req.body);
            var course = new req.schema.Course(req.body);

            course.save(function(error, data) {
                res.json((error === null) ? { msg: '' } : { msg: error });
            });
        }//if-else
    });

    app.route('/delCourse_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            res.json({ msg: "You're not root!"});
        } else {
            console.log('Trying to del a Course: ');
            console.log(req.body);

            req.schema.Course.remove({ id: req.body.id }, function(error, result) {
                res.json((error == null) ? { msg: '' } : { msg: error });
            });
        }//if-else
    });
    
    // ----------------College------------------
    app.route('/College.json').get(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            console.log('Not logged in, get /College.json failed!');
            res.end();
        } else {
            req.schema.College.find(function(err, colleges) {
                res.json(colleges);
            });
        }//if-else
    });

    app.route('/addCollege_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            res.json({ msg: "You're not root!"});
        } else {    
            console.log('Trying to add a College: ');
            console.log(req.body);
            var college = new req.schema.College(req.body);

            college.save(function(error, data) {
                res.json((error === null) ? { msg: '' } : { msg: error });
            });
        }//if-else
    });

    app.route('/delCollege_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            res.json({ msg: "You're not root!"});
        } else {
            console.log('Trying to del a College: ');
            console.log(req.body);

            req.schema.College.remove({ id: req.body.id }, function(error, result) {
                res.json((error == null) ? { msg: '' } : { msg: error });
            });
        }//if-else
    });
    
    // ----------------OpenCourse-----------------
    app.route('/OpenCourse.json').get(function(req, res) {
        req.schema.OpenCourse.find(function(err, openCourses) {
            res.json(openCourses);
        });
    });

    app.route('/addOpenCourse_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            res.json({ msg: "You're not root!"});
        } else {
            console.log('Trying to add a Opened Course: ');
            console.log(req.body);
            var openCourse = new req.schema.OpenCourse(req.body);

            openCourse.save(function(error, data) {
                res.json((error === null) ? { msg: '' } : { msg: error });
            });
        }//if-else
    });

    app.route('/delOpenCourse_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        if(cur_user !== 'root') {
            res.json({ msg: "You're not root!"});
        } else {
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
        }//if-else
    });
    
    // ----------------CourseSelection-----------------
    app.route('/CourseSelection.json').get(function(req, res) {
        var cur_user = req.cookies.user;
        var cur_user_attr = req.cookies.user_attr;
        
        if(cur_user === null || cur_user === undefined) {
            console.log('Not logged in, get /CourseSelection.json failed!');
            res.end();
            return;
        } else if(cur_user_attr == 2) {
            // root
            req.schema.CourseSelection.find(function(err, courseSelection) {
                res.json(courseSelection);
            });
        } else if(cur_user_attr == 1) {
            // teacher
            req.schema.CourseSelection.find({'teacherId': cur_user}, function(err, courseSelection) {                
                res.json(courseSelection);
                return;
            });
        } else if(cur_user_attr == 0) {
            req.schema.CourseSelection.find({'studentId': cur_user}, function(err, courseSelection) {
                res.json(courseSelection);
                return;
            });
        } else {
            console.log('corrupted user attr: ' + JSON.stringify(cur_user_attr));
            res.end();
            return;
        }//if-else
    });

    app.route('/addCourseSelection_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        var reqData = req.body;
        
        if(cur_user !== 'root') {
            if(typeof reqData.studentId !== 'undefined') {
                console.log('Not root but post with studentId: ' + JSON.stringify(reqData.studentId));
                res.json({msg: "Are you hacking me?"});
                return;
            }//if
            reqData.studentId = cur_user;
        }//if
        
        console.log('Trying to add a Course Selection: ');
        console.log(reqData);
        
        var courseSelection = new req.schema.CourseSelection(reqData);

        courseSelection.save(function(error, data) {
            res.json((error === null) ? { msg: '' } : { msg: error });
        });
    });

    app.route('/delCourseSelection_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        var cur_user_attr = req.cookies.user_attr;
        
        var reqData = req.body;

        if(cur_user_attr == 2) {
            // root
            // pass
        } else if(cur_user_attr == 1) {
            // teacher
            if(typeof reqData.teacherId === 'undefined') {
                reqData.teacherId = cur_user;
            } else if(reqData.teacherId !== cur_user) {
                console.log('Not root but post with unmatched teacherId: ' + JSON.stringify(reqData.teacherId));
                res.json({msg: 'Are you hacking me?'});
                return;
            }//if-else
        } else if(cur_user_attr == 0) {
            if(typeof reqData.studentId === 'undefined') {
                reqData.studentId = cur_user;
            } else if(reqData.studentId !== cur_user) {
                console.log('Not root but post with unmatched studentId: ' + JSON.stringify(reqData.studentId));
                res.json({msg: 'Are you hacking me?'});
                return;
            }//if-else
        } else {
            console.log('corrupted user attr: ' + JSON.stringify(cur_user_attr));
            res.json({msg: 'corrupted user attr!'});
            return;
        }//if-else
        
        console.log('Trying to del a Course Selection: ');
        console.log(reqData);

        req.schema.CourseSelection.remove({
            studentId: reqData.studentId,
            semester: reqData.semester,
            courseId: reqData.courseId,
            teacherId: reqData.teacherId
        }, function(error, result) {
            res.json((error == null) ? { msg: '' } : { msg: error });
        });
    });
    
    app.route('/updateCourseSelection_post').post(function(req, res) {
        var cur_user = req.cookies.user;
        var cur_user_attr = req.cookies.user_attr;
        
        var reqData = req.body;
        
        if(cur_user_attr == 2) {
            // root
            console.log('root is granted the right, however root doesn\'t have a form to post this data. Are you hacking me?');
            res.end();
        } else if(cur_user_attr == 1) {
            // teacher
            console.log('Trying to update score to: ');
            console.log(reqData);
            req.schema.CourseSelection.update(
                {_id: mongoose.Types.ObjectId(reqData._id)},
                {$set: {overallScore: reqData.overallScore}},
                { multi: false },
                function(error, numAffected) {
                    console.log('update num affected: ' + JSON.stringify(numAffected));
                    res.json((error === null) ? {msg: ''} : {msg: error});
                    return;
                });
        } else if(cur_user_attr == 0) {
            // student
            console.log('You\'re a student. permission denied!');
            res.end();
        } else {
            console.log('corrupted user attr: ' + JSON.stringify(cur_user_attr));
            res.json({msg: 'corrupted user attr!'});
            return;
        }
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
