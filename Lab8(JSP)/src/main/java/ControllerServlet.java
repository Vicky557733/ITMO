import javafx.util.Pair;
import javax.servlet.http.*;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Map;

public class ControllerServlet extends HttpServlet {
    @Override
    public void init() {
        getServletContext().setAttribute("HitHistoryList",new ArrayList<Pair<Point2D.Double, Boolean>>());
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) {
            try {
                getServletContext().getNamedDispatcher("WebForm").forward(request,response);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) {
            try {
                getServletContext().getNamedDispatcher("AreaCheck").forward(request, response);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
    }

    private boolean isAreaCheck(Map<String, String[]> map) {
        return map.get("x") != null && map.get("x").length == 1 && isDouble(map.get("x")[0]) && Double.valueOf(map.get("x")[0]) >= -5 && Double.valueOf(map.get("x")[0]) <= 3 &&
                map.get("y") != null && map.get("y").length == 1 && isDouble(map.get("y")[0]) && Double.valueOf(map.get("y")[0]) >= -5 && Double.valueOf(map.get("y")[0]) <= 3 &&
                map.get("r") != null && map.get("r").length == 1 && isDouble(map.get("r")[0]) && Double.valueOf(map.get("r")[0]) >= 2 && Double.valueOf(map.get("r")[0]) <= 5;
    }
    private boolean isDouble(String s) {
        try {
            Double.valueOf(s);
            return true;
        } catch (Exception ex) {
            return false;
        }
    }
}