const char webappIndex[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP WebApp</title>
    <link rel="stylesheet" href="css/styles.css">
    
</head>

<body>
    <h1>Haturquiz</h1>


    <form id="form" type="GET">
        <label for="question">Frage</label>
        <input value="Wie hoch ist der Baum?" type="text" name="question" id="question">
        
        <label for="answerA">Antwort A</label>
        <input value="5m" type="text" name="answerA" id="answerA">

        <label for="answerB">Antwort B</label>
        <input value="12,5m" type="text" name="answerB" id="answerB">
        
        <label for="answerC">Antwort C</label>
        <input value="drölf Zentimäöüter" type="text" name="answerC" id="answerC">
        
        <label for="answerD">Antwort D</label>
        <input value="Scheiß egal" type="text" name="answerD" id="answerD">     

        <input type="button" onclick="validateForm()" name="submit" value="Abschicken">
    </form>

    <button onclick="getQuestions()">Fragen auslesen</button>

    <script>
        function validateForm() {
            console.log('validate')

            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open("GET", "/save__!q" + document.forms["form"]["question"].value +
                "__!a" + document.forms["form"]["answerA"].value +
                "__!b" + document.forms["form"]["answerB"].value +
                "__!c" + document.forms["form"]["answerC"].value +
                "__!d" + document.forms["form"]["answerD"].value, true);
            xmlhttp.send();
        }

        function getQuestions() {
            console.log("Testing");
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open("GET", "/getQuestions", true);
            xmlhttp.send();
        }
    </script>


</body>

</html>
)=====";