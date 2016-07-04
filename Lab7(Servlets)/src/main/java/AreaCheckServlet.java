import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.awt.*;
import java.awt.geom.Point2D;
import java.io.PrintWriter;
import java.util.Map;

public class AreaCheckServlet extends HttpServlet {
    @Override
    public void init() {
        int x = 5;
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) {
        double x = Double.valueOf(request.getParameterMap().get("x")[0]);
        double y = Double.valueOf(request.getParameterMap().get("y")[0]);
        double r = Double.valueOf(request.getParameterMap().get("r")[0]);
        boolean isInArea = calculateIsInArea(new Point2D.Double(x, y), r);

        response.setCharacterEncoding("UTF-8");

        try(PrintWriter writer = response.getWriter()) {
            writeStaticPageContent(writer, x, y, r, isInArea);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private boolean calculateIsInArea(Point2D.Double point, double radius) {
        double x = point.getX();
        double y = point.getY();

        if (x >= 0 && y >= 0)
            return y <= 2*x - radius;
        if (x >= 0 && y <= 0)
            return x <= radius && y <= radius/2;
        if (x <= 0 && y <= 0)
            return Math.pow(x, 2) + Math.pow(y, 2) <= Math.pow(radius, 2);
        if (x < 0 && y < 0)
            return false;

        // for the compiler's sake
        return false;
    }
    private void writeStaticPageContent(PrintWriter responseWriter, double x, double y, double r, boolean isInArea) {
        responseWriter.write("" +
                "<!DOCTYPE html>  \n" +
                "<html lang=\"en\"> \n" +
                "<head> \n" +
                "    <meta charset=\"UTF-8\"> \n" +
                "    <title>Area check</title> \n" +
                "    <style>\n" +
                "        body {   /*Наследование*/\n" +
                "            background-color: #d2d0d2;\n" +
                "        }\n" +
                " #tab {border:1px solid black;}\n" +
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
                "    </style>\n" +
                "</head> \n" +
                " \n" +
                "<body> \n" +
                "    <table id='tab' border='1' cellpadding='0' cellspacing='0' width='50%'>\n" +
                "        <tr> \n" +
                "           <th><p>x: </p></th> \n" +
                "           <th><p>"+ x +"</p></th>\n" +
                "       </tr>\n" +
                "       <tr>\n" +
                "           <th><p>y: </p></th>\n" +
                "           <th><p>"+ y +"</p></th>\n" +
                "       </tr>\n" +
                "       <tr>\n" +
                "           <th><p>R: </p></th>\n" +
                "           <th><p>"+ r +"</p></th>\n" +
                "       </tr>\n" +
                "       <tr>\n" +
                "           <th><p>Точка попадает в область? </p></th>\n" +
                "           <th><p>"+ (isInArea? "Да." : "Нет.") +"</p></th>\n" +
                "       </tr>\n" +
                "    </table> \n" +
                "    <div> \n" +
                "        <br/> <br/> \n" +
                "        <a href=\"/Lab7Vika/\">Назад</a> \n" +
                "    </div> \n" +
                "</body> \n" +
                "</html>");
    }
}