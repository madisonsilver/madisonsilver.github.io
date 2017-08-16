var canvas;
function findCanvas(){
    canvas = document.getElementById('playField');
}
function drawFrame(){
if (canvas.getContext) {
    var ctx = canvas.getContext('2d');
    // drawing code here
} else {
    alert("Your browser doesn't seem to support <canvas>.")
}
}
