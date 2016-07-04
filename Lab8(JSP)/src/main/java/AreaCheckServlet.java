import javafx.util.Pair;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.awt.geom.Point2D;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class AreaCheckServlet extends HttpServlet {
    @Override
    public void init() {
        int x = 5;
    }
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.getWriter().print("<h1>This page does not support GET requests</h1>");
    }
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        double x = Double.valueOf(request.getParameterMap().get("x")[0]);
        double y = Double.valueOf(request.getParameterMap().get("y")[0]);
        double r = Double.valueOf(request.getParameterMap().get("r")[0]);
        boolean isInArea = calculateIsInArea(new Point2D.Double(x, y), r);

        ArrayList<Pair<Point2D.Double, Boolean>> context = (ArrayList<Pair<Point2D.Double, Boolean>>)getServletContext().getAttribute("HitHistoryList");
        context.add(new Pair(new Point2D.Double(x, y), isInArea));

        getServletContext().getNamedDispatcher("WebForm").forward(request,response);
        response.setCharacterEncoding("UTF-8");
    }

    private boolean calculateIsInArea(Point2D.Double point, double radius) {
        double x = point.getX();
        double y = point.getY();

        if (x >= 0 && y >= 0)
            return y <= -2*x + radius;
        if (x <= 0 && y >= 0)
            return x >= -radius && y <= radius;
        if (x <= 0 && y <= 0)
            return Math.pow(x, 2) + Math.pow(y, 2) <= Math.pow(radius, 2);
        if (x < 0 && y < 0)
            return false;

        // for the compiler's sake
        return false;
    }
}
