var
NameManager = function(options) {
var usedNames = [],
    nextAnonId = 1,
    anonPrefix,
    nameManager = {},
    isNameTaken = function(name) {
        var i;
        
        for (i = 0; i < usedNames.length; i++) {
            if (usedNames[i] === name) {
                return true;
            }
        }
        
        return false;
    },
    addName = function(name) {
        usedNames.push(name);
    },
    removeName = function(name) {
        var i;
        
        for (i = 0; i < usedNames.length; i++) {
            if (usedNames[i] === name) {
                usedNames.splice(i,1);
            }
        }        
    },
    getAnonId = function() {
        var date = new Date(),
            id = nextAnonId
            ;
            
        nextAnonId++;
        nextAnonId %= 100;
                    
        return String((date.getTime() %100 ) + id);
    }
    ;
    
    options = options || {};
    anonPrefix = options.anonPredix || "User ";
    
    nameManager.changeName = function(currentName, newName) {
        if (typeof(newName) !== 'string') {
            return false;    
        }
        
        if (!isNameTaken(newName)) {
            addName(newName);
            removeName(currentName);
            
            return true;
        } else {
            return false;
        }
    };
    
    nameManager.getAnonName = function() {
        var name;
        
        do {
            name = anonPrefix + getAnonId();
        } while (isNameTaken(name));
        
        addName(name);
        return name;
    };  
    
    return nameManager;
}
;

module.exports = NameManager;
