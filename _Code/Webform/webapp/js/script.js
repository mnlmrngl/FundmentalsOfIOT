function validateForm() {
    console.log('validate')
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
    ajax("/safe");


}


function ajax(url) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", url, true);
    xhr.send();
}