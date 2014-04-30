module.exports = function(config) {
    console.log(config.db_host);
    console.log(config.db_user);
    console.log(config.db_pass);

    return function(req, res, next) { next(); };
}
