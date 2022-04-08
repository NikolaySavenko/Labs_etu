package ShapeOperators

import colors.Color
import shapes.ColoredShape2d
import shapes.Shape2d

interface IShapeCollector {
    fun addShape(shape: Shape2d): Void
    fun getShapeWithMaxArea(): Shape2d
    fun getShapeWithMinArea(): Shape2d
    fun getShapesAreaSum(): Int
    fun getShapesByBorderColor(color: Color): List<ColoredShape2d>
    fun getShapesByFillColor(color: Color): List<ColoredShape2d>
    fun getAllShapes(): List<Shape2d>
    fun getShapesCount(): Int
    fun getShapesGroupedByBorderColor(): Map<Color, List<ColoredShape2d>>
    fun getShapesGroupedByFillColor(): Map<Color, List<ColoredShape2d>>
    fun getShapesByType(type: String): List<Shape2d>
}