var express = require('express')
  , app = module.exports = express();

var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

// parses request cookies, populating
// req.cookies and req.signedCookies
// when the secret is passed, used 
// for signing the cookies.
app.use(cookieParser('my secret here'));

// parses json, x-www-form-urlencoded, and multipart/form-data
app.use(bodyParser());

app.get('/', function(req, res){
  if (req.cookies.remember) {
    res.send('Remembered :). Click to <a href="/forget">forget</a>!.');
  } else {
    res.send('<form method="post"><p>Check to <label>'
      + '<input type="checkbox" name="remember"/> remember me</label> '
      + '<input type="submit" value="Submit"/>.</p></form>');
  }
});

app.get('/forget', function(req, res){
  res.clearCookie('remember');
  res.redirect('back');
});

app.post('/', function(req, res){
  var minute = 60 * 1000;
  if (req.body.remember) res.cookie('remember', 1, { maxAge: minute });
  res.redirect('back');
});


app.listen(8000);
console.log('Express started on port %d', 8000);

