import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

public class WebFormServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) {
        response.setCharacterEncoding("UTF-8");
        writeStaticPageContent(request, response);
    }

    private void writeStaticPageContent(HttpServletRequest request, HttpServletResponse response) {
        try (PrintWriter writer = response.getWriter()) {

            writer.write("" +
                    "<!DOCTYPE html> \n" +
                    "<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">\n " +
                    "<head> \n" +
                    "  <meta charset=\"UTF-8\">\n " +
                    "  <title>Lab 7 - Servlets</title>\n" +
                    "  <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js\"></script> \n" +
                            "<style>\n" +
                            "        .redBorder {\n" +
                            "            border: 1px solid #ff0000;\n" +
                            "        }\n" +
                            "        body {   /*Наследование*/\n" +
                            "            background-color: #d2d0d2;\n" +
                            "        }\n" +
                            "        INPUT:focus{color: blue !important;} /*Применение псевдокласса :focus*/\n" +
                            "        INPUT[type=\"submit\"] {color: green;}\n" +
                            "        input {\n" +
                            "            margin: 1% 1% 4% 2%;\n" +
                            "            color: darkblue !important;  /*Каскадирование*/\n" +
                            "            font-weight:bold;\n" +
                            "            font-size: 17px;\n" +
                            "\n" +
                            "        }\n" +
                            "\n" +
                            "        #tab {border:1px solid black;}\n" +
                            "\n" +
                            "        th p {              /*Селекторы потомков*/\n" +
                            "            color: #000080;\n" +
                            "            margin: 2%;\n" +
                            "            text-align: center;\n" +
                            "        }\n" +
                            "\n" +
                            "        P {\n" +
                            "            padding-left: 20px;\n" +
                            "            color: #000080;\n" +
                            "            font-family: Arial, Verdana, sans-serif;\n" +
                            "            font-weight:bold;\n" +
                            "        }\n" +
                            "\n" +
                            "        #container {\n" +
                            "            margin: 3% auto;\n" +
                            "            width: 900px;\n" +
                            "            height: 200px;\n" +
                            "        }\n" +
                            "\n" +
                            "        #header {\n" +
                            "            height: 40px;\n" +
                            "            text-align: center;\n" +
                            "            font-size: 190%;\n" +
                            "        }\n" +
                            "\n" +
                            "        #information {\n" +
                            "            text-align: center;\n" +
                            "            font-family: Arial, Verdana, sans-serif, monospace;\n" +
                            "            color: #000080;\n" +
                            "            font-size: 130%;\n" +
                            "            font-weight: 600;\n" +
                            "            line-height: 1.5;\n" +
                            "            height: 100px;\n" +
                            "        }\n" +
                            "\n" +
                            "        #imagine {\n" +
                            "            height: 350px;\n" +
                            "            text-align: center;\n" +
                            "        }\n" +
                            "\n" +
                            "\n" +
                            "        #submit {\n" +
                            "            height: 30px;\n" +
                            "            text-align: center;\n" +
                            "            margin-left: 40%;\n" +
                            "        }\n" +
                            "\n" +
                            "        .inputs {   /*Селектор класса*/\n" +
                            "            height: 20px;\n" +
                            "            margin-left: 15%;\n" +
                            "        }\n" +
                            "        .child {\n" +
                            "            height: 20px;\n" +
                            "            margin-left: 15%;\n" +
                            "        }\n" +
                            "    </style>\n" +
                    "</head>\n" +
                    "\n" +
                    "<body>\n" +
                    "<div id=\"container\">\n" +
                    "   <div id=\"header\">\n" +
                    "<p>Лабораторная работа №7</p>\n" +
                    "</div>\n" +
                    "<div id=\"information\">\n" +
                    "           Суханова Виктория <br/>\n" +
                    "           Группа: P3218 <br/>\n" +
                    "           Вариант: 477 <br/>\n" +
                    "   </div>\n" +
                    "   <div id=\"content\">\n" +
                            "        <div id=\"imagine\">\n" +
                            "<img src=\"http://i9.pixs.ru/storage/5/6/6/Pipjpg_4739846_21691566.png\" border=\"0\" alt=\"Image Hosted by PiXS.ru\" />\n" +
                            "        </div>\n" +
                    "\n" +
                    "       <!-- Xes -->\n" +
                    "       <form method=\"get\" action=\"\">\n" +
                    "           <div id=\"xes\" class=\"inputs\">\n" +
                    "               <label><p>Выберите x: </label>\n" +
                    "                <select id=\"x\" class=\"x\" name=\"x\">");
            for (double i = -4; i <= 4; i += 1) {
                writer.write("" +
                        "                  <option value=\"" + i + "\"/>\n" +
                        "                  " + i + "</option>\n");
            }


            writer.write("" +
                    "                </select>\n" +
                    "           <label id=\"xErrorMessage\" style=\"color: red\">Select x!</label>\n" +
                    "           </div>\n" +
                    "\n" +
                    "           <!-- Y -->\n" +
                    "           <div id=\"ys\" class=\"child\">\n" +
                    "               <label>\n" +
                    "                   <p>Выберите y:\n" +
                    "                   <input id=\"y\" name=\"y\" type=\"text\"/>\n" +
                    "               </label>\n" +
                    "               <label id=\"yErrorMessage\" style=\"color: red\">Input correct numeric Y!</label>\n" +
                    "           </div>\n" +
                    "\n" +
                    "           <!-- Rs -->\n" +
                    "           <div id=\"rs\" class=\"child\">\n" +
                    "               <label><p>Выберите R: </label>\n");
            for (double i = 1; i <= 3; i += 0.5) {
                writer.write("" +
                        "                  <label>\n" +
                        "                  <input type=\"checkbox\" name=\"r\" value=\"" + i + "\" />\n" +
                        "                  " + i + "\n" +
                        "              </label>\n");
            }
            writer.write("" +
                    "               <label id=\"rErrorMessage\" style=\"color: red\">Select r!</label>\n" +
                    "           </div>\n" +
                    "\n" +
                    "            <input id=\"submit\" type=\"submit\" disabled=\"true\" value=\"Проверить точку\">\n" +
                    "       </form>\n" +
                    "   </div>\n" +
                    "</div>\n" +
                    "</body>\n" +
                    "\n" +
                    "<script>\n" +
                    "// x validator \n" +
                    "$('#x').on('change', function () { \n" +
                    "   var valueX = $('#x option:selected').val(); \n" +
                    "   if ((valueX <= -4 || valueX >= 4)) { \n" +
                    "       $('#xErrorMessage').text(\"Select X!\"); \n" +
                    "       $('#submit').attr('disabled', 'disabled'); \n" +
                    "   } else { \n" +
                    "       $('#xErrorMessage').text(\"\"); \n" +
                    "       if (validateAll() == true) { \n" +
                    "           $('#submit').removeAttr('disabled'); \n" +
                    "       } \n" +
                    "   } \n" +
                    "}); \n" +
                    "// y validator \n" +
                    "$('#y').on('change keyup paste inputc', function() { \n" +
                    "   var value = $('#y').val(); \n" +
                    "   if (isNaN(value) || $.trim(value).length === 0) { \n" +
                    "       $('#yErrorMessage').text(\"Input correct numeric Y!\"); \n" +
                    "       $('#submit').attr('disabled', 'disabled'); \n" +
                    "   } else if (value < -3 || value > 3) { \n" +
                    "       $('#yErrorMessage').text(\"Y is out of bounds {-3, 3}\"); \n" +
                    "       $('#submit').attr('disabled', 'disabled'); \n" +
                    "   } else { \n" +
                    "       $('#yErrorMessage').text(\"\"); \n" +
                    "       if (validateAll() == true) \n" +
                    "           $('#submit').removeAttr('disabled'); \n" +
                    "   } \n" +
                    "}); \n" +
                    "// r validator \n" +
                    "$(\"input[name*='r']\").on('click', function () { \n" +
                    "   var $box = $(this); \n" +
                    "   if ($box.is(\":checked\")) { \n" +
                    "       var group = \"input:checkbox[name='\" + $box.attr(\"name\") + \"']\"; \n" +
                    "       $(group).prop(\"checked\", false); \n" +
                    "       $box.prop(\"checked\", true); \n" +
                    "       $('#rErrorMessage').text(\"\"); \n" +
                    "       if (validateAll() == true) \n" +
                    "           $('#submit').removeAttr('disabled'); \n" +
                    "   } else { \n" +
                    "       $box.prop(\"checked\", false); \n" +
                    "       $('#rErrorMessage').text(\"Select R!\"); \n" +
                    "       $('#submit').attr('disabled', 'disabled'); \n" +
                    "   } \n" +
                    "}); \n\n" +
                    "function isXSelected() { \n" +
                    "   var valueX = $('#x option:selected').val(); \n" +
                    "   return (valueX >= -4 && valueX <= 4); \n" +
                    "} \n" +
                    "function isYValid() { \n" +
                    "   var value = $('#y').val();  \n" +
                    "   return (!isNaN(value) && $.trim(value).length !== 0 && value >= -3 && value <= 3);\n" +
                    "} \n" +
                    "function isRSelected() {\n" +
                    "   return $('input[name=\"r\"]:checked').val() != null;\n" +
                    "}\n\n" +
                    "function validateAll() {\n" +
                    "   return isXSelected() && isYValid() && isRSelected(); \n" +
                    "}\n" +
                    "</script>\n" +
                    "</html> \n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}