// router.js

exports.index = function(req, res) {
    res.render('index');
};

exports.login = function(req, res) {
    console.log(req.db);
    res.send(404);
};

exports.hello_txt = function(req, res) {
    // Send a plain text response
    res.send('Hola!');
};

exports.index = function(req, res) {
    res.render('index');
};

exports.sj01 = function(req, res) {
    res.render('sj01');
};
    
exports.contact = function(info) {
    return function(req, res) {
        // Render a veiw
        res.render('contact', {
            "title": info.title,
            "message": info.message,
            "youAreUsingJade": true
        });
    };
};

exports.sendfile = function(req, res) {
    res.sendfile('./public/images/logo.png', function(err) {
        if(err) {
            console.log(err);
        } else {
            console.log('file sent');
        }//if-else
    });
};

