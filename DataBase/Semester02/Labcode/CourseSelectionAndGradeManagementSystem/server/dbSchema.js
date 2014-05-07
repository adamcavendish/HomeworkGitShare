// dbSchema.js

function buildStudent(mongoose) {
    var studentSchema = new mongoose.Schema({
        id: String,
        name: String,
        gender: Boolean, // true for male, false for female
        age: Number,
        collegeId: String,
        logn: String, // login username
        pswd: String  // login password
    }, {
        collection: 'Student'
    });
    
    var Student = mongoose.model('Student', studentSchema);
    return Student;
}

function buildCollege(mongoose) {
    var collegeSchema = new mongoose.Schema({
        id: String,
        name: String,
        addr: String,
        telephone: String,
    }, {
        collection: 'College'
    });
    
    var College = mongoose.model('College', collegeSchema);
    return College;
}

function buildTeacher(mongoose) {
    var teacherSchema = new mongoose.Schema({
        id: String,
        name: String,
        gender: Boolean, // true for male, false for female
        age: Number,
        collegeId: String,
        logn: String, // login username
        pswd: String  // login password
    }, {
        collection: 'Teacher'
    });
    
    var Teacher = mongoose.model('Teacher', teacherSchema);
    return Teacher;
}

function buildCourse(mongoose) {
    var courseSchema = new mongoose.Schema({
        id: String,
        name: String,
        credit: Number,
        classHours: Number,
        collegeId: String
    }, {
        collection: 'Course'
    });
    
    var Course = mongoose.model('Course', courseSchema);
    return Course;
}

function buildOpenCourse(mongoose) {
    var openCourseSchema = new mongoose.Schema({
        semester: String,
        courseId: String,
        teacherId: String,
        time: String
    }, {
        collection: 'OpenCourse'
    });
    
    var OpenCourse = mongoose.model('OpenCourse', openCourseSchema);
    return OpenCourse;
}

function buildCourseSelection(mongoose) {
    var courseSelectionSchema = new mongoose.Schema({
        studentId: String,
        semester: String,
        courseId: String,
        teacherId: String,
        overallScore: Number
    }, {
        collection: 'CourseSelection'
    });
    var CourseSelection = mongoose.model('CourseSelection', courseSelectionSchema);
    return CourseSelection;
}

module.exports = function(mongoose) {
    return {
        Student: buildStudent(mongoose),
        College: buildCollege(mongoose),
        Teacher: buildTeacher(mongoose),
        Course: buildCourse(mongoose),
        OpenCourse: buildOpenCourse(mongoose),
        CourseSelection: buildCourseSelection(mongoose)
    };
}
