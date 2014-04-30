// user.js

exports.index = function(req, res) {
    res.send('index of users');
};

exports.new = function(req, res) {
    res.send('form for new users');
};

exports.create = function(req, res) {
    res.send('handle form for new user');
};

exports.show = function(req, res) {
    res.send('show user ' + req.params.user);
};

exports.edit = function(req, res) {
    res.send('form to edit user ' + req.params.user);
};

exports.update = function(req, res) {
    console.log('req.params: ' + req.params);
    res.send('handle forms to edit user ' + req.params.user + '<br/> get TheKey: ' + req.params.TheKey);
};

exports.destroy = function(req, res) {
    res.send('delete user ' + req.params.user);
};

