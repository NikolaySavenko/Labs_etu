package shapes

import colors.Color
import kotlin.math.pow

data class Square(val width: Double, override val borderColor: Color, override val fillColor: Color) : ColoredShape2d {
    override fun calcArea(): Double {
        return width.pow(2)
    }
}