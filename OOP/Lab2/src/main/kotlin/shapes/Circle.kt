package shapes

import colors.Color
import kotlin.math.PI
import kotlin.math.pow

data class Circle(val radius: Double, override val borderColor: Color, override val fillColor: Color) : ColoredShape2d {
    override fun calcArea(): Double {
        return PI * radius.pow(2)
    }
}