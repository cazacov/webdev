var outElem = document.getElementById('out');
var dataElem = document.getElementById('data');

var counter = 0;

$(function() {
    getSensors();
});

function getSensors() {
    $.get("/sensors", function(data, status) {
        outElem.innerHTML = counter++;
        dataElem.innerHTML = data;
        setTimeout(getSensors, 5);
    });
}
