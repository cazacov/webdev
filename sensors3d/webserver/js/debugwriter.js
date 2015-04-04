define(function () {
    var me;

    function DebugWriter(targetDiv) {
        me = this;
        if (!(this instanceof DebugWriter)) {
            throw new TypeError("DebugWriter constructor cannot be called as a function.");
        }
        this.targetDiv = targetDiv;
        this.targetDiv.empty();
    }

    DebugWriter.prototype = {
        constructor: DebugWriter,

        accelerometer: function (message) {
            showText('grav.', message);
        },

        compass: function (message) {
            showText('mag.', message);
        },

        show: function (caption, message) {
            showText(caption, message);
        }
    };

    function showText(caption, message) {
        var element = $(document.getElementById(caption));

        if (!element.length)
        {
            var row = $('<div class="row"></div>');
            var label = $('<div class="col-sm-3 debug-label"></div>');
            element = $('<div class="col-sm-9 debug-value" id="' + caption + '"></div>');

            me.targetDiv.append(row);
            row.append(label);
            row.append(element);

            label.text(caption);
        }
        element.text(message);
    }

    return DebugWriter;
});
