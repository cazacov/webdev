var divElem = document.getElementById('out');

var counter = 0;

$(function() {
    getSensors();
});

function getSensors() {
    $.get("/data/get/s", function(data, status) {
        divElem.innerHTML = counter++;
        console.log(data);
        setTimeout(getSensors, 5);
    });
}
