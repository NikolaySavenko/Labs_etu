package shapeCollectors

import colors.Color
import shapes.ColoredShape2d
import shapes.Shape2d

class ShapeCollector : ShapeStore {
    private val shapes: MutableList<ColoredShape2d> = mutableListOf()

    override fun addShape(shape: ColoredShape2d) {
        shapes.add(shape)
    }

    override fun getShapeWithMaxArea(): ColoredShape2d {
        if (shapes.isEmpty()) {
            throw Error("empty collector")
        }

        var found = shapes.first()
        shapes.forEach {
            if (found.calcArea() < it.calcArea()) {
                found = it
            }
        }
        return found
    }

    override fun getShapeWithMinArea(): ColoredShape2d {
        if (shapes.isEmpty()) {
            throw Error("empty collector")
        }

        var found = shapes.first()
        shapes.forEach {
            if (found.calcArea() > it.calcArea()) {
                found = it
            }
        }
        return found
    }

    override fun getShapesAreaSum(): Double {
        var sum = 0.0
        shapes.forEach {
            sum += it.calcArea()
        }
        return sum
    }

    override fun getShapesByBorderColor(color: Color): List<ColoredShape2d> {
        return shapes.filter {
            it.borderColor == color
        }
    }

    override fun getShapesByFillColor(color: Color): List<ColoredShape2d> {
        return shapes.filter {
            it.fillColor == color
        }
    }

    override fun getAllShapes(): List<Shape2d> {
        return shapes.toList()
    }

    override fun getShapesCount(): Int {
        return shapes.count()
    }

    override fun getShapesGroupedByBorderColor(): Map<Color, List<ColoredShape2d>> {
        return groupShapesBy { it.borderColor }
    }

    override fun getShapesGroupedByFillColor(): Map<Color, List<ColoredShape2d>> {
        return groupShapesBy { it.fillColor }
    }

    private fun <T> groupShapesBy(paramSelector: (ColoredShape2d) -> T): MutableMap<T, MutableList<ColoredShape2d>> {
        val map = mutableMapOf<T, MutableList<ColoredShape2d>>()
        shapes.forEach {
            val param = paramSelector(it)
            if (map.containsKey(param)) {
                map[param]!!.add(it)
            } else {
                map[param] = mutableListOf(it)
            }
        }
        return map
    }

    override fun <T> getShapesByType(clazz: Class<T>): List<Shape2d> {
        return buildList {
            shapes.forEach {
                if (clazz.isInstance(it)) {
                    this.add(it)
                }
            }
        }
    }
}