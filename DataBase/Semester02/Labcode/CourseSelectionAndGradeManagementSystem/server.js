// requires
var express = require('express');
var namespace = require('express-namespace');
var resource = require('express-resource');
var morganLogger = require('morgan');
var favicon = require('static-favicon');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var responseTime = require('response-time');
var errorhandler = require('errorhandler');
var http = require('http');
var path = require('path');
var mysql = require('mysql');
var connect = null;

var app = express();
var router = require('./router/router.js');
var testMain = require('./testMain.js');

// global configs
var config = require('./config.json')[app.get('env')];
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

// static dirs
app.use(express.static('./public'));
app.use(express.static('./bower_components'));
app.use(express.static('./public/images'));
app.use(express.static('./public/js'));
app.use(express.static('./public/css'));

// env
console.log('--------------------------------------------------');
console.log('env: ', app.get('env'));
console.log('--------------------------------------------------');

// middleware
if(app.get('env') === 'development') {
    app.use(testMain(config));
}//if
app.use(favicon());
app.use(morganLogger('dev')); // logger
app.use(bodyParser.json());
app.use(bodyParser.urlencoded());
app.use(cookieParser());
app.use(responseTime());
app.use(errorhandler());

// MySQL Connect
connect = mysql.createConnection({
    host: config.db_host,
    user: config.db_user,
    password: config.db_pass,
    database: config.db_database
});
connect.connect();
app.use(function(req, res, next) {
    req.db = connect;
    next();
});

// router
app.route('/').get(router.index);
app.route('/login').post(router.login);

var server = app.listen(config.port, function() {
    console.log('Listening on port %d', server.address().port);
});
