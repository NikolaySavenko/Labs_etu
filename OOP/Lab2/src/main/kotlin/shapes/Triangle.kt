package shapes

import colors.Color

data class Triangle(
    val width: Double,
    val height: Double,
    override val borderColor: Color,
    override val fillColor: Color,
) :
    ColoredShape2d {
    override fun calcArea(): Double {
        return width * height / 2
    }
}