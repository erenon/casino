// Original code is from http://api.jquery.com/jQuery.cssHooks/


(function($) {
    if(!$.cssHooks) {
        throw ("jQuery 1.4.3+ is needed for this plugin to work");
    }

    function styleSupport(prop) {
        var div = document.createElement("div"),
            supportedProp, 
            vendorProp, 
            capProp = prop.charAt(0).toUpperCase() + prop.slice(1), 
            prefixes = ["Moz", "Webkit", "O", "ms"],
            i
            ;
        
        // jslint doesn't like the "a in b" construct
        // but the advised hasOwnProperty method
        // doesn't work in firefox
        // if (div.style.hasOwnProperty(prop)) {
        if (prop in div.style) {
            supportedProp = prop;
        } else {
            for (i = 0; i < prefixes.length; i++) {
                vendorProp = prefixes[i] + capProp;
                // if (div.style.hasOwnProperty(vendorProp)) {
                if (vendorProp in div.style) {    
                    supportedProp = vendorProp;
                    break;
                }
            }
        }
        
        div = null;
        $.support[prop] = supportedProp;
        return supportedProp;
    }

    function setHook(property) {
        var supportedProp = styleSupport(property);

        // Set cssHooks only for browsers that
        // support a vendor-prefixed property
        if (supportedProp && supportedProp !== property) {
            $.cssHooks[property] = {
                get : function(elem, computed, extra) {
                    return $.css(elem, supportedProp);
                },
                set : function(elem, value) {
                    elem.style[supportedProp] = value;
                }
            };
        }
    }

    var properties = ['borderRadius', 'transition', 'transform'],
        i;

    for (i = properties.length - 1; i >= 0; i--) {
        setHook(properties[i]);
    }

}(jQuery));

