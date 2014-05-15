module.exports.printConfig = function(app) {
    if(app.get('isDebug')) {
        var config = app.get('config');
        console.log(config.db_host);
        console.log(config.db_user);
        console.log(config.db_pass);
    }//if
};
    
module.exports.printUserAndPswd = function(app, user, pswd) {
    if(app.get('isDebug')) {
        console.log('user: ' + user + ' pswd: ' + pswd);
    }//if
}
