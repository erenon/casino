var StatusBar = function(target) {
    this.target = target;
    
    this.log = function(message, severity) {
        var severity = severity || 'info',
            entry;
        
        entry = $('<li class="' + severity + '"/>').text(message);
        target.prepend(entry);
    };
};

StatusBar.prototype.info = function(message) {
    this.log(message, 'info');  
};

StatusBar.prototype.warn = function(message) {
    this.log(message, 'warn');
};

StatusBar.prototype.error = function(message) {
    this.log(message, 'error');
}