package Vika;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.List;
import javax.annotation.PostConstruct;
import javax.faces.bean.ApplicationScoped;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.component.EditableValueHolder;
import javax.faces.event.ActionEvent;
import javax.imageio.ImageIO;

import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.ScatterChart;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.data.general.DefaultPieDataset;
import org.jfree.data.general.PieDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.primefaces.model.DefaultStreamedContent;
import org.primefaces.model.StreamedContent;

public class MainManager {
    private float x = -5, y = -5;
    private static float radius = 5;
    private ArrayList<Point2D.Float> pointLog = new ArrayList<>();

    public void setX(float value) {
        this.x = value;
     }
    public float getX() {
        return x;
    }
    public void setY(float value) {
        this.y = value;
    }
    public float getY() {
        return y;
    }
    public void setRadius(float value) {
        this.radius = value;
    }
    public float getRadius() {
        return radius;
    }
    public ArrayList<Point2D.Float> getPointLog() {
        return pointLog;
    }

    public StreamedContent getImage() {
        XYSeriesCollection dataSet = new XYSeriesCollection();
        dataSet.addSeries(calculateChartSeries());
        dataSet.addSeries(calculateGreenSeries());
        dataSet.addSeries(calculateRedSeries());
       // dataSet.addSeries(calculateHitSeries(log));
        //dataSet.addSeries(calculateMissSeries(log));

        JFreeChart chart = ChartFactory.createScatterPlot("Chart", "X", "Y", dataSet, PlotOrientation.VERTICAL, true, true, false);
        XYPlot plot = (XYPlot) chart.getPlot();

        // Set plot colors
        plot.setBackgroundPaint(new Color(255, 255, 0xff));
        plot.setDomainGridlinePaint(new Color(0, 0, 0));
        plot.setRangeGridlinePaint(new Color(0, 0, 0));

        // Series customization
        XYItemRenderer renderer = plot.getRenderer();
        renderer.setSeriesShape(0, new Ellipse2D.Double(0,0,1,1));
        renderer.setSeriesPaint(0, new Color(0, 0, 0));
        renderer.setSeriesPaint(1, new Color(0, 255, 0));
        renderer.setSeriesPaint(2, new Color(255, 0, 0));

        // Set axis ranges
        ValueAxis domainAxis = plot.getDomainAxis();
        ValueAxis rangeAxis = plot.getRangeAxis();
        domainAxis.setRange(-6, 6);
        rangeAxis.setRange(-6, 6);

        try {
            File file = new File("Graphic.png");
            ChartUtilities.saveChartAsPNG(file, chart, 375, 300);
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            return new DefaultStreamedContent(new FileInputStream(new File("Graphic.png")), "image/png");
        } catch(Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public void buttonAction() {
        addPoint(x, y);
    }
    public void xButtonAction(ActionEvent actionEvent) {
        String value = (String)actionEvent.getComponent().getAttributes().get("x");
        x = Float.parseFloat(value);
    }
    public void rButtonAction(ActionEvent actionEvent) {
        String value = (String)actionEvent.getComponent().getAttributes().get("r");
        radius = Float.parseFloat(value);
    }

    private void addPoint(Float x, Float y) {
        if (pointLog.size() == 10)
            pointLog.remove(0);
        pointLog.add(new Point2D.Float(x, y));
    }

    private XYSeries calculateChartSeries() {
        final XYSeries series = new XYSeries("Graphic");
        float precision = 0.01f;

        // bottom -right square
        for (double y = 0; y >= -radius; y -= precision)
            series.add(0, y);
        for (double x = 0; x <= radius; x += precision)
            series.add(x, -radius);
        for (double y = 0; y >= -radius; y -= precision)
            series.add(radius, y);
        for (double x = radius; x >= radius/2; x -= precision)
            series.add(x, 0);

        // top-left triangle
        for (double x = -radius; x <= 0; x += precision)
            series.add(x, 0.5*x+radius/2);
        for (double x = -radius; x <= 0; x += precision)
            series.add(x, 0);

        // top-right circle
        for (double x = 0; x <= radius/2; x += precision)
            series.add(x, Math.sqrt(Math.pow(radius, 2)/4 - Math.pow(x, 2)));

        return series;
    }
    private XYSeries calculateGreenSeries() {
        final XYSeries series = new XYSeries("Green");
        for(Point2D.Float point: pointLog) {
            if (pointHit(point))
                series.add(point.x, point.y);
        }
        return series;
    }
    private XYSeries calculateRedSeries() {
        final XYSeries series = new XYSeries("Red");
        for(Point2D.Float point: pointLog) {
            if (!pointHit(point))
                series.add(point.x, point.y);
        }
        return series;
    }
    private boolean pointHit(Point2D.Float point) {
        if (point.x < 0 && point.y < 0) {
            return false;
        }
        if (point.x <= 0 && point.y >= 0) return point.y <= 0.5 * point.x + radius / 2;
        if (point.x >= 0 && point.y >= 0) return Math.pow(point.x, 2) + Math.pow(point.y, 2) <= Math.pow(radius, 2)/4;
        if (point.x >= 0 && point.y <= 0) return point.x <= radius && point.y >= -radius;
    return false;
    }
}
