package shapeCollectors

import shapes.ColoredShape2d

class ExtendedCollector: ShapeCollector(), ExtendedShapeStore {
    override fun addAll(shapes: Collection<ColoredShape2d>) {
        shapes.forEach {
            this.shapes.add(it)
        }
    }

    override fun getSorted(comparator: Comparator<ColoredShape2d>) : List<ColoredShape2d>  {
        val copy = shapes.toMutableList()
        var i = 1
        while (i < copy.size) {
            if (comparator.compare(copy[i - 1], copy[i]) > 0) {
                val first = copy[i - 1]
                copy[i - 1] = copy[i]
                copy[i] = first
            }
            i++
        }
        return copy
    }
}