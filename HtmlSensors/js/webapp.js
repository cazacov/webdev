sprintf = require(['sprintf']).sprintf;

require(['debugwriter', 'sensors'], function (DebugWriter, Sensors) {

    $().ready(function () {
        var debugBox = $(document.getElementById('debugBox'));

        var debugwriter = new DebugWriter(debugBox);
        var sensors = new Sensors(debugwriter, sprintf);
    });
});