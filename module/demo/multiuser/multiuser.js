var express = require('express'),
    app = express.createServer(),
    assert = require('assert'),
    fs = require('fs')
    ;


/* 
 * app config 
 */

app.set('view engine', 'jade');

app.use(express.cookieParser());
app.use(express.session({ 
    secret: '16dawdaw4+8aw6.-51dagaw5',
    key: 'casino-session-test',
    cookie: { path: '/', httpOnly: false, maxAge: 14400000 }
}));

/*
 * utils
 */

/*
 * routes
 */

app.get('/', function(req, res) {   
    res.render('index', {});
});

/* serve client javascript */
app.get('/client/*.js', function(req, res) {
    var filename = './client/' + req.params[0] + '.js';
    
    res.header("Content-Type", "text/javascript");
    
    fs.readFile(filename, function(err, data) {
        if (err) {
            throw err;
        }
        res.end(data);
    });
});

console.log("Server is now listening on port 8000");
app.listen(8000);


/*
 * socket.io setup
 */

var io = require('socket.io').listen(app);

io.sockets.on('connection', function(socket) {
    var sessionId;
    
    socket.on('register_sid', function(data) {
        assert.ok(data.sid);
        sessionId = data.sid;
    });    
    
    socket.on('whoami', function(data) {
        console.log('whoami: ', sessionId);
    });
});
