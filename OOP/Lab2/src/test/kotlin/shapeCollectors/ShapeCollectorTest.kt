package shapeCollectors

import colors.Color
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test
import shapes.Circle
import shapes.Rectangle
import shapes.Square
import shapes.Triangle
import kotlin.test.assertNotNull
import kotlin.test.assertNull

internal class ShapeCollectorTest {
    private lateinit var collector: ShapeStore

    @BeforeEach
    fun setUp() {
        collector = ShapeCollector()
    }


    @Test
    fun addShape() {
        val circle = Circle(1.0, Color("#ffffff"), Color("#ffffff"))
        val rectangle = Rectangle(1.0, 1.0, Color("#ffffff"), Color("#ffffff"))
        val square = Square(1.0, Color("#ffffff"), Color("#ffffff"))
        val triangle = Triangle(1.0, 1.0, Color("#ffffff"), Color("#ffffff"))

        collector.addShape(circle)
        assertEquals(1, collector.getShapesCount())

        collector.addShape(rectangle)
        assertEquals(2, collector.getShapesCount())

        collector.addShape(square)
        assertEquals(3, collector.getShapesCount())

        collector.addShape(triangle)
        assertEquals(4, collector.getShapesCount())
    }

    @Test
    fun getShapeWithMaxArea() {
        val circle = Circle(1.0, Color("#ffffff"), Color("#ffffff"))
        val rectangle = Rectangle(50.0, 10.0, Color("#ffffff"), Color("#ffffff"))

        collector.addShape(circle)
        collector.addShape(rectangle)

        assertEquals(rectangle, collector.getShapeWithMaxArea())
    }

    @Test
    fun getShapeWithMaxAreaEmptyCollector() {
        assertNull(collector.getShapeWithMaxArea())
    }

    @Test
    fun getShapeWithMinArea() {
        val circle = Circle(1.0, Color("#ffffff"), Color("#ffffff"))
        val rectangle = Rectangle(50.0, 10.0, Color("#ffffff"), Color("#ffffff"))

        collector.addShape(circle)
        collector.addShape(rectangle)

        assertEquals(circle, collector.getShapeWithMinArea())
    }

    @Test
    fun getShapesAreaSum() {
        val square1 = Square(1.0, Color("#ffffff"), Color("#ffffff"))
        val square2 = Square(2.0, Color("#ffffff"), Color("#ffffff"))

        collector.addShape(square1)
        collector.addShape(square2)

        assertEquals(5.0, collector.getShapesAreaSum())
    }

    @Test
    fun getShapesByBorderColor() {
        val square1 = Square(1.0, Color("#ffffff"), Color("#ffffff"))
        val square2 = Square(2.0, Color("#ff0000"), Color("#ffffff"))

        collector.addShape(square1)
        collector.addShape(square2)

        val shapes = collector.getShapesByBorderColor(Color("#ffffff"))
        assertEquals(1, shapes.count())
        assertEquals(square1, shapes[0])
    }

    @Test
    fun getShapesByFillColor() {
        val square1 = Square(1.0, Color("#ffffff"), Color("#d0ff00"))
        val square2 = Square(2.0, Color("#ff0000"), Color("#ffffff"))

        collector.addShape(square1)
        collector.addShape(square2)

        val shapes = collector.getShapesByFillColor(Color("#d0ff00"))
        assertEquals(1, shapes.count())
        assertEquals(square1, shapes[0])
    }

    @Test
    fun getAllShapes() {
        val square1 = Square(1.0, Color("#ffffff"), Color("#d0ff00"))
        val square2 = Square(2.0, Color("#ff0000"), Color("#ffffff"))

        collector.addShape(square1)
        collector.addShape(square2)

        val shapes = collector.getAllShapes()
        assertEquals(2, shapes.count())
        assertEquals(square1, shapes[0])
        assertEquals(square2, shapes[1])
    }

    @Test
    fun getShapesCount() {
        val square1 = Square(1.0, Color("#ffffff"), Color("#d0ff00"))
        val square2 = Square(2.0, Color("#ff0000"), Color("#ffffff"))

        collector.addShape(square1)
        collector.addShape(square2)

        assertEquals(2, collector.getShapesCount())
    }

    @Test
    fun getShapesGroupedByBorderColor() {
        val square1 = Square(1.0, Color("#ffffff"), Color("#d0ff00"))
        val square2 = Square(2.0, Color("#ffffff"), Color("#ff0000"))
        val square3 = Square(2.0, Color("#ff0000"), Color("#5a4980"))
        val square4 = Square(2.0, Color("#d54240"), Color("#5a4980"))

        collector.addShape(square1)
        collector.addShape(square2)
        collector.addShape(square3)
        collector.addShape(square4)

        val shapes = collector.getShapesGroupedByBorderColor()
        assertEquals(3, shapes.count())

        val redShapes = shapes[Color("#ffffff")]
        assertNotNull(redShapes)
        assertEquals(2, redShapes.count())
        assertEquals(square1, redShapes[0])
        assertEquals(square2, redShapes[1])

        val blueShapes = shapes[Color("#ff0000")]
        assertNotNull(blueShapes)
        assertEquals(1, blueShapes.count())
        assertEquals(square3, blueShapes[0])

        val rainbowShapes = shapes[Color("#d54240")]
        assertNotNull(rainbowShapes)
        assertEquals(1, rainbowShapes.count())
        assertEquals(square4, rainbowShapes[0])
    }

    @Test
    fun getShapesGroupedByFillColor() {
        val square1 = Square(1.0, Color("#ffffff"), Color("#d0ff00"))
        val square2 = Square(2.0, Color("#ffffff"), Color("#ff0000"))
        val square3 = Square(2.0, Color("#ff0000"), Color("#5a4980"))
        val square4 = Square(2.0, Color("#d54240"), Color("#5a4980"))

        collector.addShape(square1)
        collector.addShape(square2)
        collector.addShape(square3)
        collector.addShape(square4)

        val shapes = collector.getShapesGroupedByFillColor()
        assertEquals(3, shapes.count())

        val yellowShapes = shapes[Color("#d0ff00")]
        assertNotNull(yellowShapes)
        assertEquals(1, yellowShapes.count())
        assertEquals(square1, yellowShapes[0])

        val blueShapes = shapes[Color("#ff0000")]
        assertNotNull(blueShapes)
        assertEquals(1, blueShapes.count())
        assertEquals(square2, blueShapes[0])

        val chuckShapes = shapes[Color("#5a4980")]
        assertNotNull(chuckShapes)
        assertEquals(2, chuckShapes.count())
        assertEquals(square3, chuckShapes[0])
        assertEquals(square4, chuckShapes[1])
    }

    @Test
    fun getShapesByType() {
        val square = Square(1.0, Color("#ffffff"), Color("#d0ff00"))
        val circle = Circle(2.0, Color("#ffffff"), Color("#3366ff"))
        val rectangle = Rectangle(2.0, 2.0, Color("#ff0000"), Color("#5a4980"))
        val triangle = Triangle(2.0, 2.0, Color("#d54240"), Color("#5a4980"))


        collector.addShape(square)
        collector.addShape(circle)
        collector.addShape(rectangle)
        collector.addShape(triangle)

        val squares = collector.getShapesByType(Square::class.java)
        assertEquals(square, squares[0])

        val circles = collector.getShapesByType(Circle::class.java)
        assertEquals(circle, circles[0])

        val rectangles = collector.getShapesByType(Rectangle::class.java)
        assertEquals(rectangle, rectangles[0])

        val triangles = collector.getShapesByType(Triangle::class.java)
        assertEquals(triangle, triangles[0])
    }
}