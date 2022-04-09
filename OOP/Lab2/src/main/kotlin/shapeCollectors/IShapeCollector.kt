package shapeCollectors

import colors.Color
import shapes.ColoredShape2d
import shapes.Shape2d

interface IShapeCollector {
    fun addShape(shape: ColoredShape2d)
    fun getShapeWithMaxArea(): ColoredShape2d
    fun getShapeWithMinArea(): ColoredShape2d
    fun getShapesAreaSum(): Double
    fun getShapesByBorderColor(color: Color): List<ColoredShape2d>
    fun getShapesByFillColor(color: Color): List<ColoredShape2d>
    fun getAllShapes(): List<Shape2d>
    fun getShapesCount(): Int
    fun getShapesGroupedByBorderColor(): Map<Color, List<ColoredShape2d>>
    fun getShapesGroupedByFillColor(): Map<Color, List<ColoredShape2d>>
    fun <T> getShapesByType(clazz: Class<T>): List<Shape2d>
}