var divElem = document.getElementById('out');

var counter = 0;

$(function() {
    getSensors();
});

function getSensors() {
    $.get("/arduino/s", function(data, status) {
        divElem.innerHTML = counter++;
        setTimeout(getSensors, 5);
    });
}