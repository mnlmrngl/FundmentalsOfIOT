function validateForm() {
    var question = document.forms["form"]["question"].value;
    var answerA = document.forms["form"]["answerA"].value;
    var answerB = document.forms["form"]["answerB"].value;
    var answerC = document.forms["form"]["answerC"].value;
    var answerD = document.forms["form"]["answerD"].value;

    var data = JSON.stringify({
        "question": question,
        "answerA": answerA,
        "answerB": answerB,
        "answerC": answerC,
        "answerD": answerD,
    });
    console.log(data);
    if (1 == 1)
        ajax("/safe", data);


}


function ajax(url, data) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", url, true);
    // xhr.setRequestHeader("Content-Type", "application/json");
    xhr.send(data);
}