package shapeCollectors

import colors.Color
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test

import org.junit.jupiter.api.Assertions.*
import shapes.Circle
import shapes.Rectangle

internal class ExtendedCollectorTest {
    private lateinit var collector: ExtendedShapeStore

    @BeforeEach
    fun setUp() {
        collector = ExtendedCollector()
    }


    @Test
    fun addAll() {
        val circle = Circle(1.0, Color("#ffffff"), Color("#ffffff"))
        val rectangle = Rectangle(50.0, 10.0, Color("#ffffff"), Color("#ffffff"))

        collector.addAll(listOf(circle, rectangle))

        val shapes = collector.getAllShapes()

        assertTrue(shapes.contains(circle))
        assertTrue(shapes.contains(rectangle))
    }

    @Test
    fun getSorted() {
        val rectangle = Rectangle(50.0, 10.0, Color("#ffffff"), Color("#ffffff"))
        val circle = Circle(1.0, Color("#ffffff"), Color("#ffffff"))

        collector.addShape(circle)
        collector.addShape(rectangle)

        val sortedShapes = collector.getSorted(compareBy { it.calcArea() })

        assertEquals(circle, sortedShapes[0])
        assertEquals(rectangle, sortedShapes[1])
    }
}