const char webappIndex[] PROGMEM = R"=====(!DOCTYPE html><html lang="en"><head><meta charset="UTF-8"><meta http-equiv="X-UA-Compatible" content="IE=edge"><meta name="viewport" content="width=device-width,initial-scale=1"><title>ESP WebApp</title><style>html{height:100%}body{font-family:Arial,Helvetica,sans-serif;max-width:400px;height:100%;margin:auto}#thanks{display:none}footer{color:grey}</style><script>function validateForm() {
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
    }</script></head><body><h1>Haturquiz</h1><form tyoe="GET" id="form" onsubmit="return validateForm(this)"><input type="text" name="question" id="question"> <label for="question">Frage</label> <input type="text" name="answerA" id="answerA"> <label for="answerA">Antwort A</label> <input type="text" name="answerB" id="answerB"> <label for="answerB">Antwort B</label> <input type="text" name="answerC" id="answerC"> <label for="answerC">Antwort C</label> <input type="text" name="answerD" id="answerD"> <label for="answerD">Antwort D</label> <input type="submit" name="submit" value="Abschicken"></form><footer><p>This example covers the following:</p><ul><li>Images are embedded via base64 in the stylesheet</li><li>All ressources are stripped, unneccessary whitespace is removed (uglified)</li><li>All script and style resourrces are embedded within the html file</li><li>The final html is wrapped as an c++ char in webapp-index.h</li></ul></footer></body></html>
    )=====";