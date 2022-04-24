package shapeCollectors

import shapes.ColoredShape2d

interface ExtendedShapeStore : ShapeStore {
    fun addAll(shapes: Collection<ColoredShape2d>)
    fun getSorted(comparator: Comparator<ColoredShape2d>) : List<ColoredShape2d>
}