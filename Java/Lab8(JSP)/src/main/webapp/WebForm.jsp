<%@ page import="java.util.ArrayList" %>
<%@ page import="java.awt.geom.Point2D" %>
<%@ page import="javafx.util.Pair" %>
<!DOCTYPE html>
<!--suppress ALL -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
    <meta charset="UTF-8">
    <title>Lab 8 - JSP</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
    <style>
        body {   /*Наследование*/
            background-color: #d2d0d2;
        }
        INPUT:focus{color: blue !important;} /*Применение псевдокласса :focus*/
        INPUT[type="submit"] {color: green;}
        input {
            margin: 1% 1% 4% 2%;
            color: darkblue !important;  /*Каскадирование*/
            font-weight:bold;
            font-size: 17px;
        }

        P {
            padding-left: 0px;
            color: #000080;
            font-family: Arial, Verdana, sans-serif;
            font-weight:bold;
        }

        #container {
            margin: 0% auto;
            width: 900px;
            height: 200px;
        }

        #header {
            margin-left: 15%;
            height: 40px;
            font-size: 190%;
        }

        #information {
            margin-left: 15%;
            font-family: Arial, Verdana, sans-serif, monospace;
            color: #000080;
            font-size: 130%;
            font-weight: 600;
            line-height: 1.5;
            height: 100px;
        }

        #imagine {
            height: 210px;
            text-align: center;
        }
        img {
            border: 3px solid #00a8e1;
        }

        #submit {
            height: 30px;
            margin-left: 40%;
        }

        .inputs {   /*Селектор класса*/
            height: 25px;
            margin-left: 15%;
        }
        .child {
            height: 30px;
            margin-left: 15%;
        }
    </style>
</head>

<body>
<div id="container">
    <div id="header">
        <p>Лабораторная работа №8</p>
    </div>
    <div id="information">
        Суханова Виктория <br/>
        Группа: P3218 <br/>
        Вариант: 999 <br/>
    </div>
    <div id="content">
        <% if (request.getParameter("x")!=null && request.getParameter("y")!=null && request.getParameter("r")!=null) {%>
            <p>GET x: <%= request.getParameter("x")%></p>
            <p>GET y: <%= request.getParameter("y")%></p>
            <p>GET r: <%= request.getParameter("r")%></p>
        <% } %>

        <div id="imagine">
            <img src="\Lab7\resources\images\Lab8.png" alt="image" id="img">
        </div>

        <form method="post" action="WebForm" class="box">
            <div id="xes" class="inputs">
                <label><p>Выберите x: </label>
                <% for(int i = -5; i < 4; i++) { %>
                <label>
                    <input type="button" name="x" value="<%= i %>"/>
                </label>
                <% } %>
                <label id="xErrorMessage" style="color: red">Select x!</label>
                <input id="hiddenX" type='hidden' name='x' value="sht" />
            </div>
            <div id="ys" class="child">
                <label><p>Выберите y:</label>
                <input type="text" name="y">
                <label id="yErrorMessage" style="color: red">Input correct Numeric Y!</label>
            </div>
            <div id="rs" class="child">
                <label><p>Выберите R: </label>
                <input type="text" name="r">
                <label id="rErrorMessage" style="color: red">Select R!</label>
            </div>

            <input id="submit" type="submit" disabled="true" value="Проверить точку">
        </form>

       <center> <p>Результаты предыдущих проверок:</p></center>
        <ul>
            <% for(Pair<Point2D.Double, Boolean> isHit: (ArrayList<Pair<Point2D.Double, Boolean>>)application.getAttribute("HitHistoryList")) { %>
            <li><b><%= (isHit.getValue()? "Точка попала в заданную область" : "Точка не попала в заданную область")%></b> <%= " - Координаты точки: [" + isHit.getKey().getX() + "; " + isHit.getKey().getY() + "]" %></li>
            <% } %>
        </ul>

    </div>
</div>
</body>

<script>
    // Mouse point picker
    var chart = document.getElementById("img");
    chart.onmousedown = tryRedirect;
    function FindPosition(oElement) {
        for(var posX = 0, posY = 0; oElement; oElement = oElement.offsetParent) {
            posX += oElement.offsetLeft;
            posY += oElement.offsetTop;
        }
        return [ posX, posY ];
    }
    function tryRedirect(e) {
        var ImgPos = FindPosition(chart);
        var r =$('input[name="r"]').val();

        var x = (e.pageX - ImgPos[0] - chart.clientWidth/2);    // pixels count
        x = x / (chart.clientWidth / 2);                        // pixels / axis width
        x = x * 1.28 * r;                                       // relative to R

        var y = -(e.pageY - ImgPos[1] - chart.clientHeight/2);
        y = y / (chart.clientHeight / 2);
        y = y * 1.35 * r;

        if (isRValid()) {
            $.post(
                    "http://localhost:8080/Lab7/WebForm" ,
                    { x: x, y:y, r:r } ,
                    function (data) {}
            )
            window.location = "/Lab7/WebForm?x=" + x + "&y=" + y + "&r=" + r;
        }
        else
            alert("Выберите пожалуйста радиус!")
    }

    // x change handler
    $("input[name='x']").on('click', function () {
        var xes = $("input[name='x']");
        // Paint everything
        for (var i = 0; i < xes.size(); i++) {
            if (xes[i] != this)
                xes[i].style.background = '#dddddd';
            else
                xes[i].style.background = '#008800';
        }
        $('#xErrorMessage').text("");
        document.getElementById("hiddenX").value = this.value;
        if (validateAll() == true) {
            $('#submit').removeAttr('disabled');
        }
    });

    // y change handler
    $("input[name='y']").on('change keyup paste inputc', function() {
        var value = $("input[name='y']").val();

        if (isNaN(value) || $.trim(value).length === 0) {
            $('#yErrorMessage').text("Input correct numeric Y!");

            $('#submit').attr('disabled', 'disabled');
        } else if (value < -5 || value > 3) {
            $('#yErrorMessage').text("Y is out of bounds {-5, 3}");

            $('#submit').attr('disabled', 'disabled');
        } else {
            $('#yErrorMessage').text("");

            if (validateAll() == true)
                $('#submit').removeAttr('disabled');
        }
    });
    // r change handler
    $("input[name='r']").on('change keyup paste inputc', function () {
        var value = $("input[name='r']").val();

        if (isNaN(value) || $.trim(value).length === 0) {
            $('#rErrorMessage').text("Input correct numeric R!");

            $('#submit').attr('disabled', 'disabled');
        } else if (value < 2 || value > 5) {
            $('#rErrorMessage').text("Y is out of bounds {2, 5}");

            $('#submit').attr('disabled', 'disabled');
        } else {
            $('#rErrorMessage').text("");

            if (validateAll() == true)
                $('#submit').removeAttr('disabled');
        }
    });

    function isXValid() {
        var xes = $("input[name='x']");
        for (var i = 0; i < xes.size(); i++)
            if (xes[i].style.background == "rgb(0, 136, 0)")
                return true;
        return false;
    }

    function isYValid() {
        var value = $("input[name='y']").val();
        return (!isNaN(value) && $.trim(value).length !== 0 && value >= -5 && value <= 3);
    }
    function isRValid() {
        var value = $("input[name='r']").val();
        return (!isNaN(value) && $.trim(value).length !== 0 && value >= 2 && value <= 5);
    }

    function validateAll() {
        return isXValid() && isYValid() && isRValid();
    }
</script>
</html>
