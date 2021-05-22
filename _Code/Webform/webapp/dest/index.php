<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP WebApp</title>
    <style>
    html {
        height: 100%;
    }
    body {
        font-family: Arial, Helvetica, sans-serif;
        max-width: 400px;
        height: 100%;
        margin: auto;
    }
    
    #thanks{
        display: none;
    }
    
    footer {
        color: grey;
    }
    </style>
    <script>
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
        xhr.setRequestHeader("Content-Type", "application/json");
        xhr.send(data);
    }
    </script>
</head>
<body>
    <h1>Haturquiz</h1>

    <?php
$txt = "PHP";
echo "I love $txt!";
?>
    

    <form method="post" id="form" action="<?php echo $_SERVER['PHP_SELF']; ?>">
        <input type="text" name="question" id="question">
        <label for="question">Frage</label>

        <input type="text" name="answerA" id="answerA">
        <label for="answerA">Antwort A</label>
        <input type="text" name="answerB" id="answerB">
        <label for="answerB">Antwort B</label>
        <input type="text" name="answerC" id="answerC">
        <label for="answerC">Antwort C</label>
        <input type="text" name="answerD" id="answerD">
        <label for="answerD">Antwort D</label>

        <input type="submit" name="submit" value="Abschicken">
    </form>
    <!-- <section id="thanks">
        Vielen Dank für das Einreichen der Frage. Wir werden Deine Frage Prüfen und diese ggf. in das Quiz einfügen.
        <button id="newQuestion">Neue Frage einreichen</button>
    </section> -->

    <?php
        if(isset($_POST['submit'])){ 
            $myfile = fopen("questions.txt", "a") or die("Unable to open file!");
            fwrite($myfile, "Frage: ".$_POST["question"]."\n");
            fwrite($myfile, "   A: ".$_POST["answerA"]."\n");
            fwrite($myfile, "   B: ".$_POST["answerB"]."\n");
            fwrite($myfile, "   C: ".$_POST["answerC"]."\n");
            fwrite($myfile, "   D: ".$_POST["answerD"]."\n");
            fwrite($myfile, "-----------------------\n");
            fwrite($myfile, "\n");

            fclose($myfile);
            // header("Location: http://localhost/ESP_safe_text_file_php/thanks.php");
    ?>
            <script>
                // document.getElementById('form').style.display="none";
                // document.getElementById('thanks').style.display='block';
            </script>
<?php
    }
?>
    

    <footer>
        <p>This example covers the following:</p>
        <ul>
            <li>Images are embedded via base64 in the stylesheet</li>
            <li>All ressources are stripped, unneccessary whitespace is removed (uglified)</li>
            <li>All script and style resourrces are embedded within the html file</li>
            <li>The final html is wrapped as an c++ char in webapp-index.h</li>
        </ul>
    </footer>
    
</body>
</html>