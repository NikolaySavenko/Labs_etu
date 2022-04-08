package ShapeOperators

import colors.Color
import shapes.ColoredShape2d
import shapes.Shape2d

class ShapeCollector : IShapeCollector {
    override fun addShape(shape: Shape2d): Void {
        TODO("Not yet implemented")
    }

    override fun getShapeWithMaxArea(): Shape2d {
        TODO("Not yet implemented")
    }

    override fun getShapeWithMinArea(): Shape2d {
        TODO("Not yet implemented")
    }

    override fun getShapesAreaSum(): Int {
        TODO("Not yet implemented")
    }

    override fun getShapesByBorderColor(color: Color): List<ColoredShape2d> {
        TODO("Not yet implemented")
    }

    override fun getShapesByFillColor(color: Color): List<ColoredShape2d> {
        TODO("Not yet implemented")
    }

    override fun getAllShapes(): List<Shape2d> {
        TODO("Not yet implemented")
    }

    override fun getShapesCount(): Int {
        TODO("Not yet implemented")
    }

    override fun getShapesGroupedByBorderColor(): Map<Color, List<ColoredShape2d>> {
        TODO("Not yet implemented")
    }

    override fun getShapesGroupedByFillColor(): Map<Color, List<ColoredShape2d>> {
        TODO("Not yet implemented")
    }

    override fun getShapesByType(type: String): List<Shape2d> {
        TODO("Not yet implemented")
    }
}