var app = require('express').createServer(),
    fs = require('fs'),
    port = 3000
    ;

/* 
 * app config 
 */

app.set('view engine', 'jade');

app.listen(port);
console.log('ClientServer listens on port ' + port);

/*
 * routes
 */

app.get('/', function(req, res) {   
    res.render('index', {});
});

/* serve client resources */
(function() {
    var serveFile = function(res, file, contentType) {
        if (contentType) {       
            res.header("Content-Type", contentType);
        }
        
        fs.readFile(file, function(err, data) {
            if (err) {
                /** @todo remove this throw, log instead in prod */
                throw err;
            }
            res.end(data);
        });
    };
    
    app.get('/client/*.js', function(req, res) {
        var filename = './js/' + req.params[0] + '.js';        
        serveFile(res, filename, "text/javascript");
    });
    
    app.get('/client/*.css', function(req, res) {
        var filename = './css/' + req.params[0] + '.css';
        serveFile(res, filename, "text/css");
    });
    
    app.get('/client/*.png', function(req, res) {
        var filename = './png/' + req.params[0] + '.png';
        serveFile(res, filename, "image/png");
    });

}());

