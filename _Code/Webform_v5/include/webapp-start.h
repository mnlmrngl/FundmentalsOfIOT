const char webappStart[] = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP WebApp</title>
    <link rel="stylesheet" href="css/styles.css">
    <script>
        function validateForm() {
            console.log('validate')

            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open("GET", "/save/__!q" + document.forms["form"]["question"].value +
                "__!a" + document.forms["form"]["answerA"].value +
                "__!b" + document.forms["form"]["answerB"].value +
                "__!c" + document.forms["form"]["answerC"].value +
                "__!d" + document.forms["form"]["answerD"].value, true);
            xmlhttp.send();
        }

        function download() {
            console.log("Download");
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open("GET", "/download", true);
            xmlhttp.send();
        }

        function deleteSPIFFS() {
            console.log("Löschen");
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open("GET", "/delete", true);
            xmlhttp.send();
        }

        function createTextFile(jsonString) {
            console.log('TXT File');
            var link = document.createElement('a');
            link.download = 'data.json';
            var blob = new Blob([jsonString], {
                type: 'text/plain'
            });
            link.href = window.URL.createObjectURL(blob);
            link.click();
        }
function formatContent(content) {
            content = content.replace('__F:', '\n\nF:');
            content = content.replace('__A:', '\nA:');
            content = content.replace('__B:', '\nB:');
            content = content.replace('__C:', '\nC:');
            content = content.replace('__D:', '\nD:');
            return content;
        }

        function downloadFile(filename, content) {
            var element = document.createElement('a');
            var end = content.match(/__F/g).length
            for (let i = 0; i < end; i++) {
                content = formatContent(content);
            }        

            element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(content));
            element.setAttribute('download', filename);

            element.style.display = 'none';
            document.body.appendChild(element);

            element.click();

            document.body.removeChild(element);
        }
    </script>
</head>

<body>
    <h1>Haturquiz</h1>


    <form id="form" type="GET">
        <input type="text" name="question" id="question" value="Ich heiße Klaus">
        <label for="question">Frage</label>

        <input type="text" name="answerA" id="answerA" value="ä Ä ö Ö ü Ü">
        <label for="answerA">Antwort A</label>
        <input type="text" name="answerB" id="answerB">
        <label for="answerB">Antwort B</label>
        <input type="text" name="answerC" id="answerC">
        <label for="answerC">Antwort C</label>
        <input type="text" name="answerD" id="answerD">
        <label for="answerD">Antwort D</label>

        <input type="button" onclick="validateForm()" name="submit" value="Abschicken">
    </form>

    <button onclick="download(); window.location.reload();">Downloadlink erstellen</button>
   
    <button onclick="deleteSPIFFS(); window.location.reload();">Eingereichte Fragen löschen</button>


)=====";